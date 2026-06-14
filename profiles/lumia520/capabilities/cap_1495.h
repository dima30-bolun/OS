#ifndef BOLUN_LUMIA520_CAP_1495_H
#define BOLUN_LUMIA520_CAP_1495_H
#define BOLUN_CAP_DEVICE "lumia520"
#define BOLUN_CAP_SOC "MSM8227"
#define BOLUN_CAP_INDEX 1495
#define BOLUN_CAP_IRQ 87
#define BOLUN_CAP_DMA 7
#define BOLUN_CAP_IDLE_MW 75
static inline unsigned bolun_lumia520_cap_1495_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
