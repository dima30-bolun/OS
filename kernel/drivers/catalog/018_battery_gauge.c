#include "bolun/kernel.h"

/* Catalog module: battery gauge.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-battery_gauge",
    .device_class = "battery",
    .bus = BOLUN_BUS_DEVICE_TREE,
    .compatible = "bolun,battery-gauge",
    .required_caps = CAP_DEVICE | CAP_SYSTEM,
    .description = "battery gauge"
};

const bolun_catalog_driver_t *bolun_catalog_battery_gauge(void)
{
    return &descriptor;
}

int bolun_catalog_register_battery_gauge(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
