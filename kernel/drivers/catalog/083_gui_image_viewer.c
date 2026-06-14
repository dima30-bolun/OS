#include "bolun/kernel.h"

/* Catalog module: image_viewer GUI module.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-gui_image_viewer",
    .device_class = "gui-image_viewer",
    .bus = BOLUN_BUS_ROOT,
    .compatible = "bolun,image_viewer",
    .required_caps = CAP_DEVICE,
    .description = "image_viewer GUI module"
};

const bolun_catalog_driver_t *bolun_catalog_gui_image_viewer(void)
{
    return &descriptor;
}

int bolun_catalog_register_gui_image_viewer(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
