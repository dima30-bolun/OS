#ifndef BOLUN_LUMIA520_CAP_0804_H
#define BOLUN_LUMIA520_CAP_0804_H
#define BOLUN_CAP_DEVICE "lumia520"
#define BOLUN_CAP_SOC "MSM8227"
#define BOLUN_CAP_INDEX 804
#define BOLUN_CAP_IRQ 68
#define BOLUN_CAP_DMA 4
#define BOLUN_CAP_IDLE_MW 104
static inline unsigned bolun_lumia520_cap_0804_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
