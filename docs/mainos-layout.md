# MainOS payload layout

Bolun Phone OS packages the complete open OS payload inside `MainOS`. The build manifest lists every required payload class so review and test tooling can reject images that would require another firmware partition.

| MainOS content | Purpose | Status |
| --- | --- | --- |
| kernel | Bolun kernel image and core runtime state. | ready |
| hal | Hardware abstraction records and board-facing interfaces. | ready |
| drivers | Open drivers and compatibility interfaces for legal hardware access. | partially implemented |
| system_libraries | C/C++ runtime and Bolun support libraries. | partially implemented |
| system_services | Power, package, device, and user services. | partially implemented |
| graphical_shell | Phone shell and launch surfaces. | partially implemented |
| window_system | Compositor and surface/window management. | partially implemented |
| filesystem | VFS and filesystem drivers. | partially implemented |
| network_stack | IP, DNS, transport, and network device services. | partially implemented |
| system_apps | Built-in phone applications. | partially implemented |
| sdk | Developer tools shipped inside MainOS for the open platform. | partially implemented |
| api | Public Bolun APIs and headers. | ready |
| runtime | Native and compatibility runtimes. | partially implemented |
| package_manager | Install, update, remove, and verification tooling. | partially implemented |
| app_store | Store client and repository policy. | partially implemented |
| diagnostics | Logging and test utilities. | partially implemented |
| documentation | User, developer, porting, and safety documents. | ready |

If any item requires closed documentation, manufacturer signatures, inaccessible firmware, or unavailable open drivers on a specific Lumia model, the port status must say `requires hardware support` or `unavailable without manufacturer support`. The project must not add a bypass for bootloader, Secure Boot, Verified Boot, calibration, modem, Wi-Fi, Bluetooth, camera, DSP, or other protected firmware partitions.
