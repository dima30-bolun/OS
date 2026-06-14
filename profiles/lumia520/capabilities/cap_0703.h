#ifndef BOLUN_LUMIA520_CAP_0703_H
#define BOLUN_LUMIA520_CAP_0703_H
#define BOLUN_CAP_DEVICE "lumia520"
#define BOLUN_CAP_SOC "MSM8227"
#define BOLUN_CAP_INDEX 703
#define BOLUN_CAP_IRQ 63
#define BOLUN_CAP_DMA 7
#define BOLUN_CAP_IDLE_MW 93
static inline unsigned bolun_lumia520_cap_0703_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
