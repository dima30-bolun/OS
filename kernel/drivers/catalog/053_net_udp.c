#include "bolun/kernel.h"

/* Catalog module: UDP network module.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-net_udp",
    .device_class = "net-udp",
    .bus = BOLUN_BUS_ROOT,
    .compatible = "bolun,udp",
    .required_caps = CAP_NET,
    .description = "UDP network module"
};

const bolun_catalog_driver_t *bolun_catalog_net_udp(void)
{
    return &descriptor;
}

int bolun_catalog_register_net_udp(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
