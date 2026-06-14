#ifndef BOLUN_LUMIA520_CAP_0805_H
#define BOLUN_LUMIA520_CAP_0805_H
#define BOLUN_CAP_DEVICE "lumia520"
#define BOLUN_CAP_SOC "MSM8227"
#define BOLUN_CAP_INDEX 805
#define BOLUN_CAP_IRQ 69
#define BOLUN_CAP_DMA 5
#define BOLUN_CAP_IDLE_MW 105
static inline unsigned bolun_lumia520_cap_0805_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
