#ifndef BOLUN_LUMIA520_CAP_0887_H
#define BOLUN_LUMIA520_CAP_0887_H
#define BOLUN_CAP_DEVICE "lumia520"
#define BOLUN_CAP_SOC "MSM8227"
#define BOLUN_CAP_INDEX 887
#define BOLUN_CAP_IRQ 55
#define BOLUN_CAP_DMA 7
#define BOLUN_CAP_IDLE_MW 97
static inline unsigned bolun_lumia520_cap_0887_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
