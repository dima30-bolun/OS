#ifndef BOLUN_LUMIA520_CAP_1348_H
#define BOLUN_LUMIA520_CAP_1348_H
#define BOLUN_CAP_DEVICE "lumia520"
#define BOLUN_CAP_SOC "MSM8227"
#define BOLUN_CAP_INDEX 1348
#define BOLUN_CAP_IRQ 36
#define BOLUN_CAP_DMA 4
#define BOLUN_CAP_IDLE_MW 108
static inline unsigned bolun_lumia520_cap_1348_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
