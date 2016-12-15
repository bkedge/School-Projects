//$Author$
//$Date$
//$Log$
//////////

#include "sharedmem.h"


void sigHandler(int signum);
void sendMsg(int queID, int msgType);
void cedeCritical(int queID, int msgType);
void getMsg(int queID, int msgType);
volatile sig_atomic_t killSig = 0;

//Init clock
clockStruct *OssClock;

//Process pid
pid_t userPID;

//Message queue keys and ID's
key_t ossMessageKey;
int ossMessage_ID;

key_t userMessageKey;
int userMessage_ID;

//Clock stuff
int pNum = 0;
long long runtime;
long long clockTime;
long long userTime;

//For critical section
int CS_Done = 0;

int main(int argc, char *argv[])
{
  //Transfer values over
  int sVal_num = atoi(argv[1]);
  int tVal_num = atoi(argv[2]);
  char *filename = argv[3];
  int shm_ID = atoi(argv[4]);
  pNum = atoi(argv[5]);
  int keychecker;
  key_t key;

  //Random init
  srand(time(0) + pNum);

  userPID = getpid();

  //Signal handlers
  signal(SIGINT, SIG_IGN);
  signal(SIGQUIT, sigHandler);

  //printf("Sval: %d, tVal: %d, Filename: %s, shm_ID: %d, Process num: %d\n", sVal_num, tVal_num, filename, shm_ID, pNum);

  //Shared memory Setup
  if((key = ftok("./", 'x')) == -1)
  {
    perror("ftok for slave failed");
    exit(1);
  }

  keychecker = shmget(key, sizeof(clockStruct*), IPC_CREAT | 0777);
  if(keychecker != shm_ID)
  {
    perror("Keys do not match. Error passing key to slave?\n");
    exit(1);
  }

  //Message queues
  if((ossMessageKey = ftok("./", 'y')) == -1)
  {
    perror("ftok for slave failed");
    exit(1);
  }

  if((userMessageKey = ftok("./", 'z')) == -1)
  {
    perror("ftok for slave failed");
    exit(1);
  }

  if((ossMessage_ID = msgget(ossMessageKey, 0777)) == -1)
  {
    perror("msgget");
    exit(1);
  }

  if((userMessage_ID = msgget(userMessageKey, 0777)) == -1)
  {
    perror("msgget");
    exit(1);
  }

  //Attach to clock
  OssClock = (clockStruct*)shmat(shm_ID,0,0);

  //Block
  getMsg(userMessage_ID, 1);

//ENTER CRITICAL SECTION

  //Get runtime. Needs to be out of loop
  runtime = 1 + rand() % 100000;
  printf("User %d runtime is: %llu\n", pNum, runtime);

  //Get time to start at
  clockTime = OssClock->nanoseconds;


  do {


    //sleep(1);
    //sleep(2);

    if(killSig == 1)
    {
      break;
    }

    printf("Seconds: %d, Nanoseconds: %d\n", OssClock->seconds, OssClock->nanoseconds);
    printf("User %d is entering critical section\n", pNum);

    if((userTime = (OssClock->nanoseconds - clockTime)) > runtime) //Runs until time up
    {
      printf("User %d duration up\n", pNum);
      CS_Done = 1;
      //DONE. EXIT CRITICAL SECTION
      sendMsg(ossMessage_ID, 3);
      break;
    }
    else
    {
      //Cede CS
      printf("User %d Ceding critical section\n", pNum);
      cedeCritical(userMessage_ID, 1);
      //sleep(1);
    }

    //Block and wait to re-enter
    getMsg(userMessage_ID, 1);

  } while(CS_Done != 1);

  printf("User %d is dying\n", pNum);

  //Die
  shmdt(OssClock);

  kill(userPID, SIGTERM);
  kill(userPID, SIGKILL);

  exit(0);
  return 0;


}

void sigHandler(int signum)
{
  killSig = 1;
}

//Send message back to OSS thats it done and what time it died
void sendMsg(int queID, int msgType)
{
  struct messageBuffer message;

  message.msgtype = msgType;

  sprintf(message.msgText, "%llu.%llu\n", OssClock->seconds, OssClock->nanoseconds);

  if(msgsnd(queID, (void *) &message, sizeof(message.msgText), IPC_NOWAIT) == -1)
  {
    perror("\nuser send error\n");
  }
}

//Sends message to user queue so other process can enter CS
void cedeCritical(int queID, int msgType)
{
  struct messageBuffer message;

  message.msgtype = msgType;

  sprintf(message.msgText, "Unblock\n");

  if(msgsnd(queID, (void *) &message, sizeof(message.msgText), IPC_NOWAIT) == -1)
  {
    perror("Critical cede error");
  }
}

//Gets message from user queue to unblock and enter CS
void getMsg(int queID, int msgType)
{
  struct messageBuffer message;

  if(msgrcv(queID, (void *) &message, sizeof(message.msgText), msgType, MSG_NOERROR) == -1)
  {
    if(errno != ENOMSG)
    {
      perror("user msgrcv");
    }

  }
  else
  {
    printf("\nMessage received by user %d: %s\n", pNum, message.msgText);
  }
}
