#define NUM 20
#define SUM 60
#define NX 1
#define NY (2*NUM)

int x=0;
int y=0;

#include "seq_inv.h"

void *
t1()
{
  for(int i =0; i<NUM; i++) {
	int t;
	t = read_y2();
	write_y(t + 1);
  }
  
  write_x(1);
}


void *
t2()
{
  int t;

  while (read_xo() != 1) {}
  
  t = read_yo();
  
  for(int i =0; i<NUM; i++) {
	write_y(t + 2);
	t = read_y2();
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

  
  assert(y > 0);
  
  return 0;
}
