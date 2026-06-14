#include "bolun/kernel.h"

/* Catalog module: memory controller.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-memory_controller",
    .device_class = "memory-controller",
    .bus = BOLUN_BUS_DEVICE_TREE,
    .compatible = "bolun,memory-controller",
    .required_caps = CAP_SYSTEM,
    .description = "memory controller"
};

const bolun_catalog_driver_t *bolun_catalog_memory_controller(void)
{
    return &descriptor;
}

int bolun_catalog_register_memory_controller(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
