#include "bolun/kernel.h"

/* Catalog module: TCP network module.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-net_tcp",
    .device_class = "net-tcp",
    .bus = BOLUN_BUS_ROOT,
    .compatible = "bolun,tcp",
    .required_caps = CAP_NET,
    .description = "TCP network module"
};

const bolun_catalog_driver_t *bolun_catalog_net_tcp(void)
{
    return &descriptor;
}

int bolun_catalog_register_net_tcp(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
