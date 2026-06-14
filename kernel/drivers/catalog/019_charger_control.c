#include "bolun/kernel.h"

/* Catalog module: charger control.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-charger_control",
    .device_class = "charger",
    .bus = BOLUN_BUS_DEVICE_TREE,
    .compatible = "bolun,charger-control",
    .required_caps = CAP_DEVICE | CAP_SYSTEM,
    .description = "charger control"
};

const bolun_catalog_driver_t *bolun_catalog_charger_control(void)
{
    return &descriptor;
}

int bolun_catalog_register_charger_control(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
