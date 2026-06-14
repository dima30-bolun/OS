#include "bolun/kernel.h"

/* Catalog module: NFC NCI.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-nfc_nci",
    .device_class = "nfc",
    .bus = BOLUN_BUS_I2C,
    .compatible = "bolun,nfc-nci",
    .required_caps = CAP_DEVICE,
    .description = "NFC NCI"
};

const bolun_catalog_driver_t *bolun_catalog_nfc_nci(void)
{
    return &descriptor;
}

int bolun_catalog_register_nfc_nci(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
