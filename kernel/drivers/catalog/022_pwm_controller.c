#include "bolun/kernel.h"

/* Catalog module: PWM controller.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-pwm_controller",
    .device_class = "pwm",
    .bus = BOLUN_BUS_PWM,
    .compatible = "bolun,pwm-controller",
    .required_caps = CAP_DEVICE,
    .description = "PWM controller"
};

const bolun_catalog_driver_t *bolun_catalog_pwm_controller(void)
{
    return &descriptor;
}

int bolun_catalog_register_pwm_controller(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
