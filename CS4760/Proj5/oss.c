//$Author$
//$Date$
//$Log$
//////////

#include "shared.h"

//Shared memory
key_t key;
int shm_ID;

key_t clockKey;
int clockID;

key_t messageKey;
int messageID;

//General variables
int i;
pid_t pid;
pid_t ossPID;
int childSelected;

//pid_t returnPID;
int processCount = 0;
int tVal = 20;
char msgBuff[100];

//To pass to user
char *pnum;
char *user_clockid;
char *user_sharedID;
char *child_num;

//Structures
clockSim_t *clockStruct = NULL;
shared_data *sharedStruct;
int childPID[MAXPROCESSES];

//Signals
volatile sig_atomic_t killFlag = 0;
int status;


//FUNCTIONS
void ReceivedKill(int signum);
void cleanup();
void forkUser(int childArg);
void updatePID();
void writelog(char *);
void initShared();
void initResource();
int findPIDLocation(int searchPID);
void clearResource(int location);
void Allocate(int location);
void updateResource(int location);
int getMsg(int msgQueID, int msgType);

int main(int argc, char *argv[])
{
  int c;

  srand(time(NULL));

  //Memory allocation
  pnum = malloc(sizeof(int));
  user_clockid = malloc(sizeof(int));
  user_sharedID = malloc(sizeof(int));
  child_num = malloc(sizeof(int));

  //Signals
  signal(SIGQUIT, SIG_IGN);
  signal(SIGALRM, ReceivedKill);
  signal(SIGINT, ReceivedKill);
  //signal(SIGCHLD, SIG_IGN);


  while((c = getopt(argc, argv, "ht:")) != -1)
  {
    switch (c)
    {
      case 'h':
        printf("Options:\n");
        printf("[-t]: Change number of seconds until Master will terminate itself and all children\n");
        exit(0);
        break;
      case 't':
        tVal = atoi(optarg);
        break;
      case '?':
        if(optopt == 't')
        {
          exit(1);
        }
        else
        {
          printf("Unknown option entered. Invoke [-h] to see list of commands\n");
          exit(1);
        }
    }
  }

  //Timer
  alarm(tVal);

  //Make keys
  if((key = ftok("./", 'x')) == -1)
  {
    perror("ftok failed in oss clock");
    exit(1);
  }

  if((clockKey = ftok("./", 'y')) == -1)
  {
    perror("ftok failed in oss clock");
    exit(1);
  }

  if((messageKey = ftok("./", 'z')) == -1)
  {
    perror("ftok message key failed");
    exit(1);
  }

  //Allocate shared memory
  if((shm_ID = shmget(key, sizeof(shared_data), IPC_CREAT | 0777)) == -1)
  {
    perror("shmget failed in oss clock");
    exit(1);
  }

  if((clockID = shmget(clockKey, sizeof(clockSim_t), IPC_CREAT | 0777)) == -1)
  {
    perror("shmget failed in oss clock");
    exit(1);
  }

  if((messageID = msgget(messageKey, IPC_CREAT | 0777)) == -1)
  {
    perror("msget failed in oss");
    exit(1);
  }

  //Attach
  printf("Attaching shared memory\n");
  if((sharedStruct = (shared_data *)shmat(shm_ID, 0, 0)) == (void *) -1)
  {
    perror("shmat failed in oss clock");
    exit(-1);
  }

  if((clockStruct = (clockSim_t *)shmat(clockID, 0, 0)) == (void *) -1)
  {
    perror("shmat failed in oss clock");
    exit(-1);
  }

/*
  printf("OSS Clock ID: %d\n", clockID);
  printf("Shared ID: %d\n", shm_ID);
*/


  sprintf(user_clockid, "%d", clockID);
  sprintf(user_sharedID, "%d", shm_ID);

  //Initialize clockKey
  clockStruct->seconds = 0;
  clockStruct->nanoseconds = 0;
  clockStruct->nsTotal = 0;
  clockStruct->runningTotal = 0;

  long long nextGenTime = 0;
  long long spawntime = 0;
  long long startTime = 0;
  //long long nsTotal = 0;

  writelog("STARTING LOG\n");

  initShared();



  while(killFlag != 1)
  {

    if(clockStruct->nsTotal >= nextGenTime)
    {
      //printf("nextGenTime: %llu\n", nextGenTime);
      //printf("nsTotal: %llu\n", nsTotal);
      //sleep(1);
      if(processCount < MAXPROCESSES)
      {
        for(i = 0; i < MAXPROCESSES; i++)
        {
          //Find non running process
          if(sharedStruct->runFlag[i] == 0)
          {
            childSelected = i;
            break;
          }
        }

        printf("Forking\n");
        forkUser(childSelected);
        processCount++;
        printf("Process count: %d\n", processCount);

      }

      nextGenTime = 1 + rand() % 500000000;
      clockStruct->nsTotal = 0;

    }

    //spawntime = (clockStruct->nanoseconds - startTime);



    int increment_ns = rand() % 1001;
    clockStruct->nanoseconds += increment_ns;
    clockStruct->nsTotal += increment_ns;
    clockStruct->runningTotal += increment_ns;
    //sleep(2);


    //updates clock seconds
    if(clockStruct->nanoseconds >= 1000000000)
    {
      printf("Second passed\n");
      clockStruct->seconds++;
      clockStruct->nanoseconds -= 1000000000;
      //sleep(2);
    }



    updatePID(); //Gets when a user dies. Clears its PCB and resources
    updateResource(getMsg(messageID, 2));


  }

  cleanup();

  printf("Program done\n");

  return 0;
}


