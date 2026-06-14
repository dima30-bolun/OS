#include "bolun/kernel.h"

/* Catalog module: speaker amplifier policy.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-speaker_amp",
    .device_class = "speaker",
    .bus = BOLUN_BUS_GPIO,
    .compatible = "bolun,speaker-amplifier",
    .required_caps = CAP_DEVICE,
    .description = "speaker amplifier policy"
};

const bolun_catalog_driver_t *bolun_catalog_speaker_amp(void)
{
    return &descriptor;
}

int bolun_catalog_register_speaker_amp(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
