#include "bolun/kernel.h"

/* Catalog module: GPU command queue boundary.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-gpu_command",
    .device_class = "gpu",
    .bus = BOLUN_BUS_DEVICE_TREE,
    .compatible = "bolun,gpu-command",
    .required_caps = CAP_DEVICE,
    .description = "GPU command queue boundary"
};

const bolun_catalog_driver_t *bolun_catalog_gpu_command(void)
{
    return &descriptor;
}

int bolun_catalog_register_gpu_command(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
