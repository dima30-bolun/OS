#include "bolun/kernel.h"

/* Catalog module: Wi-Fi radio.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-wifi_radio",
    .device_class = "wi-fi",
    .bus = BOLUN_BUS_DEVICE_TREE,
    .compatible = "bolun,wifi-radio",
    .required_caps = CAP_DEVICE | CAP_NET,
    .description = "Wi-Fi radio"
};

const bolun_catalog_driver_t *bolun_catalog_wifi_radio(void)
{
    return &descriptor;
}

int bolun_catalog_register_wifi_radio(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
