#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 100

int Record[2*MAX];
int nextFree = 0;


void init(void)
  {
  int i;
  for (i=0; i<2*MAX; ++i)
    Record[i]=-1;
  }
  
void imprime(void)
  {
  int i;
  for (i=0; i<2*MAX;++i)
    printf("%d ",Record[i]);
  printf("\n");
  }
void espera(int n)
  {
  int i,j;
  for (i=0; i<n; ++i)
    for (j=0; j<100000; ++j)
      j = j;
  }

void *counter(void * param)
  {
  int i;
  int n = (int) param;
  for (i=0; i< MAX; ++i)
     {
     // tarefa muito grande e importante
     Record[nextFree]=i;
     espera(1);
     ++nextFree;
     espera(1);
     // outra tarefa legal
     }
  }

int main ()
  {
  int i;
  pthread_t t1;
  pthread_t t2;
  pthread_attr_t at;
  init();
  imprime();
  pthread_attr_init(&at);
  pthread_attr_setscope(&at,PTHREAD_SCOPE_SYSTEM);
  pthread_create(&t1,&at,counter,(void*)1);
  pthread_create(&t2,&at,counter,(void*)2);
  printf("Started\n ");
  pthread_join(t1,0);
  pthread_join(t2,0);
  printf("Finish\n ");
  imprime();

  }
