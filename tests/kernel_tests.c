#include "bolun/kernel.h"
#include <assert.h>
#include <string.h>
int main(void){ bolun_kernel_boot(); int p=bolun_process_create(1,CAP_FS); assert(p>1); assert(bolun_check_cap(p,CAP_FS)); assert(!bolun_check_cap(p,CAP_NET)); assert(bolun_virtual_alloc(p,0x400000,8192,3)==0); assert(bolun_page_fault(p,0x400123,1)==0); int t=bolun_thread_create(p,0x8000,20); assert(t>0); bolun_schedule_tick(); assert(g_kernel.current_tid==t); const char m[]="hello"; assert(bolun_ipc_send(1,p,m,sizeof(m))==0); char b[8]; assert(bolun_ipc_recv(p,b,sizeof(b))==(int)sizeof(m)); assert(strcmp(b,m)==0); bolun_process_exit(p,7); assert(bolun_wait(1,p)==7); return 0; }
