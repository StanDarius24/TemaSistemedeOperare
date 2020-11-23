#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
void collatz(int val)
{
	while(val!=1)
	{
		printf("%d ",val);
		if(val%2==0)
			val=val/2;
		else
			val=3*val+1;
	}
	printf("%d ",val);
	printf("\n");
}

int main(int argc, char *argv[])
{	
	pid_t child;
	
	if(argc<2) // testam numarul de argumente
	{
		printf("Eroare la numarul de argumente\n Usage %s number1 number2 ...\n",argv[0]);
		exit(1);
	}

	for(int i=0;i<argc-1;i++)// facem un for pentru fiecare proces argc-1 procese deoarece sunt argc-1 numere
	{
		if((child=fork())<0) // testam daca procesul a fost creat cu succes
		{
			printf("Eroare la creerea proceselor\n");
			exit(2);
		}
		if(child==0) // proces fiu acest cod o sa se execute de argc-1 ori.
			{
				int val=atoi(argv[i+1]); //primul numar incepe de la argv[1] 
				
				printf("%d : ",val);
				
				collatz(val);
				
				printf("DONE Parent %d Me %d \n",getppid(),getpid());
				exit(0);
			}

	}
	// Proces Tata
	printf("Starting parent %d\n",getpid());
	
	int status;
	
	for(int i=0;i<argc-1;i++)
	wait(&status);
	
	printf("Parent ended %d\n",getpid());

	return 0;
}