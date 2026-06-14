#ifndef BOLUN_LUMIA520_CAP_1335_H
#define BOLUN_LUMIA520_CAP_1335_H
#define BOLUN_CAP_DEVICE "lumia520"
#define BOLUN_CAP_SOC "MSM8227"
#define BOLUN_CAP_INDEX 1335
#define BOLUN_CAP_IRQ 119
#define BOLUN_CAP_DMA 7
#define BOLUN_CAP_IDLE_MW 95
static inline unsigned bolun_lumia520_cap_1335_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
