#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

void  ClientProcess(int []);//function protyp

int  main(int  argc, char *argv[])
{
     int    ShmID;//shared memory ID
     int    *ShmPTR;
     pid_t  pid; //key
     int    status;

        if (argc != 11) {//checks for correct number of parameters
					printf("Number Args passed in: %d\n", argc);
          printf("Use: %s #1 #2 #3 #4 #5 #6 #7 #8 #9 #10\n", argv[0]);
          exit(1);
     }
	//function to create shared memory
	//need key
	//need size of shared memory
	//permission as 0666
     ShmID = shmget(IPC_PRIVATE, 10*sizeof(int), IPC_CREAT | 0666);
	//checks the vallue of shmID to check for error
     if (ShmID < 0) {
          printf("*** shmget error (server) ***\n");
          exit(1);
     }
     printf("Server has received a shared memory of four integers...\n");
//gets actual shared ID
     ShmPTR = (int *) shmat(ShmID, NULL, 0);
     if (*ShmPTR == -1) {
          printf("*** shmat error (server) ***\n");
          exit(1);
     }
     printf("Server has attached the shared memory...\n");

    
     ShmPTR[0] = atoi(argv[1]);
     ShmPTR[1] = atoi(argv[2]);
     ShmPTR[2] = atoi(argv[3]);
     ShmPTR[3] = atoi(argv[4]);
		 ShmPTR[4] = atoi(argv[5]);
		 ShmPTR[5] = atoi(argv[6]);
	   ShmPTR[6] = atoi(argv[7]);
		 ShmPTR[7] = atoi(argv[8]);
		 ShmPTR[8] = atoi(argv[9]);
		 ShmPTR[9] = atoi(argv[10]);
	
     printf("Server has filled %d %d %d %d %d %d %d %d %d %d in shared memory...\n",
            ShmPTR[0], ShmPTR[1], ShmPTR[2], ShmPTR[3], ShmPTR[4], ShmPTR[5], ShmPTR[6], ShmPTR[7], ShmPTR[8], ShmPTR[9]);


     printf("Server is about to fork a child process...\n");
     pid = fork();
     if (pid < 0) {
          printf("*** fork error (server) ***\n");
          exit(1);
     }
     else if (pid == 0) {
          ClientProcess(ShmPTR);
          exit(0);
     }

     wait(&status);
     printf("Server has detected the completion of its child...\n");
     shmdt((void *) ShmPTR);
     printf("Server has detached its shared memory...\n");
     shmctl(ShmID, IPC_RMID, NULL);
     printf("Server has removed its shared memory...\n");
     printf("Server exits...\n");
     exit(0);
}

void  ClientProcess(int  SharedMem[])
{
     printf("   Client process started\n");
     printf("   Client found %d %d %d %d %d %d %d %d %d %d in shared memory\n",
                SharedMem[0], SharedMem[1], SharedMem[2], SharedMem[3], SharedMem[4], SharedMem[5], SharedMem[6], SharedMem[7], SharedMem[8], SharedMem[9]);
     printf("   Client is about to exit\n");
}