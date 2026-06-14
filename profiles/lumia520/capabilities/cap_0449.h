#ifndef BOLUN_LUMIA520_CAP_0449_H
#define BOLUN_LUMIA520_CAP_0449_H
#define BOLUN_CAP_DEVICE "lumia520"
#define BOLUN_CAP_SOC "MSM8227"
#define BOLUN_CAP_INDEX 449
#define BOLUN_CAP_IRQ 97
#define BOLUN_CAP_DMA 1
#define BOLUN_CAP_IDLE_MW 109
static inline unsigned bolun_lumia520_cap_0449_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
