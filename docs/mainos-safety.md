# MainOS-only safety policy

Bolun Phone OS is built as a replacement payload for the `MainOS` partition only. The project must not modify the bootloader, UEFI, Secure Boot policy, partition table, modem firmware, calibration storage, radio firmware, camera firmware, Bluetooth firmware, Wi-Fi firmware, DSP firmware, or any other service partition.

## Immutable device areas

The image builder refuses manifests unless they explicitly mark only `MainOS` as writable and list the protected firmware and service partitions as forbidden: `EFIESP`, `DPP`, `MODEM`, `DATA`, `RECOVERY`, `UEFI`, `SBL`, `RPM`, `TZ`, `WINSECAPP`, `NV`, `CALIBRATION`, `RADIO`, `CAMERA`, `BLUETOOTH`, `WIFI`, and `DSP`.

## Boot and trust chain

Bolun does not replace the existing boot chain. A device port must preserve the stock bootloader, UEFI, Secure Boot state, and partition table. If a device refuses to boot an unsigned or differently signed MainOS image, the porting documentation must state that limitation and must not describe a bypass.

## Updates

Updates are MainOS content updates. Update tooling may create or replace files inside the generated MainOS image, but it must not open block devices or write any other partition. Firmware, modem, wireless, camera, DSP, calibration, and trust-zone components remain owned by the device firmware package.


## Payload completeness

The generated MainOS manifest must list the OS components that live in MainOS: kernel, HAL, drivers, system libraries, services, graphical shell, window system, filesystem, network stack, system apps, SDK, API, runtime, package manager, app store, diagnostics, and documentation. If a component cannot be enabled on a device without manufacturer signatures or closed firmware access, the status must be `requires hardware support` or `unavailable without manufacturer support`.
