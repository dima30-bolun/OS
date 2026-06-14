#ifndef BOLUN_LUMIA625H_CAP_1023_H
#define BOLUN_LUMIA625H_CAP_1023_H
#define BOLUN_CAP_DEVICE "lumia625h"
#define BOLUN_CAP_SOC "MSM8930"
#define BOLUN_CAP_INDEX 1023
#define BOLUN_CAP_IRQ 95
#define BOLUN_CAP_DMA 7
#define BOLUN_CAP_IDLE_MW 53
static inline unsigned bolun_lumia625h_cap_1023_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
