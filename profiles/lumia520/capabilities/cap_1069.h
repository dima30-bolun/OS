#ifndef BOLUN_LUMIA520_CAP_1069_H
#define BOLUN_LUMIA520_CAP_1069_H
#define BOLUN_CAP_DEVICE "lumia520"
#define BOLUN_CAP_SOC "MSM8227"
#define BOLUN_CAP_INDEX 1069
#define BOLUN_CAP_IRQ 45
#define BOLUN_CAP_DMA 5
#define BOLUN_CAP_IDLE_MW 99
static inline unsigned bolun_lumia520_cap_1069_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
