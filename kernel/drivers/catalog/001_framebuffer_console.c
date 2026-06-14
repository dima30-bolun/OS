#include "bolun/kernel.h"

/* Catalog module: boot framebuffer console.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-framebuffer_console",
    .device_class = "framebuffer",
    .bus = BOLUN_BUS_DEVICE_TREE,
    .compatible = "simple-framebuffer",
    .required_caps = CAP_DEVICE,
    .description = "boot framebuffer console"
};

const bolun_catalog_driver_t *bolun_catalog_framebuffer_console(void)
{
    return &descriptor;
}

int bolun_catalog_register_framebuffer_console(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
