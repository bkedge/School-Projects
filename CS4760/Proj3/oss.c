//$Author$
//$Date$
//$Log$
//////////
#include "sharedmem.h"

pid_t pid;

//Shared memory and Message queue variables
key_t key;
int shm_ID;

key_t ossMessageKey;
int ossMessage_ID;

key_t userMessageKey;
int userMessage_ID;

//Increment in nanoseconds
const int increment = 64000;

//Clock declaration
clockStruct *OssClock = NULL;

//Max number of proccesses to spawn
const int maxProcesses = 100;

//Proccess counts for sending to user
int process_count = 1;
char *processNum;
int totalProcesses = 0;

int sVal = 5;
int tVal = 20;

int status;

char *logfile = "test.out";
char *user_sVal;
char *user_tVal;
char *user_shmid;

FILE *fp;
char *fileMsg;

volatile sig_atomic_t killFlag = 0;

//For getting pid through MsgQueue
struct msqid_ds tmpbuf;

void ReceivedKill(int signum);
void sendMsg(int msgQueID, int msgType);
void getMsg(int msgQueID, int msgType, FILE *fp);

int main(int argc, char *argv[])
{
  //Processes and general variables
  int c;
  int i;
  int status;

  //Memory allocation
  user_sVal = malloc(sizeof(int));
  user_tVal = malloc(sizeof(int));
  user_shmid = malloc(sizeof(int));
  processNum = malloc(sizeof(int));

  signal(SIGALRM, ReceivedKill);
  signal(SIGINT, ReceivedKill);
  signal(SIGCHLD, SIG_IGN);

  //Command line arguments
  while((c = getopt(argc, argv, "hs:l:t:")) != -1)
  {
    switch (c)
    {
      case 'h':
        printf("Options:\n");
        printf("[-s]: Change max number of slaves spawned\n");
        printf("[-l]: Change name of log file\n");
        printf("[-t]: Change number of seconds until Master will terminate itself and all children\n");
        exit(0);
        break;
      case 's':
        sVal = atoi(optarg);
        break;
      case 'l':
        logfile = optarg;
        break;
      case 't':
        tVal = atoi(optarg);
        break;
      case '?':
        if(optopt == 's')
        {
          exit(1);
        }
        else if(optopt == 'l')
        {
          exit(1);
        }
        else if(optopt == 't')
        {
          exit(1);
        }
        else
        {
          printf("Unknown option entered. Invoke [-h] to see a list of commands\n");
          exit(1);
        }
    }
  }

  //To pass as characters
  sprintf(user_sVal, "%d", sVal);
  sprintf(user_tVal, "%d", tVal);

  //Timer for quitting
  alarm(tVal);

  //Setup shared memory

  //Make our keys
  if((key = ftok("./", 'x')) == -1)
  {
    perror("ftok failed");
    exit(1);
  }

  if((ossMessageKey = ftok("./", 'y')) == -1)
  {
    perror("ftok failed");
    exit(1);
  }

  if((userMessageKey = ftok("./", 'z')) == -1)
  {
    perror("ftok failed");
    exit(1);
  }

  //Allocate the memory
  if((shm_ID = shmget(key, sizeof(clockStruct*), IPC_CREAT | 0777)) == -1)
  {
    perror("shmget could not allocate");
    exit(1);
  }

  if((ossMessage_ID = msgget(ossMessageKey, IPC_CREAT | 0777)) == -1)
  {
    perror("msgget failed");
    exit(1);
  }

  if((userMessage_ID = msgget(userMessageKey, IPC_CREAT | 0777)) == -1)
  {
    perror("msgget failed");
    exit(1);
  }



  printf("Attaching memory\n");
  //Attach
  OssClock = (clockStruct *)shmat(shm_ID, 0, 0);
  OssClock->seconds = 0;
  OssClock->nanoseconds = 0;


  //Debugging lines
  //printf("Values are: Sval: %d, Logfile: %s, Tval: %d, shm_ID: %d\n", sVal, logfile, tVal, shm_ID);

  //printf("ossMessage_ID: %d, userMessage_ID: %d\n", ossMessage_ID, userMessage_ID);

  //Open file
  fp = fopen(logfile, "a");
  if(!fp)
  {
    perror("Error opening file");
  }

  printf("Forking processes\n");

  sprintf(user_shmid, "%d", shm_ID);


  //Process forking
  for(i = 0; i < sVal; i++)
  {

    pid = fork();

    if(pid == -1)
    {
      perror("Failed to fork\n");
      exit(1);
    }

    if(pid == 0)
    {
      sprintf(processNum, "%d", process_count);
                              //arg1     arg2       arg3     arg4        arg5
      execl("./user", "user", user_sVal, user_tVal, logfile, user_shmid, processNum, (char *) 0);
      perror("Could not execute user process\n");
    }

    process_count++;

  }

  printf("Total Processes: %d\n", process_count);

  //Master process
  if(pid > 0)
  {

    //Send to unblock
    sendMsg(userMessage_ID, 1);

    while(totalProcesses <= maxProcesses && killFlag != 1 && OssClock->seconds < 2)
    {
      //sleep(1);
      OssClock->nanoseconds += increment;

      if(OssClock->nanoseconds >= 1000000000)
      {
        OssClock->seconds += 1; //If 1 billion nanoseconds pass then 1 second has passed in our simulated system
        OssClock->nanoseconds -= 1000000000; //Reset
      }
      //wait(&status);
      getMsg(ossMessage_ID, 3, fp);

    }

    printf("Freeing memory\n");
    free(user_sVal);
    free(user_tVal);
    free(user_shmid);
    free(processNum);
  }

  //Deallocate shared memory
  printf("Clearing shared memory and message queues\n");
  if(shmctl(shm_ID, IPC_RMID, NULL) == -1)
  {
    fprintf(stderr, "Shared memory remove failed. Remove manually please\n");
    return -1;
  }

  if(msgctl(ossMessage_ID, IPC_RMID, NULL) == -1)
  {
    perror("msgctl");
    exit(1);
  }

  if(msgctl(userMessage_ID, IPC_RMID, NULL) == -1)
  {
    perror("msgctl");
    exit(1);
  }

  printf("Detaching memory\n");
  shmdt(OssClock);

  fclose(fp);

  printf("Program done\n");
  kill(-getpgrp(), SIGKILL); //Just to be safe


  return 0;
}

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

  kill(-getpgrp(), SIGQUIT);
  //Sends quit signal to entire slave group which will then use their signal handlers to kill themselves

}

