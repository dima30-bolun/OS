#include "bolun/kernel.h"

/* Catalog module: eMMC storage.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-emmc_storage",
    .device_class = "emmc",
    .bus = BOLUN_BUS_DEVICE_TREE,
    .compatible = "bolun,emmc-storage",
    .required_caps = CAP_DEVICE | CAP_FS,
    .description = "eMMC storage"
};

const bolun_catalog_driver_t *bolun_catalog_emmc_storage(void)
{
    return &descriptor;
}

int bolun_catalog_register_emmc_storage(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
