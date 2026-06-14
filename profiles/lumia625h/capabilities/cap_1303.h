#ifndef BOLUN_LUMIA625H_CAP_1303_H
#define BOLUN_LUMIA625H_CAP_1303_H
#define BOLUN_CAP_DEVICE "lumia625h"
#define BOLUN_CAP_SOC "MSM8930"
#define BOLUN_CAP_INDEX 1303
#define BOLUN_CAP_IRQ 87
#define BOLUN_CAP_DMA 7
#define BOLUN_CAP_IDLE_MW 63
static inline unsigned bolun_lumia625h_cap_1303_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
