#ifndef BOLUN_LUMIA520_CAP_0572_H
#define BOLUN_LUMIA520_CAP_0572_H
#define BOLUN_CAP_DEVICE "lumia520"
#define BOLUN_CAP_SOC "MSM8227"
#define BOLUN_CAP_INDEX 572
#define BOLUN_CAP_IRQ 124
#define BOLUN_CAP_DMA 4
#define BOLUN_CAP_IDLE_MW 52
static inline unsigned bolun_lumia520_cap_0572_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
