#ifndef BOLUN_LUMIA520_CAP_0138_H
#define BOLUN_LUMIA520_CAP_0138_H
#define BOLUN_CAP_DEVICE "lumia520"
#define BOLUN_CAP_SOC "MSM8227"
#define BOLUN_CAP_INDEX 138
#define BOLUN_CAP_IRQ 74
#define BOLUN_CAP_DMA 2
#define BOLUN_CAP_IDLE_MW 68
static inline unsigned bolun_lumia520_cap_0138_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
