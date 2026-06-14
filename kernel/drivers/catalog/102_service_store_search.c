#include "bolun/kernel.h"

/* Catalog module: store_search service module.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-service_store_search",
    .device_class = "service-store_search",
    .bus = BOLUN_BUS_ROOT,
    .compatible = "bolun,store_search",
    .required_caps = CAP_SYSTEM,
    .description = "store_search service module"
};

const bolun_catalog_driver_t *bolun_catalog_service_store_search(void)
{
    return &descriptor;
}

int bolun_catalog_register_service_store_search(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
