#ifndef BOLUN_LUMIA520_CAP_1490_H
#define BOLUN_LUMIA520_CAP_1490_H
#define BOLUN_CAP_DEVICE "lumia520"
#define BOLUN_CAP_SOC "MSM8227"
#define BOLUN_CAP_INDEX 1490
#define BOLUN_CAP_IRQ 82
#define BOLUN_CAP_DMA 2
#define BOLUN_CAP_IDLE_MW 70
static inline unsigned bolun_lumia520_cap_1490_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
