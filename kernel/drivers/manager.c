#include "bolun/kernel.h"
#include <string.h>

int bolun_driver_register(const char *name, const char *device_class, uint32_t required_caps)
{
    if (!name || !device_class) {
        return -1;
    }
    for (int i = 0; i < BOLUN_MAX_DRIVERS; i++) {
        bolun_driver_t *d = &g_kernel.drivers[i];
        if (d->name && strcmp(d->name, name) == 0) {
            d->device_class = device_class;
            d->required_caps = required_caps;
            d->active = true;
            return i;
        }
        if (!d->name) {
            d->name = name;
            d->device_class = device_class;
            d->required_caps = required_caps;
            d->active = true;
            return i;
        }
    }
    return -2;
}

const bolun_driver_t *bolun_driver_find(const char *device_class)
{
    if (!device_class) {
        return 0;
    }
    for (int i = 0; i < BOLUN_MAX_DRIVERS; i++) {
        bolun_driver_t *d = &g_kernel.drivers[i];
        if (d->active && d->device_class && strcmp(d->device_class, device_class) == 0) {
            return d;
        }
    }
    return 0;
}

int bolun_device_register(const char *name, bolun_bus_t bus, const char *compatible, const char *driver_class)
{
    if (!name || !compatible || !driver_class) {
        return -1;
    }
    for (int i = 0; i < BOLUN_MAX_DEVICES; i++) {
        bolun_device_t *dev = &g_kernel.devices[i];
        if (dev->name && strcmp(dev->name, name) == 0) {
            dev->bus = bus;
            dev->compatible = compatible;
            dev->driver_class = driver_class;
            return i;
        }
        if (!dev->name) {
            dev->name = name;
            dev->bus = bus;
            dev->compatible = compatible;
            dev->driver_class = driver_class;
            dev->online = false;
            return i;
        }
    }
    return -2;
}

const bolun_device_t *bolun_device_find(const char *name)
{
    if (!name) {
        return 0;
    }
    for (int i = 0; i < BOLUN_MAX_DEVICES; i++) {
        bolun_device_t *dev = &g_kernel.devices[i];
        if (dev->name && strcmp(dev->name, name) == 0) {
            return dev;
        }
    }
    return 0;
}

int bolun_device_bind_all(void)
{
    int bound = 0;
    for (int i = 0; i < BOLUN_MAX_DEVICES; i++) {
        bolun_device_t *dev = &g_kernel.devices[i];
        if (dev->name && bolun_driver_find(dev->driver_class)) {
            dev->online = true;
            bound++;
        }
    }
    return bound;
}
