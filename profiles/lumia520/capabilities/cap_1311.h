#ifndef BOLUN_LUMIA520_CAP_1311_H
#define BOLUN_LUMIA520_CAP_1311_H
#define BOLUN_CAP_DEVICE "lumia520"
#define BOLUN_CAP_SOC "MSM8227"
#define BOLUN_CAP_INDEX 1311
#define BOLUN_CAP_IRQ 95
#define BOLUN_CAP_DMA 7
#define BOLUN_CAP_IDLE_MW 71
static inline unsigned bolun_lumia520_cap_1311_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
