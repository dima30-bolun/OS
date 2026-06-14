#ifndef BOLUN_LUMIA625H_CAP_1598_H
#define BOLUN_LUMIA625H_CAP_1598_H
#define BOLUN_CAP_DEVICE "lumia625h"
#define BOLUN_CAP_SOC "MSM8930"
#define BOLUN_CAP_INDEX 1598
#define BOLUN_CAP_IRQ 94
#define BOLUN_CAP_DMA 6
#define BOLUN_CAP_IDLE_MW 88
static inline unsigned bolun_lumia625h_cap_1598_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
