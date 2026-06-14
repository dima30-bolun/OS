#include "bolun/kernel.h"

/* Catalog module: bootscreen GUI module.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-gui_bootscreen",
    .device_class = "gui-bootscreen",
    .bus = BOLUN_BUS_ROOT,
    .compatible = "bolun,bootscreen",
    .required_caps = CAP_DEVICE,
    .description = "bootscreen GUI module"
};

const bolun_catalog_driver_t *bolun_catalog_gui_bootscreen(void)
{
    return &descriptor;
}

int bolun_catalog_register_gui_bootscreen(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
