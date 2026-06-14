#ifndef BOLUN_LUMIA520_CAP_0589_H
#define BOLUN_LUMIA520_CAP_0589_H
#define BOLUN_CAP_DEVICE "lumia520"
#define BOLUN_CAP_SOC "MSM8227"
#define BOLUN_CAP_INDEX 589
#define BOLUN_CAP_IRQ 45
#define BOLUN_CAP_DMA 5
#define BOLUN_CAP_IDLE_MW 69
static inline unsigned bolun_lumia520_cap_0589_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
