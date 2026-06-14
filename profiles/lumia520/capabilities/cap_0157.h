#ifndef BOLUN_LUMIA520_CAP_0157_H
#define BOLUN_LUMIA520_CAP_0157_H
#define BOLUN_CAP_DEVICE "lumia520"
#define BOLUN_CAP_SOC "MSM8227"
#define BOLUN_CAP_INDEX 157
#define BOLUN_CAP_IRQ 93
#define BOLUN_CAP_DMA 5
#define BOLUN_CAP_IDLE_MW 87
static inline unsigned bolun_lumia520_cap_0157_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
