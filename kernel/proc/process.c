#include "bolun/kernel.h"
#include <string.h>
static uint8_t next_asid=1;
int bolun_process_create(int parent,uint32_t caps){ for(int i=1;i<BOLUN_MAX_PROCESSES;i++){ bolun_process_t *p=&g_kernel.processes[i]; if(p->pid==0 || p->state==BOLUN_TERMINATED){ memset(p,0,sizeof(*p)); p->pid=i; p->parent=parent; p->caps=caps; p->asid=next_asid++; if(next_asid==0) next_asid=1; p->state=BOLUN_READY; return i; }} return -1; }
void bolun_process_exit(int pid,int code){ if(pid>0&&pid<BOLUN_MAX_PROCESSES){ g_kernel.processes[pid].state=BOLUN_TERMINATED; g_kernel.processes[pid].exit_code=code; for(int i=0;i<BOLUN_MAX_THREADS;i++) if(g_kernel.threads[i].pid==pid) g_kernel.threads[i].state=BOLUN_TERMINATED; }}
int bolun_wait(int parent,int child){ if(child<=0||child>=BOLUN_MAX_PROCESSES) return -1; bolun_process_t *p=&g_kernel.processes[child]; if(p->parent!=parent) return -2; return p->state==BOLUN_TERMINATED?p->exit_code:-3; }
int bolun_thread_create(int pid,uintptr_t entry,int priority){ if(pid<=0||pid>=BOLUN_MAX_PROCESSES||g_kernel.processes[pid].pid==0) return -1; for(int i=1;i<BOLUN_MAX_THREADS;i++){ bolun_thread_t *t=&g_kernel.threads[i]; if(t->tid==0||t->state==BOLUN_TERMINATED){ memset(t,0,sizeof(*t)); t->tid=i; t->pid=pid; t->priority=priority; t->state=BOLUN_READY; t->ctx.r[15]=(uint32_t)entry; t->ctx.asid=g_kernel.processes[pid].asid; return i; }} return -2; }
