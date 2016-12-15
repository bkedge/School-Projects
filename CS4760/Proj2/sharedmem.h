//Author
//$Author: o1-kedge $
//
//Date
//$Date: 2016/09/20 17:29:00 $
//
//Log
//$Log: sharedmem.h,v $
//Revision 1.1  2016/09/20 17:29:00  o1-kedge
//Initial revision
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <getopt.h>
#include <ctype.h>
#include <wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>


//Add states for peterson algo later
int sig_ID;
int killFlag;

typedef enum {idle, want_in, in_cs} state;

typedef struct info_t
{
  state flag[19]; //For max number of processes
  int turn; //Turn of process
  int sharedNum;
}info_t;

extern info_t *shared_info;
