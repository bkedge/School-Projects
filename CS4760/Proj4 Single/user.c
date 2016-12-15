//$Author$
//$Date$
//$Log$
//////////

#include "sharedmem.h"

volatile sig_atomic_t killSig = 0;

void sigHandler(int signum);
void sendMsg(int msgQueID, int msgType);

pid_t userPID;
FILE *fp;
char *filename = "log.out";

clockSim_t *ossClock;
shared_t *userShared;

//Shared memory
key_t sharedKey;
key_t keycheck1;

key_t clockKey;
key_t keycheck2;


//Message queues
key_t messageKey;
int UserMessageID;

//variables
long long runtime;
long long Quant;
long long clocktime;
long long userTime;
long long reQueueTime;

int quantFlag = 0;
int reQueFlag = 0;

int userNum;

int main(int argc, char *argv[])
{
  userNum = atoi(argv[1]);
  int user_shmid = atoi(argv[2]);
  int user_clockid = atoi(argv[3]);

  userPID = getpid();

  signal(SIGINT, SIG_IGN);
  signal(SIGQUIT, sigHandler);

  //Shared memory and queue Setup
  if((sharedKey = ftok("./", 'x')) == -1)
  {
    perror("ftok for user shared failed");
    exit(1);
  }

  keycheck1 = shmget(sharedKey, STRUCT_SIZE, IPC_CREAT | 0777);
  if(keycheck1 != user_shmid)
  {
    perror("Shared key does not match. Error passing shared key?");
    exit(1);
  }

  if((clockKey = ftok("./", 'y')) == -1)
  {
    perror("ftok for user clock failed");
    exit(1);
  }

  keycheck2 = shmget(clockKey, sizeof(clockSim_t), IPC_CREAT | 0777);
  if(keycheck2 != user_clockid)
  {
    perror("Clock key does not match. Error passing shared key?");
    exit(1);
  }

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

  userShared = (shared_t*)shmat(user_shmid,0,0);

  ossClock = (clockSim_t*)shmat(user_clockid,0,0);

/*
  printf("Attached\n");
  printf("Shared ID: %d\n", user_shmid);
  printf("Clock ID: %d\n", user_clockid);
*/

  printf("User Message ID: %d\n", UserMessageID);

  //printf("I got executed, my Process number is: %d\n", userNum);

  //Spinlock
  while(killSig != 1 && userShared->scheduledPID != userShared->pcb[userNum].pid);
  printf("USER %d is running\n", userShared->pcb[userNum].pid);

  runtime = userShared->pcb[userNum].burstTime;

  printf("User %d runtime is %llu\n", userShared->pcb[userNum].pid, runtime);

  Quant = queue0slice;

  clocktime = ossClock->nanoseconds;

  if(runtime > Quant)
  {
    printf("RUNTIME FOR USER: %d WAS GREATER THAN QUANTUM\n", userShared->pcb[userNum].pid);
    quantFlag = 1;
  }

  do
  {
    while(killSig != 1 && userShared->scheduledPID != userShared->pcb[userNum].pid);

    if(killSig == 1)
    {
      break;
    }

    //printf("Time: %llu\n", ossClock->nanoseconds);
    //sleep(1);

    if(reQueFlag == 1)
    {
      printf("Got back into que and will finish quantum\n");
      clocktime = ossClock->nanoseconds;
      while(1)
      {
        if((reQueueTime = (ossClock->nanoseconds - clocktime)) >= runtime)
        {
          printf("User %d finished its re-queue time and will exit\n", userShared->pcb[userNum].pid);
          userShared->scheduleNext = 1;
          userShared->runComplete = 1;
          userShared->scheduledPID = -1;
          userNum = -1;
          sendMsg(UserMessageID, 3);
          break;
        }
      }

      break;
    }

    if(reQueFlag == 0)
    {
      if(runtime > Quant)
      {
        if((userTime = (ossClock->nanoseconds - clocktime)) >= Quant)
        {
          //Finished quantum
          printf("User %d finished quantum and will re-queue\n", userShared->pcb[userNum].pid);
          //sleep(1);
          //userShared->pcb[userNum].burstTime = (runtime - Quant); //Get remaining time
          runtime = (runtime - Quant);
          reQueFlag = 1;


          userShared->scheduleNext = 1;
          userShared->runComplete = 1;
          userShared->scheduledPID = -1;
          sendMsg(UserMessageID, 3);
        }
      }
      else if((userTime = (ossClock->nanoseconds - clocktime)) >= runtime)
      {
        printf("User %d finished before quantum and is exiting\n", userShared->pcb[userNum].pid);
        userShared->scheduleNext = 1;
        userShared->runComplete = 1;
        userShared->scheduledPID = -1;
        userNum = -1;
        sendMsg(UserMessageID, 3);
        break;
      }
    }

    //printf("Re-Looping\n");
    //userShared->scheduledPID = -1;
    //Wait until time to run again
    //while(killSig != 1 && userShared->scheduledPID != getpid());


  } while(killSig != 1);

  if(killSig == 1)
  {
    shmdt(userShared);
    shmdt(ossClock);

    printf("User %d dying\n", userNum);
    kill(userPID, SIGTERM);
    kill(userPID, SIGKILL);
  }

  shmdt(userShared);
  shmdt(ossClock);

  return 0;
}

void sigHandler(int signum)
{
  killSig = 1;
}

void sendMsg(int QueID, int msgType)
{
  struct messageBuffer message;

  message.msgtype = msgType;
  sprintf(message.msgText, "%d", userNum);

  if(msgsnd(QueID, (void *) &message, sizeof(message.msgText), IPC_NOWAIT) == -1)
  {
    sleep(1);
    perror("user send error");
  }
}
