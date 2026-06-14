#include "bolun/kernel.h"

/* Catalog module: fat32_mount filesystem module.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-fs_fat32_mount",
    .device_class = "fs-fat32_mount",
    .bus = BOLUN_BUS_ROOT,
    .compatible = "bolun,fat32_mount",
    .required_caps = CAP_FS,
    .description = "fat32_mount filesystem module"
};

const bolun_catalog_driver_t *bolun_catalog_fs_fat32_mount(void)
{
    return &descriptor;
}

int bolun_catalog_register_fs_fat32_mount(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
