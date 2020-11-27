#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

// important chmod 700 thread.c | gcc -Wall -D_REENTRANT -pthread -o exec thread.c
// asa se creaza executabilul -pthread -> pentru linux

void *thread_code(void *arg)
{
    int dim;
    int i;
    dim=strlen((char *) arg); // aici puteam sa lucrez direct cu arg, dar
                             // erau prea multe cast-uri si probabil nu se intelegea mai nimic
    char c;                   // asa ca am preferat sa copiez intrun (char *) si sa prelucrez acel char
    char *s=malloc(sizeof(char)*50);
    strcpy(s,arg);
    
    for(i=0;i<dim/2;i++)
    {
      c=s[i];
      s[i]=s[dim-i-1];
      s[dim-i-1]=c;
    }


    return (void *)(s);
}

int main(int argc, char *argv[])
{
   pthread_t th1;
   void *ret1; 
   if(argc != 2)
   {
    printf("Eroare la nr de argumente\n Usage %s string\n",argv[0]);
    exit(1);
   }

   pthread_create( &th1, NULL, thread_code, (void*) argv[1]); //in acest mod se creaza un thread
   // el executa functia (void thread_code) si doar atat
   //un luctu foarte important ca si argument trebuie sa i trimitem intotdeauna
   // ceva de tip (void *) , e foarte folositor pentru ca ii putem face cast mai tarziu
   // adica daca voiam sa prelucrez ceva valori int, la ret specificam ca e int
   // si programul rula fara probleme. Nu e ok sa trimitem altceva ca parametru functiei
   // decat void deoarece (cum am invatat si la OOP) este o superclasa pe care o suprascrie
   // si asa are semnatura (o explicatie mai babeste).
  
   
   printf("Threads created.\n");
   
   pthread_join(th1, &ret1); // asa preluam rezultatul functiei
 
   
   printf("Thread 1 ends returning: %s.\n", (char*)ret1); // asa se printeaza, facand cast ca e un char (*)
   // un lucru foarte important, la thread uri trebuie sa lucram doar cu pointeri!
  
   exit(0);
   
   return 0;
}