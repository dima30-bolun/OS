#include "bolun/kernel.h"

/* Catalog module: display panel sequencing boundary.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-display_panel",
    .device_class = "display",
    .bus = BOLUN_BUS_DEVICE_TREE,
    .compatible = "bolun,display-panel-portable",
    .required_caps = CAP_DEVICE,
    .description = "display panel sequencing boundary"
};

const bolun_catalog_driver_t *bolun_catalog_display_panel(void)
{
    return &descriptor;
}

int bolun_catalog_register_display_panel(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
