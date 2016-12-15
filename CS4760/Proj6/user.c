//$Author$
//$Date$
//$Log$
//////////

#include "shared.h"

volatile sig_atomic_t killSig = 0;

char msgBuff[150];

PCB_t *pcb = NULL;
clockSim_t *clockStruct;



//FUNCTIONS
void sigHandler(int signum);

int main(int argc, char *argv[])
{

  int i;
  int user_clockid = atoi(argv[1]);
  int user_sharedID = atoi(argv[2]);
  int child_num = atoi(argv[3]);

  pid_t userPID = getpid();

  srand(time(NULL));

  signal(SIGINT, SIG_IGN);
  signal(SIGQUIT, sigHandler);

  if((pcb = (PCB_t *) shmat(user_sharedID,0,0)) == (void*) -1)
  {
    perror("PCB attach user");
  }

  if((clockStruct = (clockSim_t *) shmat(user_clockid,0,0)) == (void*) -1)
  {
    perror("Clock attach user");
  }

  while(killSig != 1 && pcb->completeFlag != 1)
  {

  }

  shmdt(pcb);
  shmdt(clockStruct);

  return 0;
}

void sigHandler(int signum)
{
  killSig = 1;
}
