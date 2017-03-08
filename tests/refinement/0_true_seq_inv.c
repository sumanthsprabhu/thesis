extern void __VERIFIER_error() __attribute__ ((__noreturn__));

#define NUM 15
#define NY (NUM+1)
#define NX NUM

int x=0;
int y=0;

int verr=0;
//#include <pthread.h>
#include "seq_inv.h"

void *
t1()
{
  //  int t = 0;

  while (read_yo() < NUM) {
    int tmpx, tmpy;
	
    //x = x + y;
    tmpx = read_x4();
    tmpy = read_y4();
    write_x(tmpx+tmpy);

    //y = y+1;
    tmpy = read_y4();
    write_y(tmpy + 1);

    
  }
  
  //  pthread_exit(NULL);
}

void *
t2()
{
  int t = 0;

  while (read_yo() < NUM) {} //spin
  //t = y;
  t = read_yo();
  
  //y = x + y;
  int tmpx, tmpy;
  tmpx = read_xo();
  tmpy = read_yo();
  write_y(tmpx+tmpy);
  
  
  if (read_yo() != t + read_xo()) {
    verr = 1;
    // __VERIFIER_error();
  }

  //pthread_exit(NULL);
}

int
main(int argc, char **argv)
{
  /* pthread_t id1, id2; */

  /* pthread_create(&id1, NULL, t1, NULL); */
  /* pthread_create(&id2, NULL, t2, NULL); */

  /* pthread_join(id1, (void *)0); */
  /* pthread_join(id2, (void *)0); */

  sysinit();
  procinit(); t1(); procend();
  procinit(); t2(); procend();
  sysend();

  assert(!verr);
  
  return 0;
}
