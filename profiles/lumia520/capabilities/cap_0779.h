#ifndef BOLUN_LUMIA520_CAP_0779_H
#define BOLUN_LUMIA520_CAP_0779_H
#define BOLUN_CAP_DEVICE "lumia520"
#define BOLUN_CAP_SOC "MSM8227"
#define BOLUN_CAP_INDEX 779
#define BOLUN_CAP_IRQ 43
#define BOLUN_CAP_DMA 3
#define BOLUN_CAP_IDLE_MW 79
static inline unsigned bolun_lumia520_cap_0779_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
