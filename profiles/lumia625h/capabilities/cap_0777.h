#ifndef BOLUN_LUMIA625H_CAP_0777_H
#define BOLUN_LUMIA625H_CAP_0777_H
#define BOLUN_CAP_DEVICE "lumia625h"
#define BOLUN_CAP_SOC "MSM8930"
#define BOLUN_CAP_INDEX 777
#define BOLUN_CAP_IRQ 41
#define BOLUN_CAP_DMA 1
#define BOLUN_CAP_IDLE_MW 77
static inline unsigned bolun_lumia625h_cap_0777_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
