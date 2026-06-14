#include "bolun/kernel.h"

/* Catalog module: IPV6 network module.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-net_ipv6",
    .device_class = "net-ipv6",
    .bus = BOLUN_BUS_ROOT,
    .compatible = "bolun,ipv6",
    .required_caps = CAP_NET,
    .description = "IPV6 network module"
};

const bolun_catalog_driver_t *bolun_catalog_net_ipv6(void)
{
    return &descriptor;
}

int bolun_catalog_register_net_ipv6(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
