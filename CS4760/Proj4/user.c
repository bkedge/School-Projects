//$Author$
//$Date$
//$Log$
//////////

#include "sharedmem.h"

volatile sig_atomic_t killSig = 0;

void sigHandler(int signum);
void sendMsg(int msgQueID, int msgType);
int IO();
long long getQuantum();

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
long long totalRuntime = 0;

int quantFlag = 0;
int reQueFlag = 0;

int userNum;

int main(int argc, char *argv[])
{
  userNum = atoi(argv[1]);
  int user_shmid = atoi(argv[2]);
  int user_clockid = atoi(argv[3]);

  userPID = getpid();

  srand(time(0) + userPID);

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


  //Spinlock
  while(killSig != 1 && userShared->scheduledPID != userShared->pcb[userNum].pid);
  printf("USER %d is running\n", userShared->pcb[userNum].pid);

  userShared->pcb[userNum].quantum = getQuantum();


  clocktime = ossClock->nanoseconds;


  printf("User %d Priority: %d, Runtime: %llu\n", userShared->pcb[userNum].pid, userShared->pcb[userNum].priority, userShared->pcb[userNum].quantum);
  //printf("USERNUM: %d\n", userNum);



  do
  {
    while(killSig != 1 && userShared->scheduledPID != userShared->pcb[userNum].pid);



    clocktime = ossClock->nanoseconds;

    if(killSig == 1)
    {
      break;
    }

    userShared->pcb[userNum].quantum = getQuantum();

    runtime = userShared->pcb[userNum].quantum;

    if(IO() == 3)
    {
      printf("GOT IO BLOCK!!!\n");
      userShared->pcb[userNum].quantum = getQuantum();

      userShared->pcb[userNum].quantum = rand() % userShared->pcb[userNum].quantum;
      userShared->pcb[userNum].io = 1;
      printf("IO RUNTIME: %llu\n", userShared->pcb[userNum].quantum);
    }

    while(killSig != 1)
    {

      userTime = (ossClock->nanoseconds - clocktime);


      if((userShared->pcb[userNum].totalCpuTime + userTime) > MaxRunTime)
      {
        userShared->scheduleNext = 1;
        userShared->runComplete = 1;
        userShared->scheduledPID = -1;
        userShared->pcb[userNum].done = 1;
        printf("User %d FINISHED COMPLETELY\n", userShared->pcb[userNum].pid);
        //userShared->pcb[userNum].pid = 0;
        userNum = -1;
        sendMsg(UserMessageID, 3);

        shmdt(userShared);
        shmdt(ossClock);
        exit(0);
        killSig = 1;
      }

      if(userTime > userShared->pcb[userNum].quantum)
      {
        printf("User %d finished quantum\n", userShared->pcb[userNum].pid);
        userShared->scheduleNext = 1;
        userShared->pcb[userNum].totalCpuTime += userTime;
        printf("User %d total time: %llu\n", userShared->pcb[userNum].pid, userShared->pcb[userNum].totalCpuTime);
        userShared->runComplete = 1;
        userShared->scheduledPID = -1;
        sendMsg(UserMessageID, 3);
        break;
      }

    }


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
    //sleep(1);
    perror("user send error");
  }
}

int IO()
{
  return 1 + rand() % 7;
}

long long getQuantum()
{
  if(userShared->pcb[userNum].priority == priorityZero)
  {
    return queue0slice;
  }
  else if(userShared->pcb[userNum].priority == priorityOne)
  {
    return queue1slice;
  }
  else if(userShared->pcb[userNum].priority == priorityTwo)
  {
    return queue2slice;
  }
  else if(userShared->pcb[userNum].priority == priorityThree)
  {
    return queue3slice;
  }
  else
  {
    return queue1slice;
  }
}
