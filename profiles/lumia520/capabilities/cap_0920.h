#ifndef BOLUN_LUMIA520_CAP_0920_H
#define BOLUN_LUMIA520_CAP_0920_H
#define BOLUN_CAP_DEVICE "lumia520"
#define BOLUN_CAP_SOC "MSM8227"
#define BOLUN_CAP_INDEX 920
#define BOLUN_CAP_IRQ 88
#define BOLUN_CAP_DMA 0
#define BOLUN_CAP_IDLE_MW 40
static inline unsigned bolun_lumia520_cap_0920_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
