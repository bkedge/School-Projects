//Author
//$Author: o1-kedge $
//
//Date
//$Date: 2016/09/20 17:29:00 $
//
//Log
//$Log: slave.cpp,v $
//Revision 1.1  2016/09/20 17:29:00  o1-kedge
//Initial revision
//

#include "sharedmem.h"

void sigHandler(int signum);
pid_t slavePID;
volatile sig_atomic_t killSignal = 0;
info_t *shared_info;
FILE *fp;
char *fileMsg;

int main(int argc, char *argv[])
{
  srand(time(0) + getpid());
  //Args passed from fork
  int slaveNumber = atoi(argv[1]);
  int num_processes = atoi(argv[2]); //Number of processes
  char *filename = argv[3]; //Filename to write to
  int numWrites = atoi(argv[4]); //Number of writes to do
  int maxSeconds = atoi(argv[5]); //Timeout length
  int shm_ID = atoi(argv[6]);//Get shared mem id from master
  int slaveID = slaveNumber - 1;
  const int n = num_processes;
  int keychecker;
  key_t key;
  slavePID = getpid();
  int i;
  int j;

  //For time stuff
  time_t now;
  struct tm *timeinfo;

  //Ignore signal
  signal(SIGINT, SIG_IGN);


  signal(SIGQUIT, sigHandler);

  //Shared memory Setup
  if((key = ftok("./", 'x')) == -1)
  {
    perror("ftok for slave failed");
    exit(1);
  }

  keychecker = shmget(key, sizeof(info_t*), IPC_CREAT | 0777);
  if(keychecker != shm_ID)
  {
    perror("Keys do not match. Error passing key to slave?\n");
    exit(1);
  }


  printf("Attaching slave %d shared memory\n", slaveNumber);
  shared_info = (info_t*)shmat(shm_ID,0,0);

  for(i = 0; i < numWrites; i++)
  {

    if(killSignal == 1)
    {
      printf("Slave %d received quit signal. Dying\n", (slaveID+1));
      break;
    }


    do
    {
      //Raise flag
      shared_info->flag[slaveID] = want_in;
      j = shared_info->turn; //set local
      while(j != slaveID)//While not my turn
      {
        j = (shared_info->flag[j] != idle) ? shared_info->turn : (j+1) % n;
      }

      //Declare intent to enter CS
      shared_info->flag[slaveID] = in_cs;

      //Check no one else in CS
      for(j = 0; j < n; j++)
      {

        if((j != slaveID) && (shared_info->flag[j] == in_cs))
        {
          break;
        }

      }

    } while((j < n) || (shared_info->turn != slaveID && shared_info->flag[shared_info->turn] != idle));

    shared_info->turn = slaveID;
    time(&now);
    timeinfo = localtime(&now);

    //Entering
    fprintf(stderr, "Process %d is entering critical section at time: %d:%02d\n", (slaveID+1), timeinfo->tm_hour, timeinfo->tm_min);

    /*CRITICAL SECTION*/

    int randnum;
    randnum = rand() % 3;
    printf("Sleeping for %d seconds\n", randnum);
    sleep(randnum);
    //Increment sharedNum
    shared_info->sharedNum += 1;
    //Write message
    fp = fopen(filename, "a");
    if(!fp)
    {
      perror("Error opening file");
      return -1;
    }

    time(&now);
    timeinfo = localtime(&now);
    asprintf(&fileMsg, "File modified by process number %d at time %d:%02d with sharedNum = %d\n", (slaveID+1), timeinfo->tm_hour, timeinfo->tm_min, shared_info->sharedNum);
    fprintf(fp, "%s", fileMsg);


    randnum = rand() % 3;
    printf("Sleeping for %d seconds\n", randnum);
    sleep(randnum);

    //Free up file
    free(fileMsg);
    fileMsg = NULL;
    fclose(fp);
    fp = NULL;

    time(&now);
    timeinfo = localtime(&now);

    //Exiting
    fprintf(stderr, "Process %d is exiting critical section at time: %d:%02d\n\n", (slaveID+1), timeinfo->tm_hour, timeinfo->tm_min);

    /*EXIT CRITICAL SECTION*/

    //Give turn to next process
    j = (shared_info->turn + 1) % n;
    while(shared_info->flag[j] == idle)
    {
      j = (j+1) % n;
    }

    shared_info->turn = j;
    shared_info->flag[slaveID] = idle;


  }

  //Detach slaves memory
  printf("Detaching slave %d shared memory\n\n", slaveNumber);
  if(shmdt(shared_info) == -1)
  {
    perror("Slave couldnt detach shared mem\n");
  }


  kill(slavePID, SIGTERM);
  kill(slavePID, SIGKILL);

  exit(0);
  return 0;
}

void sigHandler(int signum)
{
  killSignal = 1;
}
