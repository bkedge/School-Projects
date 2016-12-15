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

#define STRUCT_SIZE ((sizeof(pcb_t) * 18) + sizeof(shared_t))

//PARAMETERS
long long queue0slice = 25000000;
long long queue1slice = 10000000;
long long queue2slice = 20000000;
long long queue3slice = 40000000;

const long long totalSeconds = 25; //Amount of simulated seconds for program to run

long long MaxRunTime = 70000000;


int priorityZero = 0;
int priorityOne = 1;
int priorityTwo = 2;
int priorityThree = 3;

typedef struct
{
  long long totalCpuTime;
  long long runTime;
  long long quantum;
  int io;
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
  long long totalSysTime;
  //int quantum;
  int runComplete;
  int scheduleNext;
  int location;
  pcb_t pcb[18]; //Process control block x 18
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
