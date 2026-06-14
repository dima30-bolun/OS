# Bolun Phone OS feature status

This document records the realistic completion state of the current open implementation. It avoids claims that require closed Lumia firmware and separates host-validated code from hardware-dependent enablement.

| Area | Status | Notes |
| --- | --- | --- |
| Kernel boot model | Ready | Host kernel model creates init, tracks ticks, processes, threads, handles, drivers, services, devices, VFS nodes, page cache entries, and HAL state. |
| Architecture registry | Ready | ARMv7, ARMv8, ARM64, x86, x86_64, and RISC-V 64-bit identifiers are available for modular ports. |
| HAL | Ready | The kernel has an explicit HAL information block for architecture, cores, timer frequency, MMU, NX, ASLR capability state, and a portable IRQ registration/dispatch layer for host validation. |
| Processes and threads | Ready | Process lifecycle, priorities, wait, exit, and thread context records are implemented. |
| Preemptive scheduling model | Partially implemented | Timer ticks choose the highest-priority ready thread; real IRQ preemption requires board timer integration. |
| Virtual memory and MMU model | Partially implemented | Page records, lazy fault population, ASID assignment, map/protect/translate helpers, and user/write permission checks exist; real page-table register writes are hardware-dependent. |
| Synchronization | Ready | Mutex, spinlock, rwlock, semaphore, and event primitives are implemented for the host model. |
| IPC | Ready | Bounded message queues move data between process IDs. |
| Driver model and Device Manager | Ready | Drivers and devices are registered independently, matched by class, and bound through a Plug-and-Play-style pass; the compiled portable catalog adds more than 100 module-level driver/device boundaries. |
| Bus inventory | Partially implemented | Device metadata represents Device Tree, ACPI, PCI, USB, GPIO, I2C, SPI, UART, DMA, RTC, and PWM buses; enumeration is data-driven in the host model. |
| Service Manager | Ready | Named services can be registered, owned by a process, and marked running. |
| Lumia hardware profiles | Ready | Lumia 520, 525, 620, 625H, 720, 820, 920, 925, 1020, Redmi 9A, and Redmi 9C NFC profiles are represented with SoC/display metadata; detailed board resources still require open board files or vendor documentation. |
| Phone-class driver inventory | Partially implemented | Display, touchscreen, framebuffer, GPU, audio, microphone, camera, USB host/device, battery, charger, power, RTC, GPIO, PWM, timers, watchdog, storage, serial buses, radios, magnetometer/sensors, haptics, LEDs, and buttons are registered through the Driver Manager; production enablement requires board resources and hardware documentation. |
| VFS | Ready | In-memory VFS nodes support create, read, write, and snapshot operations for tests and early boot configuration. |
| Page cache | Ready | Fixed-size page cache entries support path/page lookup and dirty-state tracking. |
| FAT32/ext4 detection and formatting | Partially implemented | Boot-sector/superblock detection and minimal in-memory FAT32/ext4 formatting helpers are available for mount probing tests; full persistent file operations and journaling still require block-device integration. |
| Network stack helpers | Partially implemented | Internet checksum, DNS wire-name encoding, IPv4 packet construction, and UDP datagram construction are available; full TCP/TCPv6/DHCP/socket routing remains future work. |
| Application compatibility | Partially implemented | Package inspection identifies ELF, XAP, APPX/MSIX, APK, and EXE/PE; runtimes are sandbox/container-limited and x86/x86_64 PE is rejected instead of claimed runnable. |
| Store, signatures, updates | Partially implemented | Manifest and package tooling exist; repository policy and update transport need deployment services. |
| Graphical shell and system apps | Partially implemented | Documentation defines the Windows Phone-inspired direction; compositor and app surfaces need further implementation. |
| Secure boot and encryption | Requires hardware support | Open policy can be implemented, but secure boot enforcement depends on verified boot chain control. |
| Manufacturer-gated hardware features | Unavailable without manufacturer support | Features requiring closed signatures, inaccessible firmware interfaces, or non-public calibration data are documented instead of bypassed. |
