# Architecture

Bolun Phone OS is split into Boot Layer, Kernel, HAL, Drivers, Security, Services, Graphics, Runtime, MainOS shell, Applications, SDK, Package Manager, Compatibility Layer, Update System, and Testing.

The boot layer is designed to be packed into a MainOS image while preserving all non-MainOS Lumia partitions. The kernel implements process, thread, VM, IPC, capability, syscall, scheduler, and crash paths in portable C with ARMv7 context structures. The HAL exposes Snapdragon S4 MSM8930 hardware through open Linux/Qualcomm-compatible driver boundaries.
