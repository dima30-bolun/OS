#include "bolun/kernel.h"

/* Catalog module: block_cache filesystem module.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-fs_block_cache",
    .device_class = "fs-block_cache",
    .bus = BOLUN_BUS_ROOT,
    .compatible = "bolun,block_cache",
    .required_caps = CAP_FS,
    .description = "block_cache filesystem module"
};

const bolun_catalog_driver_t *bolun_catalog_fs_block_cache(void)
{
    return &descriptor;
}

int bolun_catalog_register_fs_block_cache(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
