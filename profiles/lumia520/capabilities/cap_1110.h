#ifndef BOLUN_LUMIA520_CAP_1110_H
#define BOLUN_LUMIA520_CAP_1110_H
#define BOLUN_CAP_DEVICE "lumia520"
#define BOLUN_CAP_SOC "MSM8227"
#define BOLUN_CAP_INDEX 1110
#define BOLUN_CAP_IRQ 86
#define BOLUN_CAP_DMA 6
#define BOLUN_CAP_IDLE_MW 50
static inline unsigned bolun_lumia520_cap_1110_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
