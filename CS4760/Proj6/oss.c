//$Author$
//$Date$
//$Log$
//////////

#include "shared.h"

//General
int i;
int tVal = 20; //Real time seconds till terminate
int sVal = 8;

int freePages = 256;
int systemMem[8];

//Queue
int queueBack = 0;
int queueFront = 0;



//Signals
volatile sig_atomic_t killFlag = 0;
int status;

//Shared memory
key_t key;
int shm_ID;

key_t clockKey;
int clockID;

//User passage arguments
char *user_clockid;
char *user_sharedID;
char *child_num;

//Structures
clockSim_t *clockStruct = NULL;
PCB_t *pcbs[NUMPROCESSES] = { NULL };
//sharedData_t *sharedStruct = NULL;



//FUNCTIONS
void ReceivedKill(int signum);
void cleanup();
PCB_t *initPCB(int index);
void removePCB(PCB_t *pcbs[], int index);
void cleanPCBS(PCB_t *pcbs[]);
void setBit(int v[], int k);
int testBit(int v[], int k);
void clearBit(int v[], int k);

int main(int argc, char *argv[])
{
  int c;//For getopt
  int processCount = 0;
  int usedPCBS[1] = { 0 }; //Bit vector
  int pcbFull = 0;
  int nextPID;
  srand(time(NULL));

  //Memory allocation
  user_clockid = malloc(sizeof(int));
  child_num = malloc(sizeof(int));
  user_sharedID = malloc(sizeof(int));

  //Signals
  signal(SIGQUIT, SIG_IGN);
  signal(SIGALRM, ReceivedKill);
  signal(SIGINT, ReceivedKill);

  while((c = getopt(argc, argv, "ht:s:")) != -1)
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
      case 's':
        sVal = atoi(optarg);
        break;
      case '?':
        if(optopt == 't')
        {
          exit(1);
        }
        else if(optopt == 's')
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
  if((clockKey = ftok("./", 'x')) == -1)
  {
    perror("ftok failed in oss clock");
    exit(1);
  }

  if((key = ftok("./", 'y')) == -1)
  {
    perror("ftok failed in oss clock");
    exit(1);
  }

  //Allocate shared memory
  if((clockID = shmget(clockKey, sizeof(clockSim_t), IPC_CREAT | 0777)) == -1)
  {
    perror("shmget failed in oss clock");
    exit(1);
  }

  /*
  if((shm_ID = shmget(key, sizeof(PCB_t * NUMPROCESSES), IPC_CREAT | 0777)) == -1)
  {
    perror("shmget failed in oss clock");
    exit(1);
  }
  */

  //Attach
  printf("Attaching shared memory\n");
  if((clockStruct = (clockSim_t *)shmat(clockID, 0, 0)) == (void *) -1)
  {
    perror("shmat failed in oss clock");
    exit(-1);
  }

  /*
  if((pcb[NUMPROCESSES] = (PCB_t *)shmat(shm_ID, 0, 0)) == (void *) -1)
  {
    perror("shmat failed in oss clock");
    exit(-1);
  }
  */

  sprintf(user_clockid, "%d", clockID);
  //sprintf(user_sharedID, "%d", shm_ID);

  //Initialize clockStruct
  clockStruct->seconds = 0;
  clockStruct->nanoseconds = 0;
  clockStruct->nsTotal = 0;
  clockStruct->runningTotal = 0;

  //initPCB();

  long long nextGenTime = 0;
  long long spawntime = 0;
  long long startTime = 0;

  writelog("STARTING LOG\n");

  while(killFlag != 1 && clockStruct->runningTotal < 100000000000) //Runs till signal or 100 simulated seconds
  {
    if(clockStruct->nsTotal >= nextGenTime)
    {
      if(processCount <= NUMPROCESSES)
      {
        pcbFull = 1;
        for(i = 0; i < NUMPROCESSES; i++)
        {
          if(testBit(usedPCBS, i) == 0)
          {
            printf("nextPID is %d\n", i);
            nextPID = i;
            pcbFull = 0;
            break;
          }
        }

        if(pcbFull == 1)
        {
          //printf("PCB FULL\n");
        }
        else
        {
          printf("Forking\n");

          pcbs[nextPID] = initPCB(nextPID);
          setBit(usedPCBS, nextPID);

          sprintf(user_clockid, "%d", clockID);
          sprintf(user_sharedID, "%d", pcbs[nextPID]->shm_id);
          sprintf(child_num, "%d", nextPID);
          printf("Process count: %d\n", processCount);
          sleep(2);

          if((pcbs[nextPID]->pid = fork()) == -1)
          {
            perror("fork error");
            kill(-getpgrp(), SIGQUIT);
            killFlag = 1;
          }

          if(pcbs[nextPID] != NULL && pcbs[nextPID]->pid == 0)
          {
            printf("Executing process %d\n", processCount);

            execl("./user", "user", user_clockid, user_sharedID, child_num, (char *) 0);
            perror("Could not exec user process");
          }

          processCount++;
        }
      }

      nextGenTime = 1 + rand() % 500000000;
      clockStruct->nsTotal = 0;

    }

    int increment_ns = rand() % 1001;
    clockStruct->nanoseconds += increment_ns;
    clockStruct->nsTotal += increment_ns;
    clockStruct->runningTotal += increment_ns;

    if(clockStruct->nanoseconds >= 1000000000)
    {
      printf("Second passed\n");
      clockStruct->seconds++;
      clockStruct->nanoseconds -= 1000000000;
    }
  }//End while

  cleanup();

  printf("Program done\n");

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

  //Kill users. Oss ignores sigquit
  kill(-getpgrp(), SIGQUIT);
}

