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
#include "log.h"

//Basic template from Excercise 2.13
typedef struct list_struct
{
  data_t item;
  struct list_struct *next;
} log_t;

//Linked list stuff
static log_t *headPtr = NULL;
static log_t *tailPtr = NULL;

//Like book example with add on for executable name
int addmsg(data_t data, char *arg0)
{
  log_t *newnode = NULL;//Holds all the data for an error message
  void *vp = NULL;//Temporary pointer to setup node mem. allocation
  if(NULL == (vp = malloc(sizeof(log_t))))
  {
    perror("Malloc failed (sizeof(log_t))");
    return -1;
  }

  //Setup space for time string
  newnode = (log_t *)vp;
  newnode->item.time = data.time;

  int timeTemp = newnode->item.time;


  //Calculate space for node
  int nodesize = strlen(arg0) + strlen(": Time:000000000 Error: ") + sizeof(timeTemp) + strlen(data.string) + 1;
  if(NULL == (vp = malloc(nodesize)))
  {
    perror("Malloc failed allocating nodesize");
    free(newnode);
    return -1;
  }

  //Set string to pointer
  newnode->item.string = (char *)vp;
  //Fill string
  sprintf(newnode->item.string, "%s: Time: %d000000000 Error: %s",arg0, timeTemp, data.string);
  newnode->next = NULL;


  //Puts string as EOF if its not Empty
  if(headPtr == NULL)
  {
    headPtr = newnode;
  }
  else
  {
    tailPtr->next = newnode;
  }

  tailPtr = newnode;

  return 0;
}

//Clears log
void clearlog(void)
{
  log_t *nextPtr = headPtr;
  //Loop through and clear the log
  while(nextPtr != NULL)
  {
    nextPtr = headPtr->next;
    free(headPtr);
    headPtr = nextPtr;
  }
}

char *getlog(void)
{
  int size = 1;//Set to 1 because of null terminator
  int entryNum = 0; //Number of error logs
  log_t *node = headPtr; //Start at beginning
  char *wholeLog = NULL; //Used to return the entire log

  //Get size
  while(node != NULL)
  {
    entryNum++;
    size += strlen(node->item.string);
    node = node->next;
  }

  //Memory allocation
  wholeLog = malloc(sizeof(char)*(size + 1 + (entryNum * 2)));
  if(wholeLog == NULL)
  {
    perror("Malloc failed: ");
    return NULL;
  }

  //Reset node to beggining
  node = headPtr;

  //Builds the entire log to return
  while(node != NULL)
  {
    wholeLog = strcat(wholeLog, node->item.string);
    wholeLog = strcat(wholeLog, "\n"); //New line
    node = node->next;
  }

  return wholeLog;

}

int savelog(char *filename)
{
  FILE *f;
  char *logPrinter;
  f = fopen(filename, "a");
  if(f == NULL)
  {
    perror("Error opening file: ");
    return -1;
  }

  //Get the log to print
  logPrinter = getlog();

  if(logPrinter == NULL)
  {
    printf("Empty Log\n");
    return 0;
  }

  fprintf(f, "%s\n", logPrinter);
  fclose(f);
  return 0;
}
