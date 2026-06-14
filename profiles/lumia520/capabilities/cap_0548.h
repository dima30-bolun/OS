#ifndef BOLUN_LUMIA520_CAP_0548_H
#define BOLUN_LUMIA520_CAP_0548_H
#define BOLUN_CAP_DEVICE "lumia520"
#define BOLUN_CAP_SOC "MSM8227"
#define BOLUN_CAP_INDEX 548
#define BOLUN_CAP_IRQ 100
#define BOLUN_CAP_DMA 4
#define BOLUN_CAP_IDLE_MW 28
static inline unsigned bolun_lumia520_cap_0548_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
