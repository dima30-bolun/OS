#include "bolun/kernel.h"
bool bolun_check_cap(int pid,uint32_t cap){ return pid>0&&pid<BOLUN_MAX_PROCESSES&&(g_kernel.processes[pid].caps&cap)==cap; }
int bolun_open_handle(int pid,void *object,uint32_t rights){ if(pid<=0||pid>=BOLUN_MAX_PROCESSES) return -1; for(int i=1;i<BOLUN_MAX_HANDLES;i++){ if(g_kernel.handles[i].id==0){ g_kernel.handles[i]=(bolun_handle_t){.id=i,.owner=pid,.rights=rights,.object=object}; return i; }} return -2; }
