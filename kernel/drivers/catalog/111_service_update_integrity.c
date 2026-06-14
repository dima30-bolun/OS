#include "bolun/kernel.h"

/* Catalog module: update_integrity service module.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-service_update_integrity",
    .device_class = "service-update_integrity",
    .bus = BOLUN_BUS_ROOT,
    .compatible = "bolun,update_integrity",
    .required_caps = CAP_SYSTEM,
    .description = "update_integrity service module"
};

const bolun_catalog_driver_t *bolun_catalog_service_update_integrity(void)
{
    return &descriptor;
}

int bolun_catalog_register_service_update_integrity(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
