#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
/*

Ipoteza Collatz spune ca plecand de la orice numar n 2 N daca aplicam
urmatorul algoritm
n =
(
n=2 mod (n; 2) = 0
3n + 1 mod (n; 2) 6= 0
seria va converge la 1. Implementat, i un program care foloses,te fork(2)
si testeaza ipoteza generand secvent,a unui numar dat in procesul copil.

*/

void procesfiu(int val)
{
	printf("%d ",val);
	if(val==1)
	exit(0); 

	if(val%2==0)
		procesfiu(val/2);
	else
		procesfiu(3*val+1);

}

void procestata(int val)
{	
	
	pid_t wpid; 
	int status;
	wpid=wait(&status);
	if(WIFEXITED(status))
             printf("\nChild %d ended with code %d\n",wpid,WEXITSTATUS(status));
          else
             printf("\nChild %d ended abnormally\n",wpid);
         exit(0);
}

int main(int argc,char * argv[])
{
	if(argc!=2) // e important de fiecare data sa verificam numarul de argumente
	{
		printf("Eroare la numarul de argumente\n Usage %s number\n",argv[1]);
		exit(1); 
	}


	pid_t child;
	int valoare;
	valoare=atoi(argv[1]); // atoi converteste un string intr-ul int,
							//mai exista si atof care-l converteste intr un float
	
	
	if((child=fork())<0)
	{
		printf("Eroare la creerea procesului\n");
		exit(2);
	}
	else
	if(child==0)
		procesfiu(valoare);
	else
		procestata(valoare);



return 0;
}