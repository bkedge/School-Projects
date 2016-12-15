//Author
//$Author: o1-kedge $
//
//Date
//$Date: 2016/09/20 17:29:00 $
//
//Log
//$Log: master.cpp,v $
//Revision 1.1  2016/09/20 17:29:00  o1-kedge
//Initial revision
//

#include "sharedmem.h"

//Global
pid_t proc_pid[20];
pid_t pid;

//For slave parameters. Logfile is already character.
char *slave_sVal;
char *slave_iVal;
char *slave_tVal;
char *slave_num;
char *slave_shmid;

int MAX_NUM_PROC = 20;

info_t *shared_info = NULL;



void ReceivedKill(int signum);

int main(int argc, char *argv[])
{
  int process_count = 1;
  int c;
  int i = 0; //Because initialization is only allowed in C99?
  int sVal = 5; //Value for slave processes. Default 5
  char *logfile;
  logfile = "test.out";
  int iVal = 3; //Value for slave writes to a file. Default 3.
  int tVal = 20; //Value for time in second till master terminates. Default 20 //Holds value of processes not to go over
  int status;
  int result;

  pid_t ppid;

  sig_ID = 0;

  int shm_ID;
  key_t key;

  signal(SIGALRM, ReceivedKill);//For timeout
  signal(SIGINT, ReceivedKill); //Gets signal from timeout or CTRL-C


  //Allocate room for integer values/
  slave_sVal = malloc(sizeof(int));
  slave_iVal = malloc(sizeof(int));
  slave_tVal = malloc(sizeof(int));
  slave_num = malloc(sizeof(int));
  slave_shmid = malloc(sizeof(int));


  //Parse command line options. Dont need getopt_long_only because no -help
  while((c = getopt(argc, argv, "hs:l:i:t:")) != -1)
  {
    switch(c)
    {
      case 'h':
        printf("Options:\n");
        printf("[-s]: Change number of slaves\n");
        printf("[-l]: Change name of log file\n");
        printf("[-i]: Change number of writes to file per slave\n");
        printf("[-t]: Change number seconds until Master will terminate itself\n");
        exit(0);
        break;
      case 's':
        sVal = atoi(optarg);
        break;
      case 'l':
        logfile = optarg;
        break;
      case 'i':
        iVal = atoi(optarg);
        break;
      case 't':
        tVal = atoi(optarg);
        break;
      case '?':
        if(optopt == 's')
        {
          exit(0);
        }
        else if(optopt == 'l')
        {
          exit(0);
        }
        else if(optopt == 'i')
        {
          exit(0);
        }
        else if(optopt == 't')
        {
          exit(0);
        }
        else
        {
          printf("Unknown option entered. Use [-h] to see list of commands\n");
          exit(0);
        }
    }
  }

  //Store arguments as characters to pass to slave
  sprintf(slave_sVal, "%d", sVal);
  sprintf(slave_iVal, "%d", iVal);
  sprintf(slave_tVal, "%d", tVal);

  alarm(tVal);

  //Setup shared memory

  //Make our key
  if((key = ftok("./", 'x')) == -1)
  {
    perror("ftok failed");
    exit(1);
  }

  //Allocate the memory
  if((shm_ID = shmget(key, sizeof(info_t*), IPC_CREAT | 0777)) == -1)
  {
    perror("shmget could not allocate");
    exit(1);
  }

  //Attach
  shared_info = (info_t*)shmat(shm_ID, 0, 0);
  for(i = 0; i < 19; i++)
  {
    shared_info->flag[i] = idle;
  }
  shared_info->sharedNum = 0;
  shared_info->turn = 0;

  shmdt(shared_info);



  //STARTS FORKING OF PROCESSES
  for(i = 0; i < sVal; i++)
  {

    //Print argument of slave number to char string
    sprintf(slave_num, "%d", (i+1));



    //If process count reaches 20 break loop
    if(process_count > 19)
    {
      printf("\n**REACHED 20 PROCESSES. STOPPING FORKING**\n\n");
      break;
    }
    process_count++;

    //Standard fork
    pid = fork();

    //Standard Error checking
    if(pid == -1)
    {
      perror("Failed to fork");
      exit(1);
    }

    //Spawn the slaves
    if(pid == 0)
    {
      proc_pid[i] = pid;
      pid_t grpID = getpgrp();

      if(sVal > 19)
      {
        sprintf(slave_sVal, "%d", 19);
      }

      sprintf(slave_shmid, "%d", shm_ID);

      execl("./slave", "slave", slave_num, slave_sVal, logfile, slave_iVal, slave_tVal, slave_shmid, (char *) 0);
      perror("Master process could not execute slave");

    }


  } //End for loop

  //Parent process
  if(pid > 0)
  {
    
    while(process_count != 0)
    {
      wait(&status);
      process_count--;
    }

    //Free memory to be safe
    printf("Freeing memory\n");
    free(slave_iVal);
    free(slave_sVal);
    free(slave_tVal);
    free(slave_num);
    free(slave_shmid);

  }



  //Deallocate shmget
  printf("Clearing shared memory\n");
  if(shmctl(shm_ID, IPC_RMID, NULL) == -1)
  {
    fprintf(stderr, "Shared memory remove failed. Remove manually please\n");
    return -1;
  }

  printf("\nProgram done\n");
  return 0;
}


void ReceivedKill(int signum)
{
  //Ignore Signals
  //NEED THIS OR INFINITE LOOP HAPPENS AND YOU CAN'T CTRL-C. **BEWARE**
  signal(SIGQUIT, SIG_IGN); //Ignore exit from slave. Need this or Master process wont finish.
  signal(SIGALRM, SIG_IGN);
  signal(SIGINT, SIG_IGN);

  if(signum == SIGINT)
  {
    fprintf(stderr, "\n**Received CTRL-C. Killing all child processes**\n\n");
  }
  else if(signum == SIGALRM)
  {
    fprintf(stderr, "\n**Timer ran out. Killing all child processes**\n\n");
  }

  kill(-getpgrp(), SIGQUIT);
  //Sends quit signal to entire slave group which will then use their signal handlers to kill themselves

}
