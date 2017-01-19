#define MAXXW (NX+1)
#define MAXYW (NY+1)

#define MAXT ((MAXXW-1)+(MAXYW-1)+1)

#define LOCAL 1
#define NON_LOCAL 0

int *value_x,*value_y;
unsigned short *ts_x,xloc=0,xcount=0,xlast=0;
unsigned short *ts_y,yloc=0,ycount=0,ylast=0;
unsigned short ct=0;
_Bool *free_x,*free_y;

void sysinit(){
  value_x=(int *)malloc(
			sizeof(int) * MAXXW);
  value_x[0]=x;
  ts_x=(unsigned short*)malloc(
		       sizeof(unsigned short)*(MAXXW+1));
  ts_x[0]=0; ts_x[MAXXW]=MAXT;
  for (int k=1; k<MAXXW+1; k++)
    __CPROVER_assume(ts_x[k-1] < ts_x[k]);
  free_x=(_Bool *)malloc(
			 sizeof(_Bool)*MAXXW);
  free_x[0]=0;


  
    value_y=(int *)malloc(
			sizeof(int) * MAXYW);
  value_y[0]=y;
  ts_y=(unsigned short*)malloc(
		       sizeof(unsigned short)*(MAXYW+1));
  ts_y[0]=0; ts_y[MAXYW]=MAXT;
  for (int k=1; k<MAXYW+1; k++)
    __CPROVER_assume(ts_y[k-1] < ts_y[k]);
  free_y=(_Bool *)malloc(
			 sizeof(_Bool)*MAXYW);
  free_y[0]=0;

}

void sysend() {
  __CPROVER_assume(xlast==xcount); x=value_x[xlast];
  __CPROVER_assume(ylast==ycount); y=value_y[ylast];
}

void procinit() {
  ct=0; xloc=0; yloc=0;
}
void procend() {
  if (xlast<xloc) xlast=xloc;
  if (ylast<yloc) ylast=yloc;
}

void write_x(int value) {
  unsigned short loc;
  __CPROVER_assume(xloc < loc &&
		   loc < MAXXW &&
		   free_x[loc] &&
		   ts_x[loc] > ct &&
		   value_x[loc] == value);
  xloc = loc;
  free_x[loc] = 0;
  xcount++;
  ct = ts_x[loc];
}

int read_x(_Bool isLocal) {
  unsigned short loc;
  /* if (isLocal) { */
  /*   __CPROVER_assume(ts_x[xloc+1] > ct); */
  /*   return value_x[xloc]; */
  /* } else { */
  /*   __CPROVER_assume(xloc <= loc && */
  /* 		     loc < MAXW && ts_x[loc+1] > ct); */
  /*   __CPROVER_assume(ts_x[loc+1] > ct); */
  /*   xloc = loc; */
  /*   if (ct<ts_x[loc]) ct=ts_x[loc]; */
  /*   return value_x[loc]; */
  /* } */

  /* __CPROVER_assume((!isLocal || xloc == loc) && */
  /* 		   (isLocal || (xloc <= loc && loc < MAXW))); */
  __CPROVER_assume((!isLocal || loc == xloc) &&
		   (isLocal || (xloc <= loc && loc < MAXXW)));

  __CPROVER_assume(ts_x[loc+1] > ct);
  xloc = loc;
  if (ct<ts_x[loc]) ct=ts_x[loc];
  return value_x[loc];
  
  //if (isLocal) {
    //__CPROVER_assume(loc == xloc);
  //  __CPROVER_assume(ts_x[xloc+1] > ct);
  //  return value_x[xloc];
  //} else {
  /* __CPROVER_assume((!isLocal || loc == xloc && ts_x[xloc+1] > ct) && */
  /* 		   (isLocal || xloc <= loc && */
  /* 		    loc < MAXW && ts_x[loc+1] > ct)); */
  
  //__CPROVER_assume(ts_x[loc+1] > ct);
  /* xloc = loc; */
  /* if (ct<ts_x[loc]) ct=ts_x[loc]; */
  /* return value_x[loc]; */
  //}
}

int read_x_local() {
  unsigned short loc;
  /* if (isLocal) { */
  /*   __CPROVER_assume(ts_x[xloc+1] > ct); */
  /*   return value_x[xloc]; */
  /* } else { */
  /*   __CPROVER_assume(xloc <= loc && */
  /* 		     loc < MAXW && ts_x[loc+1] > ct); */
  /*   __CPROVER_assume(ts_x[loc+1] > ct); */
  /*   xloc = loc; */
  /*   if (ct<ts_x[loc]) ct=ts_x[loc]; */
  /*   return value_x[loc]; */
  /* } */

  /* __CPROVER_assume((!isLocal || xloc == loc) && */
  /* 		   (isLocal || (xloc <= loc && loc < MAXW))); */
  __CPROVER_assume(xloc <= loc && loc < MAXXW && loc == xloc);

  __CPROVER_assume(ts_x[loc+1] > ct);
  xloc = loc;
  if (ct<ts_x[loc]) ct=ts_x[loc];
  return value_x[loc];
}

int read_x1() {
  unsigned short loc;
  __CPROVER_assume(loc == xloc);
  __CPROVER_assume(ts_x[loc+1] > ct);
  xloc = loc;
  if (ct<ts_x[loc]) ct=ts_x[loc];
  return value_x[loc];
}

int read_x2() {
  unsigned short loc;
  __CPROVER_assume(loc == xloc &&
		   xloc <= loc && loc < MAXXW);
  __CPROVER_assume(ts_x[loc+1] > ct);
  xloc = loc;
  if (ct<ts_x[loc]) ct=ts_x[loc];
  return value_x[loc];
}

