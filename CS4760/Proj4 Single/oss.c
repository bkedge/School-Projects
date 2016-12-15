//$Author$
//$Date$
//$Log$
//////////

#include "sharedmem.h"

#define QUEUE_SIZE 18

//PARAMETERS

long long BURST = 35000;

int tVal = 20;
int i;
int processLocation;
int pcbFullFlag = 0;
FILE *fp;
char *filename = "log.out";
char buffer[100] = "";

//To pass to user
char *pnum;
char *user_shmid;
char *user_clockid;

//Queues
pid_t pidQueue[QUEUE_SIZE];
int front = 0;
int rear = -1;
int itemcount = 0;

pid_t pidQueue1[QUEUE_SIZE];
int front1 = 0;
int rear1 = -1;
int itemcount1 = 0;

pid_t pidQueue2[QUEUE_SIZE];
int front2 = 0;
int rear2 = -1;
int itemcount2 = 0;

pid_t pidQueue3[QUEUE_SIZE];
int front3 = -1;
int rear3 = -1;
int itemcount3 = -1;


//Constants
const int maxProcesses = 18;

//Shared memory and keys
key_t key;
int shm_ID;

key_t clockKey;
int clockID;

key_t messageKey;
int messageID;

//Structure delcare
shared_t *sharedStruct = NULL;
clockSim_t *clockStruct = NULL;

//Signal handling
volatile sig_atomic_t killFlag = 0;

//Get pid through message queue
struct msqid_ds tmpbuf;

//General variables
int processCount;
pid_t mypid;
pid_t ossPID;


//FUNCTIONS
void ReceivedKill(int signum);
void cleanup();
void init_PCB(int proc_num);
void forkUser();
int pcbFull();
pid_t scheduleProcess();
int getMsg(int msgQueID, int msgType);
int getTurn();
void updateQueue(int locationPID);

//Queue functions
pid_t peek();
int isEmpty();
int isFull();
int size();
void insert(pid_t data);
pid_t removeData();


