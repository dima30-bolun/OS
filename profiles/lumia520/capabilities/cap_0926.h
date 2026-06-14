#ifndef BOLUN_LUMIA520_CAP_0926_H
#define BOLUN_LUMIA520_CAP_0926_H
#define BOLUN_CAP_DEVICE "lumia520"
#define BOLUN_CAP_SOC "MSM8227"
#define BOLUN_CAP_INDEX 926
#define BOLUN_CAP_IRQ 94
#define BOLUN_CAP_DMA 6
#define BOLUN_CAP_IDLE_MW 46
static inline unsigned bolun_lumia520_cap_0926_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
