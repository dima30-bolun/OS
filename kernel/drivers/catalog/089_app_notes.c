#include "bolun/kernel.h"

/* Catalog module: notes built-in app module.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-app_notes",
    .device_class = "app-notes",
    .bus = BOLUN_BUS_ROOT,
    .compatible = "bolun,notes",
    .required_caps = CAP_SYSTEM,
    .description = "notes built-in app module"
};

const bolun_catalog_driver_t *bolun_catalog_app_notes(void)
{
    return &descriptor;
}

int bolun_catalog_register_app_notes(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
