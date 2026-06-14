#include "bolun/kernel.h"

/* Catalog module: SOCKET network module.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-net_socket",
    .device_class = "net-socket",
    .bus = BOLUN_BUS_ROOT,
    .compatible = "bolun,socket",
    .required_caps = CAP_NET,
    .description = "SOCKET network module"
};

const bolun_catalog_driver_t *bolun_catalog_net_socket(void)
{
    return &descriptor;
}

int bolun_catalog_register_net_socket(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
