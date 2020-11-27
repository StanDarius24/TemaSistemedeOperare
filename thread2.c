#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// se creaza executabilul cu 

//  chmod 700 thread2.c | gcc -Wall -D_REENTRANT -pthread -o exec thread2.c

typedef struct argumente{
	int arg1;				// pentru a trimite 2 argumente pentru functia thread_code
	int arg2;				// trebuie sa creem o structura prin care o sa facem cast 
}argumente;					// mai tarziu, acum putem observa puterea tipului (void *)
							// care practic poate fi orice.
void *thread_code(void *arg)
{
    struct argumente *args= arg; // facem cast la argumentul transmis

    int val = args->arg1 * args ->arg2;  // argumentul transmis stim ca e de tip argumente
    									// si atunci are 2 valori in el
    // respectam formula si inmultim valorile

    return (void *) ((int) val); // transmitem parametrul
    //care e de tip (void *) dar trebuie tratat ca un int (int) val
}


int main(int argc, char *argv[])
{
   pthread_t th1;
   void *ret1; 
   
   int a[3][3]={
   	{1,2,1},
   	{5,4,0},
   	{4,1,2}
   };			// e cam complicat sa citim de fiecare data matricile de la tastatura

    int b[3][3]={
   	{2,2,1},
   	{2,3,0},
   	{5,0,1}
   };			// si dupa aprerea mea important aici e sa observam functionalitatea thread-urilor
   				// nu sa repetam matricile invatate in anul 1 la CP

   int res[3][3]={  // trebuie sa fie 11 8 2
								//    18 22 5
								//    20 11 6 -> pentru valorile date
   	{0,0,0},
   	{0,0,0},
   	{0,0,0}
   };

	int i,j,k;
	struct argumente *val=malloc(sizeof(struct argumente)); // dupa cum ziceam avem nevoie de o structura
  for(i=0;i<3;i++)
	for(j=0;j<3;j++)
			for(k=0;k<3;k++)
			{

				val->arg1=a[i][k];  // punem valorile in structura a i,k * b k,j
				val->arg2=b[k][j];
		   pthread_create( &th1, NULL, thread_code, (void*) val); // creem un fir de executie
		   // care sa execute functia thread_code cu argumentele date
		   
		 
		   
		   pthread_join(th1, &ret1); // preluam valoarea 
		   res[i][j]+=(int)ret1; // o calculam dupa formula
  
}   
   
	 for(i=0;i<3;i++)
		{
			for(j=0;j<3;j++)
			printf("%d ",res[i][j]);
			printf("\n");
		}
 // printam rezultatul
   
   exit(0);
   
   return 0;
}