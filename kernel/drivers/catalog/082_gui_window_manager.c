#include "bolun/kernel.h"

/* Catalog module: window_manager GUI module.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-gui_window_manager",
    .device_class = "gui-window_manager",
    .bus = BOLUN_BUS_ROOT,
    .compatible = "bolun,window_manager",
    .required_caps = CAP_DEVICE,
    .description = "window_manager GUI module"
};

const bolun_catalog_driver_t *bolun_catalog_gui_window_manager(void)
{
    return &descriptor;
}

int bolun_catalog_register_gui_window_manager(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
