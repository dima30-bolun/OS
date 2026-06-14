#ifndef BOLUN_LUMIA520_CAP_0751_H
#define BOLUN_LUMIA520_CAP_0751_H
#define BOLUN_CAP_DEVICE "lumia520"
#define BOLUN_CAP_SOC "MSM8227"
#define BOLUN_CAP_INDEX 751
#define BOLUN_CAP_IRQ 111
#define BOLUN_CAP_DMA 7
#define BOLUN_CAP_IDLE_MW 51
static inline unsigned bolun_lumia520_cap_0751_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
