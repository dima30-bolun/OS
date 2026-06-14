#ifndef BOLUN_LUMIA520_CAP_0426_H
#define BOLUN_LUMIA520_CAP_0426_H
#define BOLUN_CAP_DEVICE "lumia520"
#define BOLUN_CAP_SOC "MSM8227"
#define BOLUN_CAP_INDEX 426
#define BOLUN_CAP_IRQ 74
#define BOLUN_CAP_DMA 2
#define BOLUN_CAP_IDLE_MW 86
static inline unsigned bolun_lumia520_cap_0426_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
