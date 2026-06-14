#include "bolun/kernel.h"

/* Catalog module: MIPI DSI host boundary.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-mipi_dsi_host",
    .device_class = "mipi-dsi",
    .bus = BOLUN_BUS_DEVICE_TREE,
    .compatible = "bolun,mipi-dsi-host",
    .required_caps = CAP_DEVICE,
    .description = "MIPI DSI host boundary"
};

const bolun_catalog_driver_t *bolun_catalog_mipi_dsi_host(void)
{
    return &descriptor;
}

int bolun_catalog_register_mipi_dsi_host(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
