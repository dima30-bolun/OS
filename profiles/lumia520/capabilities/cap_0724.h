#ifndef BOLUN_LUMIA520_CAP_0724_H
#define BOLUN_LUMIA520_CAP_0724_H
#define BOLUN_CAP_DEVICE "lumia520"
#define BOLUN_CAP_SOC "MSM8227"
#define BOLUN_CAP_INDEX 724
#define BOLUN_CAP_IRQ 84
#define BOLUN_CAP_DMA 4
#define BOLUN_CAP_IDLE_MW 24
static inline unsigned bolun_lumia520_cap_0724_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
