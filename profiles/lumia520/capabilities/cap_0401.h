#ifndef BOLUN_LUMIA520_CAP_0401_H
#define BOLUN_LUMIA520_CAP_0401_H
#define BOLUN_CAP_DEVICE "lumia520"
#define BOLUN_CAP_SOC "MSM8227"
#define BOLUN_CAP_INDEX 401
#define BOLUN_CAP_IRQ 49
#define BOLUN_CAP_DMA 1
#define BOLUN_CAP_IDLE_MW 61
static inline unsigned bolun_lumia520_cap_0401_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
