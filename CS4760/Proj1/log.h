//Author
//$Author$
//
//Date
//$Date$
//
//Log
//$Log$

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <time.h>

typedef struct data_struct
{
  time_t time;
  char *string;
} data_t;

int addmsg(data_t data, char *arg0);
void clearlog(void);
char *getlog(void);
int savelog(char *filename);
