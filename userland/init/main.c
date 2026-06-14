#include "bolun/kernel.h"
#include <stdio.h>
int bolun_lumia_probe_all(void);
int main(void){ bolun_kernel_boot(); bolun_lumia_probe_all(); for(int i=0;i<3;i++) bolun_schedule_tick(); printf("Bolun Phone OS MainOS model booted: pid=%d tid=%d ticks=%llu\n",1,g_kernel.current_tid,(unsigned long long)g_kernel.ticks); return 0; }