/////////////////////////////////
//      General functions     //
///////////////////////////////

void ReceivedKill(int signum)
{
  signal(SIGQUIT, SIG_IGN);
  signal(SIGALRM, SIG_IGN);
  signal(SIGINT, SIG_IGN);

  if(signum == SIGINT)
  {
    killFlag = 1;
    fprintf(stderr, "\n**Received CTRL-C. Killing all children**\n\n");
  }
  else if(signum == SIGALRM)
  {
    killFlag = 1;
    fprintf(stderr, "\n**Timer ran out. Killing all child processes**\n\n");
  }

  //Kill users. Oss ignores sigquit
  kill(-getpgrp(), SIGQUIT);
}

void cleanup()
{
  signal(SIGQUIT, SIG_IGN);

  printf("Detaching memory\n");
  shmdt(sharedStruct);
  shmdt(clockStruct);

  printf("Clearing shared memory\n");
  if(shmctl(clockID, IPC_RMID, NULL) == -1)
  {
    fprintf(stderr, "Shared memory remove failed. Please remove manually\n");
    exit(-1);
  }

  if(shmctl(shm_ID, IPC_RMID, NULL) == -1)
  {
    fprintf(stderr, "Shared memory remove failed. Please remove manually\n");
    exit(-1);
  }

  if(msgctl(messageID, IPC_RMID, NULL) == -1)
  {
    perror("msgctl");
    exit(1);
  }

  free(pnum);
  free(user_clockid);
  free(user_sharedID);

}

void childHandler(int sig)
{

}

void forkUser(int childArg)
{
  pid = fork();
  if(pid == -1)
  {
    perror("Failed to fork");
    kill(-getpgrp(), SIGQUIT);
    killFlag = 1;
  }

  if(pid == 0)
  {
    //printf("Executing process\n");
    pid_t myPID = getpid();
    //sharedStruct->child[childArg] = myPID;
    sprintf(child_num, "%d", childArg);
    printf("Executing Child arg %d with PID: %d\n", childArg, myPID);
    execl("./user", "user", user_clockid, user_sharedID, child_num, (char *) 0);
    perror("Could not exec user process");
  }
  else
  {
    //printf("Setting child %d to running\n", childArg);
    sharedStruct->runFlag[childArg] = 1;
    //printf("Child %d runFlag: %d\n", childArg, sharedStruct->runFlag[childArg]);
    //printf("Child %d PID is %d\n", childArg, sharedStruct->child[childArg]);
  }
}

void updatePID()
{

  pid_t returnPID;
  int returnLocation;

  if((returnPID = waitpid(-1, &status, WNOHANG)) > 0)
  {
    printf("Return val: %d\n", returnPID);
    returnLocation = findPIDLocation(returnPID);
    printf("Returned Location: %d\n", returnLocation);
    clearResource(returnLocation);
    processCount--;
    printf("Process count: %d\n", processCount);
  }
  else
  {
    return;
  }
}