void cleanup()
{
  signal(SIGQUIT, SIG_IGN);

  printf("Detaching memory\n");
  //shmdt(sharedStruct);
  shmdt(clockStruct);

  printf("Clearing shared memory\n");
  if(shmctl(clockID, IPC_RMID, NULL) == -1)
  {
    fprintf(stderr, "Shared memory remove failed. Please remove manually\n");
    exit(-1);
  }

  cleanPCBS(pcbs);

/*
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
  */

  //free(pnum);
  free(child_num);
  free(user_clockid);
  free(user_sharedID);

}

PCB_t *initPCB(int index)
{
  int i;
  int shm_id;
  PCB_t *pcb;

  if ((shm_id = shmget(IPC_PRIVATE, sizeof(PCB_t*), IPC_CREAT | 0755)) == -1) {
		perror("shmget init");
		exit(1);
	}
	if ((pcb = (PCB_t*) shmat(shm_id,0,0)) == (void*)-1) {
		perror("shmat init");
		exit(1);
	}

  pcb->hits = 0;
  pcb->misses = 0;
  pcb->numRefs = 0;
  pcb->completeFlag = 0;
  pcb->waiting = 0;
  pcb->pageSize = (rand() % 18) + 15;
  pcb->shm_id = shm_id;

  for(i = 0; i < pcb->pageSize; i++)
  {
    pcb->PT[i].validBit = 0;
    pcb->PT[i].dirtyBit = 0;
    pcb->PT[i].referenceBit = 0;
    pcb->PT[i].pAddr = -1;
    pcb->PT[i].protectionBit = 0;
  }

  return pcb;
}

void removePCB(PCB_t *pcbs[], int index)
{
  int shm_id;
  int check;

  if(pcbs[index] == NULL)
  {
    return;
  }

  shm_id = pcbs[i]->shm_id;

  shmdt(pcbs[index]);

  if((check = shmctl(shm_id, IPC_RMID, NULL)) == -1)
  {
    perror("Failed shared memory clear of PCB");
  }

  pcbs[index] = NULL;
}

void cleanPCBS(PCB_t *pcbs[])
{
  for(i = 0; i < NUMPROCESSES; i++)
  {
    if(pcbs[i] != NULL)
    {
      removePCB(pcbs, i);
    }
  }
}

void setBit(int v[], int k)
{
	v[(k/32)] |= 1 << (k % 32);
}

void clearBit(int v[], int k)
{
	v[(k/32)] &= ~(1 << (k % 32));
}

int testBit(int v[], int k)
{
	return ((v[(k/32)] & (1 << (k % 32))) != 0);
}
