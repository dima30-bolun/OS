#include "bolun/kernel.h"
#include <stdio.h>
#include <string.h>

typedef enum {
    LUMIA_NEEDS_OPEN_BINDINGS,
    LUMIA_NEEDS_VENDOR_DOCUMENTATION
} lumia_enablement_t;

typedef struct {
    const char *name;
    const char *open_stack;
    const char *klass;
    bolun_bus_t bus;
    const char *compatible;
    uint32_t caps;
    lumia_enablement_t enablement;
} lumia_driver_t;

static const lumia_driver_t drivers[] = {
    { "display", "DRM/KMS panel bridge model", "display", BOLUN_BUS_DEVICE_TREE, "bolun,display-panel", CAP_DEVICE, LUMIA_NEEDS_VENDOR_DOCUMENTATION },
    { "touchscreen", "Linux input multi-touch model", "touch", BOLUN_BUS_I2C, "synaptics,rmi4", CAP_DEVICE, LUMIA_NEEDS_VENDOR_DOCUMENTATION },
    { "framebuffer", "simplefb-compatible boot framebuffer", "framebuffer", BOLUN_BUS_DEVICE_TREE, "simple-framebuffer", CAP_DEVICE, LUMIA_NEEDS_OPEN_BINDINGS },
    { "gpu", "DRM/MSM userspace boundary", "gpu", BOLUN_BUS_DEVICE_TREE, "qcom,adreno-305", CAP_DEVICE, LUMIA_NEEDS_VENDOR_DOCUMENTATION },
    { "audio-codec", "ALSA SoC codec boundary", "audio-codec", BOLUN_BUS_DEVICE_TREE, "qcom,pmic-audio-codec", CAP_DEVICE, LUMIA_NEEDS_VENDOR_DOCUMENTATION },
    { "audio-output", "ALSA PCM playback boundary", "audio-output", BOLUN_BUS_DEVICE_TREE, "qcom,msm-audio-out", CAP_DEVICE, LUMIA_NEEDS_VENDOR_DOCUMENTATION },
    { "microphone", "ALSA PCM capture boundary", "microphone", BOLUN_BUS_DEVICE_TREE, "qcom,msm-audio-in", CAP_DEVICE, LUMIA_NEEDS_VENDOR_DOCUMENTATION },
    { "camera", "V4L2 camera sensor pipeline", "camera", BOLUN_BUS_I2C, "qcom,camera-sensor", CAP_DEVICE, LUMIA_NEEDS_VENDOR_DOCUMENTATION },
    { "usb-host", "USB host controller model", "usb-host", BOLUN_BUS_USB, "qcom,usb-host", CAP_DEVICE, LUMIA_NEEDS_OPEN_BINDINGS },
    { "usb-device", "USB gadget/device model", "usb-device", BOLUN_BUS_USB, "qcom,usb-gadget", CAP_DEVICE, LUMIA_NEEDS_OPEN_BINDINGS },
    { "battery", "power_supply battery boundary", "battery", BOLUN_BUS_DEVICE_TREE, "qcom,pmic-battery", CAP_DEVICE | CAP_SYSTEM, LUMIA_NEEDS_VENDOR_DOCUMENTATION },
    { "charger", "power_supply charger boundary", "charger", BOLUN_BUS_DEVICE_TREE, "qcom,pmic-charger", CAP_DEVICE | CAP_SYSTEM, LUMIA_NEEDS_VENDOR_DOCUMENTATION },
    { "power-management", "PMIC regulator and suspend model", "power-management", BOLUN_BUS_DEVICE_TREE, "qcom,pmic-pm", CAP_DEVICE | CAP_SYSTEM, LUMIA_NEEDS_VENDOR_DOCUMENTATION },
    { "rtc", "RTC class boundary", "rtc", BOLUN_BUS_RTC, "qcom,pmic-rtc", CAP_DEVICE | CAP_SYSTEM, LUMIA_NEEDS_VENDOR_DOCUMENTATION },
    { "gpio", "gpiolib-style controller", "gpio", BOLUN_BUS_GPIO, "qcom,msm-gpio", CAP_DEVICE, LUMIA_NEEDS_OPEN_BINDINGS },
    { "pwm", "PWM controller boundary", "pwm", BOLUN_BUS_PWM, "qcom,pmic-pwm", CAP_DEVICE, LUMIA_NEEDS_VENDOR_DOCUMENTATION },
    { "timers", "HAL timer source", "timers", BOLUN_BUS_DEVICE_TREE, "arm,architected-timer", CAP_SYSTEM, LUMIA_NEEDS_OPEN_BINDINGS },
    { "watchdog", "watchdog class boundary", "watchdog", BOLUN_BUS_DEVICE_TREE, "qcom,msm-watchdog", CAP_SYSTEM, LUMIA_NEEDS_OPEN_BINDINGS },
    { "emmc", "MMC/SDHCI MSM storage", "emmc", BOLUN_BUS_DEVICE_TREE, "qcom,sdhci-msm-emmc", CAP_DEVICE | CAP_FS, LUMIA_NEEDS_OPEN_BINDINGS },
    { "sd-card", "removable MMC/SDHCI storage", "sd-card", BOLUN_BUS_DEVICE_TREE, "qcom,sdhci-msm-sdcard", CAP_DEVICE | CAP_FS, LUMIA_NEEDS_OPEN_BINDINGS },
    { "nand", "MTD raw NAND boundary", "nand", BOLUN_BUS_DEVICE_TREE, "bolun,nand-optional", CAP_DEVICE | CAP_FS, LUMIA_NEEDS_VENDOR_DOCUMENTATION },
    { "spi", "SPI controller model", "spi", BOLUN_BUS_SPI, "qcom,spi-qup", CAP_DEVICE, LUMIA_NEEDS_OPEN_BINDINGS },
    { "i2c", "I2C controller model", "i2c", BOLUN_BUS_I2C, "qcom,i2c-qup", CAP_DEVICE, LUMIA_NEEDS_OPEN_BINDINGS },
    { "uart", "UART serial controller", "uart", BOLUN_BUS_UART, "qcom,msm-uart", CAP_DEVICE, LUMIA_NEEDS_OPEN_BINDINGS },
    { "bluetooth", "BlueZ HCI firmware boundary", "bluetooth", BOLUN_BUS_UART, "qcom,wcn-bluetooth", CAP_DEVICE | CAP_NET, LUMIA_NEEDS_VENDOR_DOCUMENTATION },
    { "wi-fi", "cfg80211/wpa_supplicant boundary", "wi-fi", BOLUN_BUS_DEVICE_TREE, "qcom,wcn36xx", CAP_DEVICE | CAP_NET, LUMIA_NEEDS_VENDOR_DOCUMENTATION },
    { "gps", "GNSS daemon serial/QMI boundary", "gps", BOLUN_BUS_UART, "qcom,gnss", CAP_DEVICE | CAP_PHONE, LUMIA_NEEDS_VENDOR_DOCUMENTATION },
    { "gsm-lte-modem", "QMI modem boundary", "modem", BOLUN_BUS_USB, "qcom,qmi-modem", CAP_DEVICE | CAP_PHONE | CAP_NET, LUMIA_NEEDS_VENDOR_DOCUMENTATION },
    { "nfc", "NCI controller boundary", "nfc", BOLUN_BUS_I2C, "bolun,nfc-controller", CAP_DEVICE, LUMIA_NEEDS_VENDOR_DOCUMENTATION },
 codex/analyze-and-implement-missing-drivers-spk9ne
    { "magnetometer", "IIO magnetometer boundary", "magnetometer", BOLUN_BUS_I2C, "bolun,magnetometer", CAP_DEVICE, LUMIA_NEEDS_VENDOR_DOCUMENTATION },
=======
 codex/analyze-and-implement-missing-drivers-ph242g
    { "magnetometer", "IIO magnetometer boundary", "magnetometer", BOLUN_BUS_I2C, "bolun,magnetometer", CAP_DEVICE, LUMIA_NEEDS_VENDOR_DOCUMENTATION },
=======
 main
 main
    { "accelerometer", "IIO accelerometer boundary", "accelerometer", BOLUN_BUS_I2C, "bolun,accelerometer", CAP_DEVICE, LUMIA_NEEDS_VENDOR_DOCUMENTATION },
    { "gyroscope", "IIO gyroscope boundary", "gyroscope", BOLUN_BUS_I2C, "bolun,gyroscope", CAP_DEVICE, LUMIA_NEEDS_VENDOR_DOCUMENTATION },
    { "proximity-sensor", "IIO proximity boundary", "proximity", BOLUN_BUS_I2C, "bolun,proximity-sensor", CAP_DEVICE, LUMIA_NEEDS_VENDOR_DOCUMENTATION },
    { "ambient-light-sensor", "IIO light sensor boundary", "ambient-light", BOLUN_BUS_I2C, "bolun,ambient-light-sensor", CAP_DEVICE, LUMIA_NEEDS_VENDOR_DOCUMENTATION },
    { "vibration-motor", "timed-output/haptics boundary", "vibrator", BOLUN_BUS_GPIO, "bolun,vibration-motor", CAP_DEVICE, LUMIA_NEEDS_VENDOR_DOCUMENTATION },
    { "leds", "LED class device boundary", "leds", BOLUN_BUS_GPIO, "gpio-leds", CAP_DEVICE, LUMIA_NEEDS_OPEN_BINDINGS },
    { "buttons", "gpio-keys input boundary", "buttons", BOLUN_BUS_GPIO, "gpio-keys", CAP_DEVICE, LUMIA_NEEDS_OPEN_BINDINGS }
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
    { "Lumia 1020", 0x8960, BOLUN_ARCH_ARMV7, 2048, "1280x768 AMOLED", "MSM8960" },
    { "Redmi 9A", 0x6762, BOLUN_ARCH_ARM64, 2048, "1600x720 IPS", "MediaTek Helio G25/MT6762G" },
    { "Redmi 9C NFC", 0x6765, BOLUN_ARCH_ARM64, 2048, "1600x720 IPS", "MediaTek Helio G35/MT6765" }
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

size_t bolun_lumia_driver_count(void)
{
    return sizeof(drivers) / sizeof(drivers[0]);
}

int bolun_lumia_probe_all(void)
{
    int ok = 0;
    for (unsigned i = 0; i < sizeof(drivers) / sizeof(drivers[0]); i++) {
        const char *state = drivers[i].enablement == LUMIA_NEEDS_OPEN_BINDINGS ?
            "open binding" : "requires manufacturer documentation or reverse engineering";
        printf("driver %s via %s (%s)\n", drivers[i].name, drivers[i].open_stack, state);
        int did = bolun_driver_register(drivers[i].name, drivers[i].klass, drivers[i].caps);
        int devid = bolun_device_register(drivers[i].name, drivers[i].bus, drivers[i].compatible, drivers[i].klass);
        if (did >= 0 && devid >= 0) {
            ok++;
        }
    }
    bolun_device_bind_all();
    return ok;
}