int read_xo() {
  unsigned short loc;
  __CPROVER_assume(xloc <= loc && loc < MAXXW);
  __CPROVER_assume(ts_x[loc+1] > ct);
  xloc = loc;
  if (ct<ts_x[loc]) ct=ts_x[loc];
  return value_x[loc];
}


void write_y(int value) {
  unsigned short loc;
  __CPROVER_assume(yloc < loc &&
		   loc < MAXYW &&
		   free_y[loc] &&
		   ts_y[loc] > ct &&
		   value_y[loc] == value);
  yloc = loc;
  free_y[loc] = 0;
  ycount++;
  ct = ts_y[loc];
}

int read_y() {
  unsigned short loc;
  _Bool isLocal;
  /* if (isLocal) { */
  /*   __CPROVER_assume(ts_y[yloc+1] > ct); */
  /*   return value_y[yloc]; */
  /* } else { */
  /*   __CPROVER_assume(yloc <= loc && */
  /* 		     loc < MAXW && ts_y[loc+1] > ct); */
  /*   __CPROVER_assume(ts_y[loc+1] > ct); */
  /*   yloc = loc; */
  /*   if (ct<ts_y[loc]) ct=ts_y[loc]; */
  /*   return value_y[loc]; */
  /* } */

  //int tmp;

  //tmp = MAXW - yloc;
  
  /* __CPROVER_assume((!isLocal || loc == yloc) && */
  /* 		   (isLocal || (yloc <= loc && loc < MAXW))); */
  __CPROVER_assume((!isLocal || loc == yloc) &&
		   (isLocal || (yloc <= loc && loc < MAXYW)));
  
  __CPROVER_assume(ts_y[loc+1] > ct);
  yloc = loc;
  if (ct<ts_y[loc]) ct=ts_y[loc];
  return value_y[loc];

  
 // if (isLocal) {
    //__CPROVER_assume(loc == yloc);
 //   __CPROVER_assume(ts_y[yloc+1] > ct);
 //   return value_y[yloc];
  //} else {
  //  __CPROVER_assume((!isLocal || yloc == loc) && yloc <= loc &&
  //		   loc < MAXW);
  //__CPROVER_assume(ts_y[loc+1] > ct);
  /* __CPROVER_assume((!isLocal || loc == yloc && ts_x[yloc+1] > ct) && */
  /* 		   (isLocal || yloc <= loc && */
  /* 		    loc < MAXW && ts_x[loc+1] > ct)); */

  /* yloc = loc; */
  /* if (ct<ts_y[loc]) ct=ts_y[loc]; */
  /* return value_y[loc]; */
  //}
}

int read_y_local() {
  unsigned short loc;
  /* if (isLocal) { */
  /*   __CPROVER_assume(ts_y[yloc+1] > ct); */
  /*   return value_y[yloc]; */
  /* } else { */
  /*   __CPROVER_assume(yloc <= loc && */
  /* 		     loc < MAXW && ts_y[loc+1] > ct); */
  /*   __CPROVER_assume(ts_y[loc+1] > ct); */
  /*   yloc = loc; */
  /*   if (ct<ts_y[loc]) ct=ts_y[loc]; */
  /*   return value_y[loc]; */
  /* } */

  //int tmp;

  //tmp = MAXW - yloc;
  
  /* __CPROVER_assume((!isLocal || loc == yloc) && */
  /* 		   (isLocal || (yloc <= loc && loc < MAXW))); */
  __CPROVER_assume(yloc <= loc && loc < MAXYW && loc == yloc);
  
  __CPROVER_assume(ts_y[loc+1] > ct);
  yloc = loc;
  if (ct<ts_y[loc]) ct=ts_y[loc];
  return value_y[loc];

}

int read_y_nonlocal() {
  unsigned short loc;
  /* if (isLocal) { */
  /*   __CPROVER_assume(ts_y[yloc+1] > ct); */
  /*   return value_y[yloc]; */
  /* } else { */
  /*   __CPROVER_assume(yloc <= loc && */
  /* 		     loc < MAXW && ts_y[loc+1] > ct); */
  /*   __CPROVER_assume(ts_y[loc+1] > ct); */
  /*   yloc = loc; */
  /*   if (ct<ts_y[loc]) ct=ts_y[loc]; */
  /*   return value_y[loc]; */
  /* } */

  //int tmp;

  //tmp = MAXW - yloc;
  
  /* __CPROVER_assume((!isLocal || loc == yloc) && */
  /* 		   (isLocal || (yloc <= loc && loc < MAXW))); */
  __CPROVER_assume(loc > yloc && loc < MAXYW);
  
  __CPROVER_assume(ts_y[loc+1] > ct);
  yloc = loc;
  if (ct<ts_y[loc]) ct=ts_y[loc];
  return value_y[loc];

}

int read_y1() {
  unsigned short loc;
  __CPROVER_assume(loc == yloc);
  __CPROVER_assume(ts_y[loc+1] > ct);
  yloc = loc;
  if (ct<ts_y[loc]) ct=ts_y[loc];
  return value_y[loc];

}

int read_y2() {
  unsigned short loc;
  __CPROVER_assume((loc == yloc) &&
		   (yloc <= loc && loc < MAXYW));
  
  __CPROVER_assume(ts_y[loc+1] > ct);
  yloc = loc;
  if (ct<ts_y[loc]) ct=ts_y[loc];
  return value_y[loc];

}

int read_yo() {
  unsigned short loc;
  __CPROVER_assume((yloc <= loc && loc < MAXYW));
  
  __CPROVER_assume(ts_y[loc+1] > ct);
  yloc = loc;
  if (ct<ts_y[loc]) ct=ts_y[loc];
  return value_y[loc];

}

int read_y3() {
  __CPROVER_assume(ts_y[yloc+1] > ct);
  return value_y[yloc];

}
