//[Anand et al.]: Sequentialization Using Timestamps, Anand Yeolekar, Kumar Madhukar, Dipali Bhutada, Venkatesh R. In TAMC, 2017.
  
#define  v1qsize ( NUM + 1 )
int * v1q ;
enum Bool * v1b ;
unsigned char * v1t ;
unsigned char v1c=0 ;
unsigned char lv1=0 ;
unsigned char lrv1 =0;
unsigned char copy_lrv1=0;
#define  v2qsize ( NUM + 1 + 1 )
int * v2q ;
enum Bool * v2b ;
unsigned char * v2t ;
unsigned char v2c=0 ;
unsigned char lv2=0 ;
unsigned char lrv2 =0;
unsigned char copy_lrv2=0;
#define maxlast ((v1qsize-1) + (v2qsize-1) + 1)

enum Bool {false,true};

readv1()
{unsigned char lr1;
cpa(lr1 >=  lrv1  && lr1 < v1qsize  );
 cpa(v1t[lr1+1] > v2t[lrv2]);
lrv1  = lr1;
}
writev1 ()
{unsigned char lw1;
cpa(lw1 >  lrv1  && lw1 < v1qsize  ); lrv1  = lw1;
 cpa( v1b [ lrv1 ]==false);
  cpa(v1t[lrv1] >v2t[lrv2]);
v1b [ lrv1 ]=true;
 v1c ++;
 }
readv2()
{unsigned char lr1;
cpa(lr1 >=  lrv2  && lr1 < v2qsize  );
 cpa(v2t[lr1+1] > v1t[lrv1]);
lrv2  = lr1;
}
writev2 ()
{unsigned char lw1;
cpa(lw1 >  lrv2  && lw1 < v2qsize  ); lrv2  = lw1;
 cpa( v2b [ lrv2 ]==false);
  cpa(v2t[lrv2] >v1t[lrv1]);
v2b [ lrv2 ]=true;
 v2c ++;
 }
void init() { 
 int k; 

 v1t = (char*) malloc (sizeof (char) * ( v1qsize +1));
 v1b = (enum Bool *) malloc (sizeof (enum Bool) * v1qsize );
v1q  = (int *)malloc (sizeof(int) * v1qsize );
v1t [ v1qsize ] = maxlast;
 
for(k=1;k< v1qsize +1; k+=1)
{
 cpa ( v1t [k] >  v1t [k-1]);
}
 v1q [0] =  x ; v1b [0] = true;
 v2t = (char*) malloc (sizeof (char) * ( v2qsize +1));
 v2b = (enum Bool *) malloc (sizeof (enum Bool) * v2qsize );
v2q  = (int *)malloc (sizeof(int) * v2qsize );
v2t [ v2qsize ] = maxlast;
 
for(k=1;k< v2qsize +1; k+=1)
{
 cpa ( v2t [k] >  v2t [k-1]);
}
 v2q [0] =  y ; v2b [0] = true;
}
void post() {
cpa( lv1 == v1c );
 x  =  v1q [ lv1 ];
 cpa( lv2 == v2c );
 y  =  v2q [ lv2 ];
 
}
void common_join() {
lrv1 = lv1 ;
 lrv2 = lv2 ;
 
}
void processinit() {
copy_lrv1= lrv1 ;
copy_lrv2= lrv2 ;

}
void processend() {

if ( lrv1 >  lv1 )  lv1  =  lrv1 ;
lrv1 =copy_lrv1 ;

if ( lrv2 >  lv2 )  lv2  =  lrv2 ;
lrv2 =copy_lrv2 ;

}
