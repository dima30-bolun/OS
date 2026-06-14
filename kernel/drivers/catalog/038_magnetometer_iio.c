#include "bolun/kernel.h"

/* Catalog module: magnetometer.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-magnetometer_iio",
    .device_class = "magnetometer",
    .bus = BOLUN_BUS_I2C,
    .compatible = "bolun,magnetometer-iio",
    .required_caps = CAP_DEVICE,
    .description = "magnetometer"
};

const bolun_catalog_driver_t *bolun_catalog_magnetometer_iio(void)
{
    return &descriptor;
}

int bolun_catalog_register_magnetometer_iio(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
