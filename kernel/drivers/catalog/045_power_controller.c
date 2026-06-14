#include "bolun/kernel.h"

/* Catalog module: power controller.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-power_controller",
    .device_class = "power-controller",
    .bus = BOLUN_BUS_DEVICE_TREE,
    .compatible = "bolun,power-controller",
    .required_caps = CAP_DEVICE | CAP_SYSTEM,
    .description = "power controller"
};

const bolun_catalog_driver_t *bolun_catalog_power_controller(void)
{
    return &descriptor;
}

int bolun_catalog_register_power_controller(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
