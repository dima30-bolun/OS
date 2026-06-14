#include "bolun/kernel.h"

/* Catalog module: LED class.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-led_class",
    .device_class = "leds",
    .bus = BOLUN_BUS_GPIO,
    .compatible = "bolun,led-class",
    .required_caps = CAP_DEVICE,
    .description = "LED class"
};

const bolun_catalog_driver_t *bolun_catalog_led_class(void)
{
    return &descriptor;
}

int bolun_catalog_register_led_class(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
