#ifndef BOLUN_LUMIA625H_CAP_0862_H
#define BOLUN_LUMIA625H_CAP_0862_H
#define BOLUN_CAP_DEVICE "lumia625h"
#define BOLUN_CAP_SOC "MSM8930"
#define BOLUN_CAP_INDEX 862
#define BOLUN_CAP_IRQ 126
#define BOLUN_CAP_DMA 6
#define BOLUN_CAP_IDLE_MW 72
static inline unsigned bolun_lumia625h_cap_0862_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
