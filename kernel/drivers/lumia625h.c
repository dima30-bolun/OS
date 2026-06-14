#include "bolun/kernel.h"
#include <stdio.h>
#include <string.h>

typedef struct {
    const char *name;
    const char *open_stack;
    const char *klass;
    bolun_bus_t bus;
    const char *compatible;
    int available;
} lumia_driver_t;

static const lumia_driver_t drivers[] = {
    { "framebuffer/display", "Linux DRM/MSM + simplefb", "display", BOLUN_BUS_DEVICE_TREE, "qcom,msm-fb", 1 },
    { "touchscreen", "Linux input touchscreen bindings", "touch", BOLUN_BUS_I2C, "synaptics,rmi4", 1 },
    { "eMMC/microSD", "Linux MMC/SDHCI MSM", "storage", BOLUN_BUS_DEVICE_TREE, "qcom,sdhci-msm", 1 },
    { "USB/OTG", "Linux USB PHY/gadget", "usb", BOLUN_BUS_USB, "qcom,usb-otg", 1 },
    { "battery/charger", "Linux power_supply Qualcomm PMIC", "power", BOLUN_BUS_DEVICE_TREE, "qcom,pmic-charger", 1 },
    { "buttons/vibrator", "Linux input/gpio and timed-output", "input", BOLUN_BUS_GPIO, "gpio-keys", 1 },
    { "audio/mic/speaker", "ALSA SoC Qualcomm", "audio", BOLUN_BUS_DEVICE_TREE, "qcom,msm-audio", 1 },
    { "Bluetooth/Wi-Fi/GPS", "BlueZ, wpa_supplicant, gpsd with firmware boundary", "radio", BOLUN_BUS_UART, "qcom,wcn36xx", 1 },
    { "modem/SIM/calls/SMS/MMS", "oFono/ModemManager QMI; no 5G on MSM8930", "modem", BOLUN_BUS_USB, "qcom,qmi-modem", 1 },
    { "camera/flash/sensors", "V4L2, LED, IIO", "media", BOLUN_BUS_I2C, "qcom,camera-sensor", 1 }
};

static const bolun_hw_profile_t profiles[] = {
    { "Lumia 520", 0x8227, BOLUN_ARCH_ARMV7, 512, "800x480 IPS", "MSM8x27" },
    { "Lumia 525", 0x8227, BOLUN_ARCH_ARMV7, 1024, "800x480 IPS", "MSM8x27" },
    { "Lumia 620", 0x8227, BOLUN_ARCH_ARMV7, 512, "800x480 ClearBlack", "MSM8x27" },
    { "Lumia 625H", 0x8930, BOLUN_ARCH_ARMV7, 512, "800x480 4.7in IPS", "MSM8930" },
    { "Lumia 720", 0x8227, BOLUN_ARCH_ARMV7, 512, "800x480 ClearBlack", "MSM8x27" },
    { "Lumia 820", 0x8960, BOLUN_ARCH_ARMV7, 1024, "800x480 AMOLED", "MSM8960" },
    { "Lumia 920", 0x8960, BOLUN_ARCH_ARMV7, 1024, "1280x768 IPS", "MSM8960" },
    { "Lumia 925", 0x8960, BOLUN_ARCH_ARMV7, 1024, "1280x768 AMOLED", "MSM8960" },
    { "Lumia 1020", 0x8960, BOLUN_ARCH_ARMV7, 2048, "1280x768 AMOLED", "MSM8960" }
};

const bolun_hw_profile_t *bolun_lumia_profile(const char *model)
{
    if (!model) {
        return 0;
    }
    for (unsigned i = 0; i < sizeof(profiles) / sizeof(profiles[0]); i++) {
        if (strcmp(profiles[i].model, model) == 0) {
            return &profiles[i];
        }
    }
    return 0;
}

int bolun_lumia_probe_all(void)
{
    int ok = 0;
    for (unsigned i = 0; i < sizeof(drivers) / sizeof(drivers[0]); i++) {
        printf("driver %s via %s\n", drivers[i].name, drivers[i].open_stack);
        if (drivers[i].available) {
            bolun_driver_register(drivers[i].name, drivers[i].klass, CAP_DEVICE);
            bolun_device_register(drivers[i].name, drivers[i].bus, drivers[i].compatible, drivers[i].klass);
            ok++;
        }
    }
    bolun_device_bind_all();
    return ok;
}
