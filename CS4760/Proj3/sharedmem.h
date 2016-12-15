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

typedef struct clockStruct
{
  long long seconds;
  long long nanoseconds;
} clockStruct;


//For message queue. Template according to book
typedef struct messageBuffer
{
  long msgtype; //Type of message
  char msgText[100]; //Actual message to send. Size is length of message.
} messageBuffer;

#endif
