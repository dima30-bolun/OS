#ifndef BOLUN_LUMIA625H_CAP_0178_H
#define BOLUN_LUMIA625H_CAP_0178_H
#define BOLUN_CAP_DEVICE "lumia625h"
#define BOLUN_CAP_SOC "MSM8930"
#define BOLUN_CAP_INDEX 178
#define BOLUN_CAP_IRQ 114
#define BOLUN_CAP_DMA 2
#define BOLUN_CAP_IDLE_MW 108
static inline unsigned bolun_lumia625h_cap_0178_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
