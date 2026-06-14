#include "bolun/kernel.h"

/* Catalog module: USB gadget core.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-usb_device_core",
    .device_class = "usb-device",
    .bus = BOLUN_BUS_USB,
    .compatible = "bolun,usb-device-core",
    .required_caps = CAP_DEVICE,
    .description = "USB gadget core"
};

const bolun_catalog_driver_t *bolun_catalog_usb_device_core(void)
{
    return &descriptor;
}

int bolun_catalog_register_usb_device_core(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
