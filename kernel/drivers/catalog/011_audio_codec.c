#include "bolun/kernel.h"

/* Catalog module: audio codec controls.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-audio_codec",
    .device_class = "audio-codec",
    .bus = BOLUN_BUS_DEVICE_TREE,
    .compatible = "bolun,audio-codec",
    .required_caps = CAP_DEVICE,
    .description = "audio codec controls"
};

const bolun_catalog_driver_t *bolun_catalog_audio_codec(void)
{
    return &descriptor;
}

int bolun_catalog_register_audio_codec(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
