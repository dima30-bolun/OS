#ifndef BOLUN_LUMIA520_CAP_1184_H
#define BOLUN_LUMIA520_CAP_1184_H
#define BOLUN_CAP_DEVICE "lumia520"
#define BOLUN_CAP_SOC "MSM8227"
#define BOLUN_CAP_INDEX 1184
#define BOLUN_CAP_IRQ 64
#define BOLUN_CAP_DMA 0
#define BOLUN_CAP_IDLE_MW 34
static inline unsigned bolun_lumia520_cap_1184_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
