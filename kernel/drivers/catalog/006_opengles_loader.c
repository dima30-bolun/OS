#include "bolun/kernel.h"

/* Catalog module: OpenGL ES userspace handoff.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-opengles_loader",
    .device_class = "opengles",
    .bus = BOLUN_BUS_DEVICE_TREE,
    .compatible = "bolun,opengles-loader",
    .required_caps = CAP_DEVICE,
    .description = "OpenGL ES userspace handoff"
};

const bolun_catalog_driver_t *bolun_catalog_opengles_loader(void)
{
    return &descriptor;
}

int bolun_catalog_register_opengles_loader(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
