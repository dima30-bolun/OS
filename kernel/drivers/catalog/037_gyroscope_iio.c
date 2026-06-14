#include "bolun/kernel.h"

/* Catalog module: gyroscope.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-gyroscope_iio",
    .device_class = "gyroscope",
    .bus = BOLUN_BUS_I2C,
    .compatible = "bolun,gyroscope-iio",
    .required_caps = CAP_DEVICE,
    .description = "gyroscope"
};

const bolun_catalog_driver_t *bolun_catalog_gyroscope_iio(void)
{
    return &descriptor;
}

int bolun_catalog_register_gyroscope_iio(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
