#include "bolun/kernel.h"

void bolun_hal_init(bolun_arch_t arch, uint32_t cores, uint64_t timer_hz, bool has_mmu)
{
    g_kernel.hal.arch = arch;
    g_kernel.hal.cores = cores == 0 ? 1 : cores;
    g_kernel.hal.timer_hz = timer_hz == 0 ? 1000000u : timer_hz;
    g_kernel.hal.has_mmu = has_mmu;
    g_kernel.hal.has_nx = has_mmu;
    g_kernel.hal.has_aslr = has_mmu;
}

const bolun_hal_info_t *bolun_hal_info(void)
{
    return &g_kernel.hal;
}

uint64_t bolun_hal_timer_deadline(uint64_t ticks_from_now)
{
    return g_kernel.ticks + ticks_from_now;
}
