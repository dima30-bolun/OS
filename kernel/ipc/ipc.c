#include "bolun/kernel.h"
#include <string.h>
typedef struct { int src,dst; size_t len; unsigned char data[256]; int used; } msg_t; static msg_t q[64];
int bolun_ipc_send(int src,int dst,const void *data,size_t len){ if(len>256||!data) return -1; for(int i=0;i<64;i++) if(!q[i].used){ q[i].used=1; q[i].src=src; q[i].dst=dst; q[i].len=len; memcpy(q[i].data,data,len); return 0; } return -2; }
int bolun_ipc_recv(int pid,void *data,size_t cap){ if(!data) return -1; for(int i=0;i<64;i++) if(q[i].used&&q[i].dst==pid){ size_t n=q[i].len<cap?q[i].len:cap; memcpy(data,q[i].data,n); q[i].used=0; return (int)n; } return 0; }
