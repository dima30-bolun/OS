#ifndef BOLUN_LUMIA520_CAP_0642_H
#define BOLUN_LUMIA520_CAP_0642_H
#define BOLUN_CAP_DEVICE "lumia520"
#define BOLUN_CAP_SOC "MSM8227"
#define BOLUN_CAP_INDEX 642
#define BOLUN_CAP_IRQ 98
#define BOLUN_CAP_DMA 2
#define BOLUN_CAP_IDLE_MW 32
static inline unsigned bolun_lumia520_cap_0642_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
