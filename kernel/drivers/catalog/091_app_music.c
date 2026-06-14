#include "bolun/kernel.h"

/* Catalog module: music built-in app module.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-app_music",
    .device_class = "app-music",
    .bus = BOLUN_BUS_ROOT,
    .compatible = "bolun,music",
    .required_caps = CAP_SYSTEM,
    .description = "music built-in app module"
};

const bolun_catalog_driver_t *bolun_catalog_app_music(void)
{
    return &descriptor;
}

int bolun_catalog_register_app_music(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
