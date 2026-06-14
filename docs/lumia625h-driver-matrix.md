# Lumia 625H portable driver matrix

MainOS now registers every phone-class device requested by the Lumia 625H port through the existing Driver Manager and Device Manager. The implementation is intentionally data-driven: each entry declares a driver name, class, bus, compatible string, capability mask, and open integration boundary. The host build can bind these devices without programming undocumented registers.

Hardware enablement remains split into two categories:

- **Open binding**: the class can be brought up through public OS concepts such as simple framebuffer, USB host/gadget, SDHCI/MMC, GPIO keys, LEDs, UART, SPI, I2C, timers, or watchdog controller models once board resources are known.
- **Requires manufacturer documentation or reverse engineering**: the class needs panel sequencing, PMIC, codec, radio firmware, modem, GNSS, camera, sensor, haptics, or calibration details that are not encoded as invented constants in MainOS.

## Registered classes

| Driver | Class | Bus | Boundary |
| --- | --- | --- | --- |
| display | display | Device Tree | DRM/KMS panel bridge model |
| touchscreen | touch | I2C | Linux input multi-touch model |
| framebuffer | framebuffer | Device Tree | simplefb-compatible boot framebuffer |
| gpu | gpu | Device Tree | DRM/MSM userspace boundary |
| audio-codec | audio-codec | Device Tree | ALSA SoC codec boundary |
| audio-output | audio-output | Device Tree | ALSA PCM playback boundary |
| microphone | microphone | Device Tree | ALSA PCM capture boundary |
| camera | camera | I2C | V4L2 camera sensor pipeline |
| usb-host | usb-host | USB | USB host controller model |
| usb-device | usb-device | USB | USB gadget/device model |
| battery | battery | Device Tree | power_supply battery boundary |
| charger | charger | Device Tree | power_supply charger boundary |
| power-management | power-management | Device Tree | PMIC regulator and suspend model |
| rtc | rtc | RTC | RTC class boundary |
| gpio | gpio | GPIO | gpiolib-style controller |
| pwm | pwm | PWM | PWM controller boundary |
| timers | timers | Device Tree | HAL timer source |
| watchdog | watchdog | Device Tree | watchdog class boundary |
| emmc | emmc | Device Tree | MMC/SDHCI MSM storage |
| sd-card | sd-card | Device Tree | removable MMC/SDHCI storage |
| nand | nand | Device Tree | MTD raw NAND boundary |
| spi | spi | SPI | SPI controller model |
| i2c | i2c | I2C | I2C controller model |
| uart | uart | UART | UART serial controller |
| bluetooth | bluetooth | UART | BlueZ HCI firmware boundary |
| wi-fi | wi-fi | Device Tree | cfg80211/wpa_supplicant boundary |
| gps | gps | UART | GNSS daemon serial/QMI boundary |
| gsm-lte-modem | modem | USB | QMI modem boundary |
| nfc | nfc | I2C | NCI controller boundary |
| accelerometer | accelerometer | I2C | IIO accelerometer boundary |
| gyroscope | gyroscope | I2C | IIO gyroscope boundary |
| proximity-sensor | proximity | I2C | IIO proximity boundary |
| ambient-light-sensor | ambient-light | I2C | IIO light sensor boundary |
| vibration-motor | vibrator | GPIO | timed-output/haptics boundary |
| leds | leds | GPIO | LED class device boundary |
| buttons | buttons | GPIO | gpio-keys input boundary |

The matrix deliberately avoids board-private register values. A production port should replace compatible strings and resource data with values from official documentation, a legally obtained device tree, or measured reverse-engineering notes.
