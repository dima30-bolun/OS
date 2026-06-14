#ifndef BOLUN_LUMIA520_CAP_0291_H
#define BOLUN_LUMIA520_CAP_0291_H
#define BOLUN_CAP_DEVICE "lumia520"
#define BOLUN_CAP_SOC "MSM8227"
#define BOLUN_CAP_INDEX 291
#define BOLUN_CAP_IRQ 35
#define BOLUN_CAP_DMA 3
#define BOLUN_CAP_IDLE_MW 41
static inline unsigned bolun_lumia520_cap_0291_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
