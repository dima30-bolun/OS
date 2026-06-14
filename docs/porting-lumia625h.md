# Lumia 625H porting notes

The port targets Qualcomm MSM8930 ARMv7 with Adreno 305. Only MainOS payload generation is in scope. EFIESP, DPP, MODEM, DATA, RECOVERY, UEFI, and other partitions are outside the writer tool.

Open integration sources to use during hardware enablement include Linux MSM DRM, Freedreno/Mesa for Adreno, Linux MMC/SDHCI, ALSA SoC, V4L2, IIO, BlueZ, wpa_supplicant, gpsd, oFono, ModemManager, libqmi, lwIP, mbedTLS, Wine, ReactOS, and AOSP ART. Imported code must retain upstream licenses and copyright notices.


## MainOS-only rule

The Lumia 625H port must use the existing device boot chain and partition table. Bolun artifacts may replace only the MainOS payload. EFIESP, DPP, MODEM, DATA, RECOVERY, UEFI, SBL, RPM, TZ, WINSECAPP, NV, calibration, radio, camera, Bluetooth, Wi-Fi, and DSP partitions are out of scope. If Secure Boot or signature policy prevents a MainOS image from booting on a specific device, document the limitation instead of bypassing it.
