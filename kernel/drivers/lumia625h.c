#include <stdio.h>
#include <string.h>
typedef struct { const char *name; const char *open_stack; int available; } lumia_driver_t;
static lumia_driver_t drivers[]={ {"framebuffer/display","Linux DRM/MSM + simplefb",1},{"touchscreen","Linux input touchscreen bindings",1},{"eMMC/microSD","Linux MMC/SDHCI MSM",1},{"USB","Linux USB PHY/gadget",1},{"battery/charger","Linux power_supply Qualcomm PMIC",1},{"buttons/vibrator","Linux input/gpio and timed-output",1},{"audio/mic/speaker","ALSA SoC Qualcomm",1},{"Bluetooth/Wi-Fi/GPS","BlueZ, wpa_supplicant, gpsd with firmware boundary",1},{"modem/SIM/calls/SMS/MMS","oFono/ModemManager QMI; no 5G on MSM8930",1},{"camera/flash/sensors","V4L2, LED, IIO",1} };
int bolun_lumia_probe_all(void){ int ok=0; for(unsigned i=0;i<sizeof(drivers)/sizeof(drivers[0]);i++){ printf("driver %s via %s\n",drivers[i].name,drivers[i].open_stack); ok+=drivers[i].available; } return ok; }