void sendMsg(int msgQueID, int msgType)
{
  struct messageBuffer message;

  message.msgtype = msgType;

  sprintf(message.msgText, "Unblock\n");

  if(msgsnd(msgQueID, (void *) &message, sizeof(message.msgText), IPC_NOWAIT) == -1)
  {
    perror("Message send error\n");
  }

}

void getMsg(int msgQueID, int msgType, FILE *fp)
{
  //For child PID
  msgctl(ossMessage_ID, IPC_STAT, &tmpbuf);
  struct messageBuffer message;

  if(msgrcv(msgQueID, (void *) &message, sizeof(message.msgText), msgType, MSG_NOERROR | IPC_NOWAIT) == -1)
  {
    if(errno != ENOMSG)
    {
      perror("oss msgrc");
    }
  }
  else
  {
    //Printing info
    //printf("Child %d is terminating at my time %llu.%llu because it reached %s\n", tmpbuf.msg_lspid, OssClock->seconds, OssClock->nanoseconds, message.msgText);
    fprintf(fp, "Child %d is terminating at my time %llu.%llu because it reached %s\n", tmpbuf.msg_lspid, OssClock->seconds, OssClock->nanoseconds, message.msgText);
    totalProcesses++;
    sendMsg(userMessage_ID, 1);


    if(process_count <= maxProcesses)
    {
      //sleep(1); //Safety
      pid = fork();

      if(pid == -1)
      {
        perror("Failed to fork\n");
        killFlag = 1;
      }

      if(pid == 0)
      {
        sprintf(processNum, "%d", process_count);
        //printf("Exec process number %d\n", process_count);  //Debug
                                //arg1     arg2       arg3     arg4        arg5
        execl("./user", "user", user_sVal, user_tVal, logfile, user_shmid, processNum, (char *) 0);
        perror("Could not execute user process\n");
      }

      printf("Total Processes: %d\n", process_count);
      process_count++;


    }
  }


}
