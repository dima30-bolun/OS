#include "bolun/kernel.h"

/* Catalog module: RTC clock.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-rtc_clock",
    .device_class = "rtc",
    .bus = BOLUN_BUS_RTC,
    .compatible = "bolun,rtc-clock",
    .required_caps = CAP_DEVICE | CAP_SYSTEM,
    .description = "RTC clock"
};

const bolun_catalog_driver_t *bolun_catalog_rtc_clock(void)
{
    return &descriptor;
}

int bolun_catalog_register_rtc_clock(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
