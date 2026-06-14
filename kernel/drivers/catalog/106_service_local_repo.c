#include "bolun/kernel.h"

/* Catalog module: local_repo service module.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-service_local_repo",
    .device_class = "service-local_repo",
    .bus = BOLUN_BUS_ROOT,
    .compatible = "bolun,local_repo",
    .required_caps = CAP_SYSTEM,
    .description = "local_repo service module"
};

const bolun_catalog_driver_t *bolun_catalog_service_local_repo(void)
{
    return &descriptor;
}

int bolun_catalog_register_service_local_repo(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
