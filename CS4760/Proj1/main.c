//Author
//$Author$
//
//Date
//$Date$
//
//Log
//$Log$

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <getopt.h>
#include <unistd.h>
#include "log.h"

//Prototypes
void logError(data_t logEntry, char *arg0, int nVal, char *filename, char *errorMessage);

int main(int argc, char *argv[])
{
  printf("Running Program\n");

  //Structure declarations
  data_t logEntry;
  time_t currentTime;
  char *data;
  char *errorMessage;


  //For -h and -help
  struct option long_options[] =
  {
    {"help", no_argument, 0, 'h'}, {}
  };

  //Getopt declarations
  char *filename = "logfile.txt";
  int nVal = 42;
  int nFlag = 0;
  int hFlag = 0;
  int lFlag = 0;
  char *nTest;
  int c;
  int index;

  //Getopt
  opterr = 0;
  while((c = getopt_long_only(argc, argv, "n:l:h", long_options, NULL)) != -1)
  {
    switch (c)
    {
      case 'n':
          nFlag = 1;
          nVal = atoi(optarg);
        break;
      case 'l':
        lFlag = 1;
        filename = optarg;
        break;
      case 'h':
        hFlag = 1;
        break;
      case '?':
        if(optopt == 'n')
        {
          printf("[-n] option requires an argument\n");
        }
        else if(optopt == 'l')
        {
          printf("[-l] option requires an argument\n");
        }
        else
        {
          printf("Unknown option entered. Invoke [-h] or [-help] to bring up list of commands, [-n] with argument, or [-l] with argument\n");
        }
        return 1;
    }
  }

  if(nFlag == 1)
  {
    errorMessage = "N value ran index out of bounds. Did you malloc() correctly?";
    logError(logEntry, argv[0], nVal, filename, errorMessage);
  }
  else if(lFlag == 1)
  {
    errorMessage = "Your file name did something weird. Make sure you are using correct extensions";
    logError(logEntry, argv[0], nVal, filename, errorMessage);
  }
  else if(hFlag == 1)
  {
    printf("Help Menu:\n");
    printf("Usage: executable [-h or -help] [-n] [-l]\n\n");
    printf("-h and -help: Use these to bring up list of commands\n");
    printf("-n: Allows you to set the value of variable n. Default value is 42\n");
    printf("-l: Allows you to set File name. Default name is logfile.txt\n");
  }
  else
  {
    errorMessage = "No options were entered. Program segfaulted";
    logError(logEntry, argv[0], nVal, filename, errorMessage);
  }

  return 0;
}

//Use this function to be able to do one entry instead of setting up each time
void logError(data_t logEntry, char *arg0, int nVal, char *filename, char *errorMessage)
{
  time_t currentTime;
  currentTime = time(NULL);
  logEntry = (data_t){.time = currentTime, .string = errorMessage};

  FILE *fp;
  fp = fopen(filename, "a");
  if(fp == NULL)
  {
    perror("Error opening file: ");
  }

  fprintf(fp, "Value of N = %d\n", nVal);
  fclose(fp);

  addmsg(logEntry, arg0);
  savelog(filename);
  clearlog();
}
