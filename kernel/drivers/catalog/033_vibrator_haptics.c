#include "bolun/kernel.h"

/* Catalog module: haptics motor.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-vibrator_haptics",
    .device_class = "vibrator",
    .bus = BOLUN_BUS_GPIO,
    .compatible = "bolun,haptics",
    .required_caps = CAP_DEVICE,
    .description = "haptics motor"
};

const bolun_catalog_driver_t *bolun_catalog_vibrator_haptics(void)
{
    return &descriptor;
}

int bolun_catalog_register_vibrator_haptics(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
