//#define NUM 10
#define SUM (3*NUM)
#define NX 1
#define NY (2*NUM)

int x=0;
int y=0;

#include "seq_inv.h"

_Bool local=0;

void *
t1()
{
  for(int i =0; i<NUM; i++) {
	int t;
	//	local=1;
	//t = local ? read_y3() : read_yo();
	t = read_y4();
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
	//	local=1;
	//	t = local ? read_y3() : read_yo();
	t = read_y4();
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

  
  assert(y != SUM);
  
  return 0;
}
