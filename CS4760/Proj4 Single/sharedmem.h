//$Author$
//$Date$
//$Log$
//////////

#ifndef SHAREDMEM_H
#define SHAREDMEM_H

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

#define MAX_USERS 18

#define STRUCT_SIZE ((sizeof(pcb_t) * 4) + sizeof(shared_t))

//PARAMETERS
long long queue0slice = 25000;
long long queue1slice = 100000;
long long queue2slice = 200000;
long long queue3slice = 400000;

typedef struct
{
  long long totalCpuTime;
  long long totalSysTime;
  long long burstTime;
  long long waitTime;
  int priority;
  pid_t pid;
  int run;
  int done;
  //Other?
} pcb_t;

typedef struct
{
  pid_t scheduledPID;
  int quantum;
  int runComplete;
  int scheduleNext;
  pcb_t pcb[4]; //Process control block x 18
} shared_t;

typedef struct
{
  long long seconds;
  long long nanoseconds;
} clockSim_t;

typedef struct messageBuffer
{
  long msgtype;
  char msgText[100];
} messageBuffer;


#endif
