#ifndef BOLUN_LUMIA520_CAP_0627_H
#define BOLUN_LUMIA520_CAP_0627_H
#define BOLUN_CAP_DEVICE "lumia520"
#define BOLUN_CAP_SOC "MSM8227"
#define BOLUN_CAP_INDEX 627
#define BOLUN_CAP_IRQ 83
#define BOLUN_CAP_DMA 3
#define BOLUN_CAP_IDLE_MW 107
static inline unsigned bolun_lumia520_cap_0627_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
