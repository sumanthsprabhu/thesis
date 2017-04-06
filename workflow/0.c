#define NUM 20
int x = 0;
int y = 0;

#include <pthread.h>
//#include <assert.h>
#include <stdio.h>

void * t1()
{
  while (y < NUM) {
    y = y + 1;
    x = x + y;
  }

  pthread_exit(NULL);
}

void * t2()
{
  int t;
  while (y < NUM) {}
  t = y;
  y = x + y;
  //  assert(y == t + x); //
  if (y != t + x) {
    printf("assert violated\n");
    //exit(22);
  }
}

int main()
{
  pthread_t id1, id2;

  pthread_create(&id1, NULL, t1, NULL);
  pthread_create(&id2, NULL, t2, NULL);

  pthread_join(id1, (void *)0);
  pthread_join(id2, (void *)0);

  return 0;
}
