#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
/*

1. Creati un proces nou folosind fork(2) si afisati fisierele din directorul
curent cu ajutorul execve(2). Din procesul init, initial afisati pid-ul propriu
si pid-ul copilului. De exemplu:
$ . / f o r k l s
My PID=41875 , Chi ld PID=62668
Make f i l e c o l l a t z . c f o r k l s . c so􀀀lab 􀀀4. tex
c o l l a t z f o r k l s n c o l l a t z . c
Chi ld 62668 f i n i s h e d

*/


void procescopil()
{	
	char *list[]={"ls",NULL}; 
	execve("/bin/ls",list,NULL);
	exit(0); // -> important aici, avem nevoie in codul copil de un apel exit()
}			// in caz contrar, copilul o sa execute si codul scris de parinte

/*
		Exista o familie de functii exec.
		int execl(const char *pathname, const char *arg, ...
                        (char  *) NULL );
       int execlp(const char *file, const char *arg, ...
                        (char  *) NULL );
       int execle(const char *pathname, const char *arg, ...
                       , (char *) NULL, char *const envp[] );
       int execv(const char *pathname, char *const argv[]);
       int execvp(const char *file, char *const argv[]);
       int execvpe(const char *file, char *const argv[],
                       char *const envp[]);
		dintre toate doar execve() e functie de sistem, restul sunt de biblioteca
		si se gasesc in #include <unistd.h>
		in terminal cu comanda man exec o sa gasesti o lista mai detaliata despre
		cum se apeleaza si ce fac.E important pe viitor sa o citesti, eu o sa ti fac 
		un rezumatm cu ce cred eu ca e mai important
	
		exec[l] -> argumentele programului sunt date ca LISTA(de unde si l-ul) terminala cu null 
		execl[p] -> programul e cautat (si) in caile specificate de $PATH
		execlp[v] -> argumentele programului sunt date ca VECTOR terminat cu NULL
		exec[e] -> Environment-ul (variabilele de mediu) programul va fi cel dat ca argument apelului exec
*/





void procestata()
{	
	pid_t wpid; // e important sa nu folosim variabile globale pentru pid_t
	int status;
	wpid=wait(&status); // cu un man wait in terminal putem observa bibliotecile de care 
						//avem nevoie pentru a folosi functia
	/*
	   #include <sys/types.h>
       #include <sys/wait.h>

       pid_t wait(int *wstatus); -> returneaza pid-ul copilului

       pid_t waitpid(pid_t pid, int *wstatus, int options);

       int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options);
	*/
	
	printf("\nMy PID = %d,	,Child PID=%d\n",getpid(),wpid); // getpid() -> returneaza pid-ul curent
															// getppid() -> returneaza pid-ul tatalui
	if(WIFEXITED(status))
             printf("\nChild %d ended with code %d\n",wpid,WEXITSTATUS(status));
          else
             printf("\nChild %d ended abnormally\n",wpid);
    /*
    e f important sa cunoastem starea in care se afla procesul,
    asa ca o sa apelam WIFEXITED(status) pentru a verifica daca procesul s a terminat cu succes
    iar cu WEXITSTATUS -> returneaza valoarea cu care s a terminat procesul, la noi 0 deoarece am facut 
    un exit(0)-> putem avea aici doar int deci in cazul in care in copil faceam un exit(4) -> returna 4;
	WIFEXITED(status)
              returns  true  if  the  child  terminated  normally,  that is, by calling exit(3) or
              _exit(2), or by returning from main().

       WEXITSTATUS(sstatus)
              returns the exit status of the child.  This consists of the least significant 8 bits
              of  the status argument that the child specified in a call to exit(3) or _exit(2) or
              as the argument for a return statement in main().  This  macro  should  be  employed
              only if WIFEXITED returned true.
	*/

    exit(0);
}	

int main(int argc, char * argv[])  // in argc avem numarul de argumente citite din linia de comanda
{								   // luam in considerare ca la generarea executabilului de ex
								   // gcc -Wall -o exec ex1.c. Primul argument este exec urmat 
								   // de datele pe care le trimitem.
 pid_t child;// -> pid_t este un tip de date si e folosit pentru a identifica id-urile de proces

if((child=fork())<0)
{
	printf("Eroare la creerea procesului\n");
	exit(1);
}
else
	if(child==0) //proces copil
		procescopil(); // pentru a fi mai usor de urmarit, activitatea procesului copil se va
	else					//desfasura in interiorul functiei.
		procestata();	//la fel si pentru tata
return 0;
}