int main(int argc, char *argv[])
{
  int c;
  processCount = 0;

  srand(time(NULL));

  //Memory Allocate
  pnum = malloc(sizeof(int));
  user_shmid = malloc(sizeof(int));
  user_clockid = malloc(sizeof(int));

  signal(SIGQUIT, SIG_IGN);
  signal(SIGALRM, ReceivedKill);
  signal(SIGINT, ReceivedKill);
  signal(SIGCHLD, SIG_IGN);

  while((c = getopt(argc, argv, "ht:")) != -1)
  {
    switch (c) {
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

  alarm(tVal);

  //Make keys
  if((key = ftok("./", 'x')) == -1)
  {
    perror("ftok failed in oss");
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

  //Allocate memory
  if((shm_ID = shmget(key, STRUCT_SIZE, IPC_CREAT | 0777)) == -1)
  {
    perror("shmget failed in oss");
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
  printf("Attaching memory\n");
  if((sharedStruct = (shared_t *)shmat(shm_ID, 0, 0)) == (void *) -1)
  {
    perror("shmat failed in oss");
    exit(-1);
  }

  if((clockStruct = (clockSim_t *)shmat(clockID, 0, 0)) == (void *) -1)
  {
    perror("shmat failed in oss clock");
    exit(-1);
  }

  ossPID = getpid();

  //printf("Memory ID: %d\n", shm_ID);
  //printf("Clock ID: %d\n", clockID);
  //Print memory ID's to pass
  sprintf(user_shmid, "%d", shm_ID);
  sprintf(user_clockid, "%d", clockID);

  //printf("Memory size: %d\n", STRUCT_SIZE);
  //printf("OSS PID: %d\n", ossPID);
  printf("Message ID: %d\n", messageID);


  clockStruct->seconds = 0;
  clockStruct->nanoseconds = 0;


  //Open file
  fp = fopen(filename, "w");
  if(!fp)
  {
    perror("File open error");
    exit(1);
  }

  //Inititate pcb
  for(i = 0; i < 18; i++)
  {
    init_PCB(i);
  }


  long long nextGenTime = 0;
  long long timeToFork;
  int processGenerated = 0;

  //Initialize for first schedule
  sharedStruct->scheduleNext = 1;
  sharedStruct->runComplete = 0;


  /////////////////////MAIN LOOP/////////////////////////
  while(killFlag != 1)
  {
    if((pcbFull() != 1) && (clockStruct->seconds >= nextGenTime))
    {
      forkUser();
      processCount++;
      printf("Process count: %d\n", processCount);
      //printf("Inititated PCB\n");
      //processGenerated = 1;

      //Sets time until next spawn
      nextGenTime = clockStruct->seconds;
      //printf("nextGenTime before: %llu\n", nextGenTime);
      nextGenTime += rand() % 3;
      //printf("nextGenTime after: %llu\n", nextGenTime);

    }

    /*
    if(pcbFull() == 1)
    {
      printf("processCount reached\n");

      printf("itemcount: %d\n", itemcount);

      printf("Queue:   ");
      while(isEmpty() != 1)
      {
        pid_t p = removeData();
        printf("%d  ", p);
      }
      printf("\n");


      sleep(5);
    }
    */

    //Schedule process


    if(sharedStruct->scheduleNext == 1 && (isEmpty() != 1))
    {
      if((sharedStruct->scheduledPID = scheduleProcess()) != -2)
      {
        for(i = 0; i < 18; i++)
        {

          if(sharedStruct->scheduledPID == sharedStruct->pcb[i].pid)
          {
            //printf("**Found location of queue**\n");
            queueLocation = i;
            break;
          }
        }
        fprintf(fp, "OSS: Dispatching process with PID %d from queue %d at time %llu.%llu\n", sharedStruct->scheduledPID, sharedStruct->pcb[queueLocation].priority, clockStruct->seconds, clockStruct->nanoseconds);
        printf("Scheduled user %d\n", sharedStruct->scheduledPID);
        sharedStruct->scheduleNext = 0;
      }
    }



    //Increment clock
    int incrememnt_ns = rand() % 1001; // 0-1000
    clockStruct->nanoseconds += incrememnt_ns;
    //printf("Nanoseconds: %llu\n", clockStruct->nanoseconds);
    //sleep(1);

    //updates clock seconds
    if(clockStruct->nanoseconds >= 1000000000)
    {
      printf("Second passed\n");
      clockStruct->seconds++;
      clockStruct->nanoseconds -= 1000000000;
      //sleep(2);
    }

    //Get return status of process and update scheduler queues
    //if(sharedStruct->runComplete == 1)
    //{
      //printf("Updating Queues\n");
      //sleep(2);
      //updateQueue(getTurn());

      updateQueue(getMsg(messageID, 2));
    //}


    //printf("Time in Sec: %llu NanoSec: %llu\n", clockStruct->seconds, clockStruct->nanoseconds);
    //sleep(5);
  }



  //Clean
  cleanup();


  printf("Program done\n");
  return 0;
}//End main


/////////////////////////////////
//      General functions     //
///////////////////////////////

void ReceivedKill(int signum)
{
  signal(SIGQUIT, SIG_IGN);
  signal(SIGALRM, SIG_IGN);
  signal(SIGINT, SIG_IGN);

  //sleep(1);
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
  if(shmctl(shm_ID, IPC_RMID, NULL) == -1)
  {
    fprintf(stderr, "Shared memory remove failed. Please remove manually\n");
    exit(-1);
  }

  if(shmctl(clockID, IPC_RMID, NULL) == -1)
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
  free(user_shmid);
  free(user_clockid);

  fclose(fp);

}

void init_PCB(int proc_num)
{
  //Setup pcb
  sharedStruct->pcb[proc_num].totalCpuTime = 0;
  sharedStruct->pcb[proc_num].totalSysTime = 0;
  sharedStruct->pcb[proc_num].burstTime = 0;
  sharedStruct->pcb[proc_num].priority = 0;
  sharedStruct->pcb[proc_num].run = 0;
  sharedStruct->pcb[proc_num].done = 0;
  sharedStruct->pcb[proc_num].pid = 0;
}

void forkUser()
{
  processLocation = -1;

  //Loop through array and find an open spot. Initiate PCB slot
  for(i = 0; i < 18; i++)
  {
    if(sharedStruct->pcb[i].pid == 0)
    {
      processLocation = i;
      init_PCB(processLocation);
      break;
    }
  }

  if(processLocation != -1)
  {
    mypid = fork();

    if(mypid == -1)
    {
      perror("Failed to fork");
      killFlag = 1;
    }

    if(mypid == 0)
    {
      sprintf(pnum, "%d", processLocation);
      sharedStruct->pcb[processLocation].pid = getpid();
      sharedStruct->pcb[processLocation].burstTime = rand() % BURST;
      //printf("User location: %d PID: %d, Burstime: %llu\n", processLocation, sharedStruct->pcb[processLocation].pid, sharedStruct->pcb[processLocation].burstTime);
                             //arg1,    arg2,      arg3
      execl("./user", "user", pnum, user_shmid, user_clockid, (char *) 0);
      perror("Could not exec user process");
    }
  }

  if(processLocation != -1)
  {
    while(sharedStruct->pcb[processLocation].pid <= 1);
    fprintf(fp, "OSS: Generating process with PID %d and putting it in queue 0 at time %llu.%llu\n", sharedStruct->pcb[processLocation].pid, clockStruct->seconds, clockStruct->nanoseconds);
    insert(sharedStruct->pcb[processLocation].pid);
  }

}

int pcbFull()
{
  for(i = 0; i < 18; i++)
  {
    if(sharedStruct->pcb[i].pid == 0)
    {
      return 0;
    }
  }

  return 1;
}


pid_t scheduleProcess()
{
  pid_t frontPID;
  if(isEmpty() != 1)
  {
    frontPID = removeData();
    return frontPID;
  }
  else
  {
    return -2;
  }
}

int getMsg(int msgQueID, int msgType)
{
  //msgctl(messageID, IPC_STAT, &tmpbuf);
  struct messageBuffer message;

  //while(sharedStruct->scheduledPID != -1);

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
    printf("Got PID: %d from message\n", returnedLocation);
    return returnedLocation;
  }

}

int getTurn()
{
  //while(sharedStruct->runComplete != 1);

  int processSentBack = getMsg(messageID, 2);

  return processSentBack;
}

void updateQueue(int locationPID)
{
  //If process finished, don't need to add to queue
  if(locationPID == -1)
  {
    printf("process finished\n");
    return;
  }

  //Get pid of process that didnt finish
  pid_t returnedPID = sharedStruct->pcb[locationPID].pid;

  if(returnedPID != 0)
  {
    printf("Updating Que with PID: %d\n", returnedPID);
    insert(returnedPID);
    //insert(sharedStruct->pcb[locationPID].pid);
  }
  else
  {
    return;
  }
}

////////////////////////////////////
//            QUEUES             //
//////////////////////////////////
pid_t peek()
{
  return pidQueue[front];
}

int isEmpty()
{
  if(itemcount == 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }

}
int isFull()
{
  if(itemcount == QUEUE_SIZE)
  {
      return 1;
  }
  else
  {
    return 0;
  }
}
int size()
{
  return itemcount;
}
//Puts data at end of queue
void insert(pid_t data)
{
  if(isFull() != 1)
  {
    if(rear == QUEUE_SIZE - 1)
    {
      rear = -1;
    }

    printf("Adding PID: %d to queue\n", data);
    pidQueue[++rear] = data;
    itemcount++;
    printf("Item count after insert: %d\n", itemcount);
  }
}

//Pops data
pid_t removeData()
{
  pid_t data = pidQueue[front++];

  if(front == QUEUE_SIZE)
  {
    front = 0;
  }
  itemcount--;
  return data;
}
