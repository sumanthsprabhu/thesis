// [Anand et al.]: Sequentialization Using Timestamps, Anand Yeolekar, Kumar Madhukar, Dipali Bhutada, Venkatesh R. In TAMC, 2017.

union pthread_attr_t;
typedef union pthread_attr_t pthread_attr_t;
union pthread_attr_t{
char  __size [56];
long  __align;
} ;
typedef unsigned long  pthread_t;
extern int  pthread_create(pthread_t* __newthread, pthread_attr_t const* __attr, void *(* __start_routine)(void *), void * __arg);
extern void  pthread_exit(void * __retval);
extern int  pthread_join(pthread_t __th, void ** __thread_return);
void * t1();
void * t2();
int  mymain();
int  x=0;
int  y=0;
#define cpa __CPROVER_assume
#include "std_inv.h"
_Bool AFlag0=1;
void * t1()
{
int v1tmp;
int v2tmp;

while(1) { 

readv2_inv();
v2tmp = v2q[lrv2];

 if (!(v2tmp  < NUM)){break;}
else{
readv2_inv();
v2tmp = v2q[lrv2];


writev2( ); 
cpa(v2q[lrv2]==v2tmp  + 1);
readv2_inv();
v2tmp = v2q[lrv2];
readv1_inv();
v1tmp = v1q[lrv1];


writev1( ); 
cpa(v1q[lrv1]==v1tmp  + v2tmp );
}
}

//pthread_exit((( void * ) 0));
}
void * t2()
{
int v1tmp;
int v2tmp;
int  t;

while(1) { 

readv2();
v2tmp = v2q[lrv2];

 if (!(v2tmp  < NUM)){break;}
else{
;
}
}
readv2();
v2tmp = v2q[lrv2];

t = v2tmp ;
readv2_inv();
v2tmp = v2q[lrv2];
readv1();
v1tmp = v1q[lrv1];


writev2( ); 
cpa(v2q[lrv2]==v1tmp  + v2tmp );
readv2();
v2tmp = v2q[lrv2];
readv1();
v1tmp = v1q[lrv1];

readv2();
v2tmp = v2q[lrv2];
readv1();
v1tmp = v1q[lrv1];
//assert(v2tmp  == t + v1tmp )
AFlag0 = (v2tmp  == t + v1tmp );
}
int  mymain()
{
int v1tmp;
int v2tmp;
//pthread_t id1;
//pthread_t id2;

//pthread_create( & id1, (( void * ) 0), t1, (( void * ) 0))
processinit();t1(0); 
 processend();

//pthread_create( & id2, (( void * ) 0), t2, (( void * ) 0))
processinit();t2(0); 
 processend();

//pthread_join(id1, ( void * ) 0);

//pthread_join(id2, ( void * ) 0)
common_join();
return 0;
}
void main() {
init();
processinit(); mymain(); processend();
post();

 assert(AFlag0);
/* if( ! ( AFlag0)) */
/* {ERROR : __VERIFIER_error();} */
}
