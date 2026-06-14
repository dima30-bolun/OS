# Bolun Phone OS

Bolun Phone OS is an experimental, open-source mobile OS workspace for the Nokia/Microsoft Lumia 625H class of hardware (Qualcomm Snapdragon S4 MSM8930, ARMv7). It is intentionally scoped to replacing only the Windows Phone `MainOS` payload and never writes EFIESP, DPP, MODEM, DATA, RECOVERY, UEFI, or other firmware partitions.

This repository contains a buildable research OS core, Lumia 625H hardware profile, host/QEMU test harness, userland services, app manifests, compatibility-layer parsers, packaging tools, and plain-language documentation. The kernel code is original MIT-licensed code and provides concrete implementations for scheduling, process/thread bookkeeping, virtual memory simulation, IPC, handle management, security capabilities, syscalls, file objects, network packets, and Lumia device driver models. Hardware-specific register programming is expressed as data-driven drivers and open-driver integration boundaries because closed Microsoft firmware code is not used.

## Build

```sh
make
make test
make image
```

The default build is a Linux-hosted ARMv7-compatible model used for validation. Cross-compiling a real MainOS image requires an ARM EABI toolchain and device-specific open driver imports documented in `docs/porting-lumia625h.md`.

## Safety

The image tool creates `out/bolun-mainos.img` only. It does not access block devices and cannot modify phone partitions. Flashing remains a separate manual research operation.
