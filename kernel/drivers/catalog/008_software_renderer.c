#include "bolun/kernel.h"

/* Catalog module: portable software renderer.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-software_renderer",
    .device_class = "renderer",
    .bus = BOLUN_BUS_ROOT,
    .compatible = "bolun,software-renderer",
    .required_caps = CAP_DEVICE,
    .description = "portable software renderer"
};

const bolun_catalog_driver_t *bolun_catalog_software_renderer(void)
{
    return &descriptor;
}

int bolun_catalog_register_software_renderer(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
