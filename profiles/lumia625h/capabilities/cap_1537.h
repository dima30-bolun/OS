#ifndef BOLUN_LUMIA625H_CAP_1537_H
#define BOLUN_LUMIA625H_CAP_1537_H
#define BOLUN_CAP_DEVICE "lumia625h"
#define BOLUN_CAP_SOC "MSM8930"
#define BOLUN_CAP_INDEX 1537
#define BOLUN_CAP_IRQ 33
#define BOLUN_CAP_DMA 1
#define BOLUN_CAP_IDLE_MW 27
static inline unsigned bolun_lumia625h_cap_1537_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
