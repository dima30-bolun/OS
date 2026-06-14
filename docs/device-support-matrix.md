# Device support matrix

MainOS keeps device support as data that feeds the existing HAL, Driver Manager, and Device Manager. This file records what is present in-tree and what still needs public board documentation before a real-device boot can safely program hardware.

| Device | CPU architecture | SoC family in profile | Current status |
| --- | --- | --- | --- |
| Lumia 520 | ARMv7 | MSM8x27 | Profile present; board-private regulator, panel, camera, sensor, and PMIC tables still require open board files. |
| Lumia 525 | ARMv7 | MSM8x27 | Profile present; same open-board-file requirement as Lumia 520. |
| Lumia 620 | ARMv7 | MSM8x27 | Profile present; same open-board-file requirement as Lumia 520. |
| Lumia 625H | ARMv7 | MSM8930 | Primary profile; portable driver inventory binds in host tests, real hardware enablement requires board resources. |
| Lumia 720 | ARMv7 | MSM8x27 | Profile present; same open-board-file requirement as Lumia 520. |
| Lumia 820 | ARMv7 | MSM8960 | Profile present; MSM8960 resources need open board files before hardware programming. |
| Lumia 920 | ARMv7 | MSM8960 | Profile present; MSM8960 resources need open board files before hardware programming. |
| Lumia 925 | ARMv7 | MSM8960 | Profile present; MSM8960 resources need open board files before hardware programming. |
| Lumia 1020 | ARMv7 | MSM8960 | Profile present; camera stack needs public sensor/calibration documentation before production enablement. |
| Redmi 9A | ARM64 | MediaTek Helio G25/MT6762G | Profile present; boot chain, DRAM layout, display, PMIC, touchscreen, camera, Wi-Fi/BT, and modem resources require open DTS/BSP evidence. |
| Redmi 9C NFC | ARM64 | MediaTek Helio G35/MT6765 | Profile present; NFC plus the Redmi 9A resource classes require open DTS/BSP evidence. |

The project must not add register addresses, clocks, GPIO numbers, panel sequences, or calibration data to board files unless those values are confirmed by open manufacturer documentation, Linux kernel sources, U-Boot, an open BSP, or reproducible reverse-engineering notes.
