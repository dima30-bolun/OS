#ifndef BOLUN_LUMIA625H_CAP_1133_H
#define BOLUN_LUMIA625H_CAP_1133_H
#define BOLUN_CAP_DEVICE "lumia625h"
#define BOLUN_CAP_SOC "MSM8930"
#define BOLUN_CAP_INDEX 1133
#define BOLUN_CAP_IRQ 109
#define BOLUN_CAP_DMA 5
#define BOLUN_CAP_IDLE_MW 73
static inline unsigned bolun_lumia625h_cap_1133_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
