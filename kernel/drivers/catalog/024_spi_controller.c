#include "bolun/kernel.h"

/* Catalog module: SPI controller.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-spi_controller",
    .device_class = "spi",
    .bus = BOLUN_BUS_SPI,
    .compatible = "bolun,spi-controller",
    .required_caps = CAP_DEVICE,
    .description = "SPI controller"
};

const bolun_catalog_driver_t *bolun_catalog_spi_controller(void)
{
    return &descriptor;
}

int bolun_catalog_register_spi_controller(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
