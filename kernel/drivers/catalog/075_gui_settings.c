#include "bolun/kernel.h"

/* Catalog module: settings GUI module.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-gui_settings",
    .device_class = "gui-settings",
    .bus = BOLUN_BUS_ROOT,
    .compatible = "bolun,settings",
    .required_caps = CAP_DEVICE,
    .description = "settings GUI module"
};

const bolun_catalog_driver_t *bolun_catalog_gui_settings(void)
{
    return &descriptor;
}

int bolun_catalog_register_gui_settings(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