void initShared()
{
  initResource();

  for(i = 0; i < MAXPROCESSES; i++)
  {


    sharedStruct->runFlag[i] = 0;
    sharedStruct->waitTime[i] = 0;
    sharedStruct->cpuTime[i] = 0;
  }

  for(i = 0; i < MAXRESOURCES; i++)
  {
    int j;
    for(j = 0; j < MAXPROCESSES; j++)
    {
      sharedStruct->rsd[i].allocated[j] = 0;
      sharedStruct->rsd[i].requested[j] = 0;
      sharedStruct->rsd[i].release[j] = 0;
      sharedStruct->rsd[i].maxClaim[j] = 0;
    }
  }

  writelog("Resources Initialized");


}

void initResource()
{
  int sharedPercentage = rand() % 10 + 15;
  //printf("Shared PERCENTAGE: %d\n", sharedPercentage);
  int numShared = MAXRESOURCES * ((float)sharedPercentage / 100);
  //printf("RANDOM SHARED PERCENTAGE: %d\n", numShared);
  for(i = 0; i < MAXRESOURCES; i++)
  {
    sharedStruct->rsd[i].resource_total = 1 + (rand() % 10);
    sharedStruct->rsd[i].resource_available = sharedStruct->rsd[i].resource_total;

    if(i < (MAXRESOURCES - numShared))
    {
      sharedStruct->rsd[i].shared = 0;
    }
    else
    {
      sharedStruct->rsd[i].shared = 1;
    }
  }

}

void clearResource(int location)
{
  printf("CLEARING CHILD %d RESOURCES\n", location);
  sharedStruct->child[location] = 0;
  sharedStruct->runFlag[location] = 0;
  sharedStruct->waitTime[location] = 0;
  sharedStruct->cpuTime[location] = 0;

  for(i = 0; i < MAXRESOURCES; i++)
  {
    sharedStruct->rsd[i].allocated[location] = 0;
    sharedStruct->rsd[i].requested[location] = 0;
    sharedStruct->rsd[i].release[location] = 0;
  }
}

int findPIDLocation(int searchPID)
{
  for(i = 0; i < MAXPROCESSES; i++)
  {
    if(searchPID == sharedStruct->child[i])
    {
      int clearLocation = i;
      return clearLocation;
    }
  }

  return -1;
}

void Allocate(int location)
{

}

void updateResource(int location)
{
  int i;
  int j;
  if(location == -1)
  {
    return;
  }

  //If location of process returned a location
  if(location >= 0 && location <= 20)
  {
    for(i = 0; i < MAXRESOURCES; i++) //Search for location
    {
      //printf("Searching for Resource %d\n", location);
      //printf("Location: %d\n", location);
      //sleep(1);
      if(sharedStruct->rsd[i].requested[location] > 0) //Find request
      {
        //printf("Found a Request for P%d\n", location);
        sprintf(msgBuff, "Master has detected Process P%d requesting R%d at time: %llu.%llu", location, i, clockStruct->seconds, clockStruct->nanoseconds);
        writelog(msgBuff);
        if(sharedStruct->rsd[i].requested[location] <= sharedStruct->rsd[i].resource_available)
        {
          sprintf(msgBuff, "Master granting Process P%d request R%d at time: %llu.%llu", location, i, clockStruct->seconds, clockStruct->nanoseconds);
          writelog(msgBuff);
          sharedStruct->rsd[i].resource_available -= sharedStruct->rsd[i].requested[location];
          sharedStruct->rsd[i].allocated[location] += sharedStruct->rsd[i].requested[location];
          sharedStruct->rsd[i].requested[location] = 0; //Request was granted, set to 0
        }
      }
      else if(sharedStruct->rsd[i].release[location] > 0)
      {
        sharedStruct->rsd[i].resource_available += sharedStruct->rsd[i].release[location];
        sprintf(msgBuff, "Process P%d releasing R%d:%d at time: %llu.%llu", location, i, sharedStruct->rsd[i].release[location], clockStruct->seconds, clockStruct->nanoseconds);
        writelog(msgBuff);
        sharedStruct->rsd[i].release[location] = 0;
        sharedStruct->rsd[i].allocated[location] = 0;

      }
    }
  }

}

int getMsg(int msgQueID, int msgType)
{

  struct messageBuffer message;


  if(msgrcv(messageID, (void *) &message, sizeof(message.msgText), 3, MSG_NOERROR | IPC_NOWAIT) == -1)
  {
    if(errno != ENOMSG)
    {
      perror("oss msgrc");
      return -1;
    }
  }
  else
  {
    int returnedLocation = atoi(message.msgText);
    //printf("Got Location: %d from message\n", returnedLocation);
    return returnedLocation;
  }

}
