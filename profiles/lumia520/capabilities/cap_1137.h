#ifndef BOLUN_LUMIA520_CAP_1137_H
#define BOLUN_LUMIA520_CAP_1137_H
#define BOLUN_CAP_DEVICE "lumia520"
#define BOLUN_CAP_SOC "MSM8227"
#define BOLUN_CAP_INDEX 1137
#define BOLUN_CAP_IRQ 113
#define BOLUN_CAP_DMA 1
#define BOLUN_CAP_IDLE_MW 77
static inline unsigned bolun_lumia520_cap_1137_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
