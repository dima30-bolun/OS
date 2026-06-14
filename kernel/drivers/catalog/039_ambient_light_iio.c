#include "bolun/kernel.h"

/* Catalog module: ambient light sensor.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-ambient_light_iio",
    .device_class = "ambient-light",
    .bus = BOLUN_BUS_I2C,
    .compatible = "bolun,ambient-light-iio",
    .required_caps = CAP_DEVICE,
    .description = "ambient light sensor"
};

const bolun_catalog_driver_t *bolun_catalog_ambient_light_iio(void)
{
    return &descriptor;
}

int bolun_catalog_register_ambient_light_iio(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
