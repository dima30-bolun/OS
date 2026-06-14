#include "bolun/kernel.h"

/* Catalog module: USB OTG role switching.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-usb_otg",
    .device_class = "usb-otg",
    .bus = BOLUN_BUS_USB,
    .compatible = "bolun,usb-otg",
    .required_caps = CAP_DEVICE,
    .description = "USB OTG role switching"
};

const bolun_catalog_driver_t *bolun_catalog_usb_otg(void)
{
    return &descriptor;
}

int bolun_catalog_register_usb_otg(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
