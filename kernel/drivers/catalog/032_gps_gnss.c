#include "bolun/kernel.h"

/* Catalog module: GNSS receiver.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-gps_gnss",
    .device_class = "gps",
    .bus = BOLUN_BUS_UART,
    .compatible = "bolun,gnss",
    .required_caps = CAP_DEVICE | CAP_PHONE,
    .description = "GNSS receiver"
};

const bolun_catalog_driver_t *bolun_catalog_gps_gnss(void)
{
    return &descriptor;
}

int bolun_catalog_register_gps_gnss(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
