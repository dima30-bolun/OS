#include "bolun/kernel.h"

/* Catalog module: LCD backlight PWM policy.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-lcd_backlight",
    .device_class = "backlight",
    .bus = BOLUN_BUS_PWM,
    .compatible = "bolun,lcd-backlight",
    .required_caps = CAP_DEVICE,
    .description = "LCD backlight PWM policy"
};

const bolun_catalog_driver_t *bolun_catalog_lcd_backlight(void)
{
    return &descriptor;
}

int bolun_catalog_register_lcd_backlight(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
