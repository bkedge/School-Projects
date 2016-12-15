//$Author$
//$Date$
//$Log$
//////////

#ifndef SHARED_H
#define SHARED_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <getopt.h>
#include <ctype.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/sem.h>

#define MAXPROCESSES 18
#define NUMPROCESSES 8
#define MAXFRAMES 32
#define MAXMEMORY 256

typedef struct
{
  unsigned validBit;
  unsigned dirtyBit;
  unsigned referenceBit;
  unsigned pAddr;
  unsigned protectionBit;
} page_t;

typedef struct PCB_t
{

  int waiting;
  int pageSize;
  page_t PT[MAXFRAMES];
  int hits;
  int misses;
  int numRefs;
  int completeFlag;
  int pid;
  int shm_id;
  //sem_t sem;
} PCB_t;

typedef struct sharedData_t
{
  PCB_t pcb[NUMPROCESSES];
} sharedData_t;


typedef struct clockSim_t
{
  long long seconds;
  long long nanoseconds;
  long long nsTotal;
  long long runningTotal;
} clockSim_t;

void writelog(char *msg)
{
  FILE *logfile = fopen("log.out", "a");

  fprintf(logfile, "%s\n", msg);

  fclose(logfile);
}

#endif
