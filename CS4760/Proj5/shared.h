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

#define MAXPROCESSES 18
#define MAXRESOURCES 20

typedef struct
{
  long long seconds;
  long long nanoseconds;
  long long nsTotal;
  long long runningTotal;
} clockSim_t;

typedef struct
{
  int resource_total;
  int resource_available;
  int shared;
  int allocated[MAXPROCESSES];
  int requested[MAXPROCESSES];
  int release[MAXPROCESSES];
  int maxClaim[MAXPROCESSES];
} resource_descriptor;

typedef struct
{
  int runFlag[MAXPROCESSES];
  int waitTime[MAXPROCESSES];
  long long cpuTime[MAXPROCESSES];
  resource_descriptor rsd[MAXRESOURCES];
  pid_t child[MAXPROCESSES];
} shared_data;

typedef struct messageBuffer
{
  long msgtype;
  char msgText[100];
} messageBuffer;

void writelog(char *msg)
{
  FILE *logfile = fopen("log.out", "a");

  fprintf(logfile, "%s\n", msg);

  fclose(logfile);
}

#endif
