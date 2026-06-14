#include "bolun/kernel.h"

/* Catalog module: Bluetooth HCI.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-bluetooth_hci",
    .device_class = "bluetooth",
    .bus = BOLUN_BUS_UART,
    .compatible = "bolun,bluetooth-hci",
    .required_caps = CAP_DEVICE | CAP_NET,
    .description = "Bluetooth HCI"
};

const bolun_catalog_driver_t *bolun_catalog_bluetooth_hci(void)
{
    return &descriptor;
}

int bolun_catalog_register_bluetooth_hci(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
