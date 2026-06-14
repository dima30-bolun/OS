# Bolun Phone OS feature status

This document records the realistic completion state of the current open implementation. It avoids claims that require closed Lumia firmware and separates host-validated code from hardware-dependent enablement.

| Area | Status | Notes |
| --- | --- | --- |
| Kernel boot model | Ready | Host kernel model creates init, tracks ticks, processes, threads, handles, drivers, services, devices, VFS nodes, page cache entries, and HAL state. |
| Architecture registry | Ready | ARMv7, ARMv8, ARM64, x86, x86_64, and RISC-V 64-bit identifiers are available for modular ports. |
| HAL | Ready | The kernel has an explicit HAL information block for architecture, cores, timer frequency, MMU, NX, and ASLR capability state. |
| Processes and threads | Ready | Process lifecycle, priorities, wait, exit, and thread context records are implemented. |
| Preemptive scheduling model | Partially implemented | Timer ticks choose the highest-priority ready thread; real IRQ preemption requires board timer integration. |
| Virtual memory and MMU model | Partially implemented | Page records, lazy fault population, ASID assignment, and user/kernel separation metadata exist; real page-table writes are hardware-dependent. |
| Synchronization | Ready | Mutex, spinlock, rwlock, semaphore, and event primitives are implemented for the host model. |
| IPC | Ready | Bounded message queues move data between process IDs. |
| Driver model and Device Manager | Ready | Drivers and devices are registered independently, matched by class, and bound through a Plug-and-Play-style pass. |
| Bus inventory | Partially implemented | Device metadata represents Device Tree, ACPI, PCI, USB, GPIO, I2C, SPI, UART, DMA, RTC, and PWM buses; enumeration is data-driven in the host model. |
| Service Manager | Ready | Named services can be registered, owned by a process, and marked running. |
| Lumia hardware profiles | Ready | Lumia 520, 525, 620, 625H, 720, 820, 920, 925, and 1020 profiles are represented with Snapdragon S4-class SoC metadata. |
| Display, touch, storage, USB, power, input, audio, radio, modem, camera | Requires hardware support | Open integration boundaries are declared; production enablement requires board testing and open driver stacks. |
| VFS | Ready | In-memory VFS nodes support create, read, write, and snapshot operations for tests and early boot configuration. |
| Page cache | Ready | Fixed-size page cache entries support path/page lookup and dirty-state tracking. |
| FAT32, ext4, BolunFS | Partially implemented | The VFS boundary is in place; persistent on-disk format drivers remain to be added. |
| Network stack helpers | Partially implemented | Internet checksum and DNS wire-name encoding are available; full TCP/IP remains future work. |
| Application compatibility | Partially implemented | Package inspection identifies ELF, XAP, APPX/MSIX, APK, and EXE/PE; runtimes are sandbox/container-limited and x86/x86_64 PE is rejected instead of claimed runnable. |
| Store, signatures, updates | Partially implemented | Manifest and package tooling exist; repository policy and update transport need deployment services. |
| Graphical shell and system apps | Partially implemented | Documentation defines the Windows Phone-inspired direction; compositor and app surfaces need further implementation. |
| Secure boot and encryption | Requires hardware support | Open policy can be implemented, but secure boot enforcement depends on verified boot chain control. |
| Manufacturer-gated hardware features | Unavailable without manufacturer support | Features requiring closed signatures, inaccessible firmware interfaces, or non-public calibration data are documented instead of bypassed. |
