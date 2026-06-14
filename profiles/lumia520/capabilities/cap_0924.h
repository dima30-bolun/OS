#ifndef BOLUN_LUMIA520_CAP_0924_H
#define BOLUN_LUMIA520_CAP_0924_H
#define BOLUN_CAP_DEVICE "lumia520"
#define BOLUN_CAP_SOC "MSM8227"
#define BOLUN_CAP_INDEX 924
#define BOLUN_CAP_IRQ 92
#define BOLUN_CAP_DMA 4
#define BOLUN_CAP_IDLE_MW 44
static inline unsigned bolun_lumia520_cap_0924_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
