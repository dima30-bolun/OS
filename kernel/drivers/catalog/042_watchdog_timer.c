#include "bolun/kernel.h"

/* Catalog module: watchdog.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-watchdog_timer",
    .device_class = "watchdog",
    .bus = BOLUN_BUS_DEVICE_TREE,
    .compatible = "bolun,watchdog",
    .required_caps = CAP_SYSTEM,
    .description = "watchdog"
};

const bolun_catalog_driver_t *bolun_catalog_watchdog_timer(void)
{
    return &descriptor;
}

int bolun_catalog_register_watchdog_timer(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
