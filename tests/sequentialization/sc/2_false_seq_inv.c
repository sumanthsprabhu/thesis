#define NUM 15
#define NY (2*NUM)
#define NX 0

int x=0, y=0;

#include "seq_inv.h"

void *
t1()
{
  for(int i =0; i<NUM; i++) {
	int t;
	t = read_y_nonlocal();
	write_y(t + 1);
  }
}


void *
t2()
{
  int t;
  t = read_y();
  for(int i =0; i<NUM; i++) {
	write_y(t + 2);
	t = read_y_nonlocal();
  }

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

  
  assert(y != 45);
  
  return 0;
}
