/* extern void __VERIFIER_error() __attribute__ ((__noreturn__)); */

/* #include <pthread.h> */

/* int i=1, j=1; */

/* #define NUM 6 */

/* void * */
/* t1(void* arg) */
/* { */
/*   int k = 0; */

/*   for (k = 0; k < NUM; k++) */
/*     i+=j; */

/*   pthread_exit(NULL); */
/* } */

/* void * */
/* t2(void* arg) */
/* { */
/*   int k = 0; */

/*   for (k = 0; k < NUM; k++) */
/*     j+=i; */

/*   pthread_exit(NULL); */
/* } */

/* int */
/* main(int argc, char **argv) */
/* { */
/*   pthread_t id1, id2; */

/*   pthread_create(&id1, NULL, t1, NULL); */
/*   pthread_create(&id2, NULL, t2, NULL); */

/*   if (i >= 377 || j >= 377) { */
/*     ERROR: __VERIFIER_error(); */
/*   } */

/*   return 0; */
/* } */


#define NX NUM
#define NY NUM

int x = 1, y =1;
#include "seq.h"


void *
t1()
{
  int k = 0;

  for (k = 0; k < NUM; k++) {
    int t1, t2;
    t1 = read_x();
    t2 = read_y();
    write_x(t1 + t2);
    //    i+=j;
  }

  //pthread_exit(NULL);
}

void *
t2()
{
  int k = 0;

  for (k = 0; k < NUM; k++) {
    int t1, t2;
    t1 = read_x();
    t2 = read_y();
    write_y(t1+t2);
    //    j+=i;
  }

  //  pthread_exit(NULL);
}

int
main(int argc, char **argv)
{
  /* pthread_t id1, id2; */

  /* pthread_create(&id1, NULL, t1, NULL); */
  /* pthread_create(&id2, NULL, t2, NULL); */

  sysinit();
  procinit(); t1(); procend();
  procinit(); t2(); procend();
  sysend();

  if (x >= 377 || y >= 377) {
    assert(0);
    //    ERROR: __VERIFIER_error();
  }

  return 0;
}
