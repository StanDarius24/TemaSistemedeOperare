#include <sys/mman.h>
#include <sys/stat.h>        
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#define shm_size 4096



int main(int argc, char* argv[])
{ 
char shm_name[] = "myshm" ;
int shm_fd;
shm_fd = shm_open( shm_name , O_CREAT|O_RDWR, S_IRUSR | S_IWUSR);
	
	if(shm_fd<0)
	{
		printf("Eroare\n");
		exit(1);
	}

if(ftruncate(shm_fd,shm_size) == -1){
	printf("Eroare ftruncate\n");
	shm_unlink(shm_name);
	exit(2);
} 

	pid_t child;
	void *ptr;
	ptr=mmap(NULL,shm_size,PROT_WRITE| PROT_READ,MAP_SHARED,shm_fd,0);


	for(int i=0;i<argc-1;i++)
		{
			if((child=fork())<0) 
			{
				printf("Eroare la creerea proceselor\n");
				exit(2);
			}
			if(child==0) 
				{	char *array = malloc(sizeof(char)*4096);
					int val=atoi(argv[i+1]); 
					
					sprintf(array,"%s :",argv[i+1]);
					
					while(val!=1)
					{
						sprintf(array,"%s %d ",array,val);
						
						if(val%2==0)
							val=val/2;
						else
							val=3*val+1;
					}
					sprintf(array,"%s 1\n",array);
					
					
					sprintf(ptr,"%s%s\n",(char *) ptr,array);
					
					ptr += strlen(array);
					
					sleep(2);
					
					printf("DONE Parent %d Me %d \n",getppid(),getpid());
					free(array);

					
					
					exit(0);
				}

		}
		
		printf("Starting parent %d\n",getpid());
		
		int status;
		printf("\n\n");
		for(int i=0;i<argc-1;i++)
			
				wait(&status);
		
	
		
		printf("%s",(char *) ptr);
		
munmap( ptr, shm_size ) ;
shm_unlink(shm_name);
		
		
		printf("Parent ended %d\n",getpid());

	return 0;
}