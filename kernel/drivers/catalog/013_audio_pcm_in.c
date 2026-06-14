#include "bolun/kernel.h"

/* Catalog module: PCM capture engine.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-audio_pcm_in",
    .device_class = "microphone",
    .bus = BOLUN_BUS_DEVICE_TREE,
    .compatible = "bolun,pcm-input",
    .required_caps = CAP_DEVICE,
    .description = "PCM capture engine"
};

const bolun_catalog_driver_t *bolun_catalog_audio_pcm_in(void)
{
    return &descriptor;
}

int bolun_catalog_register_audio_pcm_in(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
