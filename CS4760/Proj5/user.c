//$Author$
//$Date$
//$Log$
//////////

#include "shared.h"

volatile sig_atomic_t killSig = 0;

pid_t userPID;
int userNum;
char msgBuff[150];

clockSim_t *ossClock;
shared_data *sharedUser;

//Shared memory
key_t clockKey;
key_t keycheck2;

key_t sharedKey;
key_t keycheck;

//Message queues
key_t messageKey;
int UserMessageID;

long long totalTime = 0;
long long checkTime = 0;
long long requestTime = 0;



void sigHandler(int signum);
int checkToTerminate();
void sendMsg(int QueID, int msgType);


int main(int argc, char *argv[])
{
  int user_clockid = atoi(argv[1]);
  int user_sharedID = atoi(argv[2]);
  userNum = atoi(argv[3]);

  userPID = getpid();

  int i;
  int j;
  int release;
  int request;


  srand(time(0) + userPID);

  signal(SIGINT, SIG_IGN);
  signal(SIGQUIT, sigHandler);

  //printf("Clock ID: %d\n", user_clockid);

  //Shared memory

  if((clockKey = ftok("./", 'y')) == -1)
  {
    perror("ftok for user clock failed");
    exit(1);
  }

  keycheck2 = shmget(clockKey, sizeof(clockSim_t), IPC_CREAT | 0777);
  if(keycheck2 != user_clockid)
  {
    perror("Clock key does not match. Error passing clock key?");
    exit(1);
  }

  ossClock = (clockSim_t*)shmat(user_clockid,0,0);


  //Shared struct setup
  if((sharedKey = ftok("./", 'x')) == -1)
  {
    perror("ftok for user clock failed");
    exit(1);
  }

  keycheck = shmget(sharedKey, sizeof(shared_data), IPC_CREAT | 0777);
  if(keycheck != user_sharedID)
  {
    perror("User shared key does not match. Error passing shared key?");
    exit(1);
  }

  sharedUser = (shared_data*)shmat(user_sharedID,0,0);

  //Message Queues
  if((messageKey = ftok("./", 'z')) == -1)
  {
    perror("ftok for message in user failed");
    exit(1);
  }

  if((UserMessageID = msgget(messageKey, 0777)) == -1)
  {
    perror("msgget in user");
    exit(1);
  }
/*
  printf("Attached\n");
  printf("Shared ID: %d\n", user_sharedID);
  printf("Clock ID: %d\n", user_clockid);
*/

  sharedUser->child[userNum] = userPID;

  printf("User %d has PID %d\n", userNum, sharedUser->child[userNum]);


  int runCount = 0;

  long long userStart = ossClock->runningTotal;
  long long userCheckStart = ossClock->runningTotal;
  long long randTerm = rand() % 250000000;
  long long userRequestStart = ossClock->runningTotal;
  long long requestBound = rand() % 50000000;



  while(killSig != 1)
  {

    totalTime = ossClock->runningTotal - userStart;
    checkTime = ossClock->runningTotal - userCheckStart;
    requestTime = ossClock->runningTotal - userRequestStart;

    //If running for one second check to see if termination time
    if(totalTime > 1000000000)
    {
      if(checkTime >= randTerm)
      {
        if(checkToTerminate() == 1)
        {
          for(i = 0; i < MAXRESOURCES; i++)
          {
            sharedUser->rsd[i].requested[userNum] = 0;
            sharedUser->rsd[i].release[userNum] = sharedUser->rsd[i].allocated[userNum];
            sendMsg(UserMessageID, 3);
          }
          break;
        }
        else
        {
          userCheckStart = ossClock->runningTotal;
          randTerm = rand() % 250000000;
        }
      }

    }

    //If time for request or release
    if(requestTime > requestBound)
    {

      int choice = rand() % 2;

      if(choice == 1)
      {
        request = rand() % 20;
        //printf("User: %d Requesting resource %d\n", userNum, request);
        sharedUser->rsd[request].requested[userNum] = 1 + rand() % sharedUser->rsd[request].resource_total;
        //printf("User: %d requested resource %d with a total of: %d\n", userNum, request, sharedUser->rsd[request].requested[userNum]);
        sendMsg(UserMessageID, 3);
        while(sharedUser->rsd[request].allocated[userNum] == 0)
        {
          if(killSig == 1)
          {
            break;
          }
        }//Wait till request granted
      }
      else
      {
        int releaseRand = rand() % 20;

        if(sharedUser->rsd[releaseRand].allocated > 0)
        {
          //sharedUser->rsd[releaseRand].resource_available += sharedUser->rsd[releaseRand].allocated[userNum];
          sharedUser->rsd[releaseRand].release[userNum] = sharedUser->rsd[releaseRand].allocated[userNum];
          sendMsg(UserMessageID, 3);
          //sharedUser->rsd[releaseRand].allocated[userNum] = 0;
        }
      }

      userRequestStart = ossClock->runningTotal;
    }

  }

  if(killSig == 1)
  {

    shmdt(ossClock);
    shmdt(sharedUser);

    printf("User %d dying\n", userPID);
    kill(userPID, SIGTERM);
    kill(userPID, SIGKILL);
  }

  shmdt(ossClock);
  shmdt(sharedUser);

  printf("User %d dying\n", userPID);
  return 0;
}

void sigHandler(int signum)
{
  killSig = 1;
}

int checkToTerminate()
{
  int randCheck = 1 + rand() % 5;

  if(randCheck == 2)
  {
    printf("Time to terminte user %d\n", userPID);
    return 1;
  }
  else
  {
    return 0;
  }
}

void sendMsg(int QueID, int msgType)
{
  struct messageBuffer message;

  message.msgtype = msgType;
  sprintf(message.msgText, "%d", userNum);

  if(msgsnd(QueID, (void *) &message, sizeof(message.msgText), IPC_NOWAIT) == -1)
  {
    //sleep(1);
    perror("user send error");
  }
}
