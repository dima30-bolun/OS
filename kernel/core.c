#include "bolun/kernel.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
bolun_kernel_t g_kernel;
void bolun_panic(const char *reason){ fprintf(stderr,"BOLUN PANIC: %s\n",reason); abort(); }
void bolun_kernel_boot(void){ memset(&g_kernel,0,sizeof(g_kernel)); g_kernel.current_tid=-1; bolun_hal_init(BOLUN_ARCH_ARMV7,1,1000000u,true); int init=bolun_process_create(0,CAP_FS|CAP_NET|CAP_DEVICE|CAP_PHONE|CAP_SYSTEM); if(init!=1) bolun_panic("init process allocation failed"); if(bolun_thread_create(init,0x10000,10)<0) bolun_panic("init thread allocation failed"); }
