#ifndef BOLUN_LUMIA520_CAP_0208_H
#define BOLUN_LUMIA520_CAP_0208_H
#define BOLUN_CAP_DEVICE "lumia520"
#define BOLUN_CAP_SOC "MSM8227"
#define BOLUN_CAP_INDEX 208
#define BOLUN_CAP_IRQ 48
#define BOLUN_CAP_DMA 0
#define BOLUN_CAP_IDLE_MW 48
static inline unsigned bolun_lumia520_cap_0208_score(unsigned battery_percent) {
    return (battery_percent * 100u) / (BOLUN_CAP_IDLE_MW + 1u);
}
#endif
