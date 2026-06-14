#include "bolun/kernel.h"

/* Catalog module: UART controller.
 * This module is compiled into the host kernel and registers a portable
 * device boundary without embedding undocumented board registers.
 */
static const bolun_catalog_driver_t descriptor = {
    .name = "catalog-uart_controller",
    .device_class = "uart",
    .bus = BOLUN_BUS_UART,
    .compatible = "bolun,uart-controller",
    .required_caps = CAP_DEVICE,
    .description = "UART controller"
};

const bolun_catalog_driver_t *bolun_catalog_uart_controller(void)
{
    return &descriptor;
}

int bolun_catalog_register_uart_controller(void)
{
    int driver = bolun_driver_register(descriptor.name, descriptor.device_class, descriptor.required_caps);
    int device = bolun_device_register(descriptor.name, descriptor.bus, descriptor.compatible, descriptor.device_class);
    return driver >= 0 && device >= 0 ? 0 : -1;
}
