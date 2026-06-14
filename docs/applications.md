# Application guide

## Phone
What it does: provides the Phone experience. Why it is needed: it covers a core phone task. How it works: it uses sandboxed services and capability checks optimized for Lumia ARMv7 profiles. User use: open it from the app list or a live tile.

## Contacts
What it does: provides the Contacts experience. Why it is needed: it covers a core phone task. How it works: it uses sandboxed services and capability checks optimized for Lumia ARMv7 profiles. User use: open it from the app list or a live tile.

## Messages
What it does: provides the Messages experience. Why it is needed: it covers a core phone task. How it works: it uses sandboxed services and capability checks optimized for Lumia ARMv7 profiles. User use: open it from the app list or a live tile.

## Mail
What it does: provides the Mail experience. Why it is needed: it covers a core phone task. How it works: it uses sandboxed services and capability checks optimized for Lumia ARMv7 profiles. User use: open it from the app list or a live tile.

## Calendar
What it does: provides the Calendar experience. Why it is needed: it covers a core phone task. How it works: it uses sandboxed services and capability checks optimized for Lumia ARMv7 profiles. User use: open it from the app list or a live tile.

## Clock
What it does: provides the Clock experience. Why it is needed: it covers a core phone task. How it works: it uses sandboxed services and capability checks optimized for Lumia ARMv7 profiles. User use: open it from the app list or a live tile.

## Calculator
What it does: provides the Calculator experience. Why it is needed: it covers a core phone task. How it works: it uses sandboxed services and capability checks optimized for Lumia ARMv7 profiles. User use: open it from the app list or a live tile.

## Camera
What it does: provides the Camera experience. Why it is needed: it covers a core phone task. How it works: it uses sandboxed services and capability checks optimized for Lumia ARMv7 profiles. User use: open it from the app list or a live tile.

## Gallery
What it does: provides the Gallery experience. Why it is needed: it covers a core phone task. How it works: it uses sandboxed services and capability checks optimized for Lumia ARMv7 profiles. User use: open it from the app list or a live tile.

## Music
What it does: provides the Music experience. Why it is needed: it covers a core phone task. How it works: it uses sandboxed services and capability checks optimized for Lumia ARMv7 profiles. User use: open it from the app list or a live tile.

## Video
What it does: provides the Video experience. Why it is needed: it covers a core phone task. How it works: it uses sandboxed services and capability checks optimized for Lumia ARMv7 profiles. User use: open it from the app list or a live tile.

## Browser
What it does: provides the Browser experience. Why it is needed: it covers a core phone task. How it works: it uses sandboxed services and capability checks optimized for Lumia ARMv7 profiles. User use: open it from the app list or a live tile.

## Maps
What it does: provides the Maps experience. Why it is needed: it covers a core phone task. How it works: it uses sandboxed services and capability checks optimized for Lumia ARMv7 profiles. User use: open it from the app list or a live tile.

## Settings
What it does: provides the Settings experience. Why it is needed: it covers a core phone task. How it works: it uses sandboxed services and capability checks optimized for Lumia ARMv7 profiles. User use: open it from the app list or a live tile.

## Files
What it does: provides the Files experience. Why it is needed: it covers a core phone task. How it works: it uses sandboxed services and capability checks optimized for Lumia ARMv7 profiles. User use: open it from the app list or a live tile.

## Store
What it does: provides the Store experience. Why it is needed: it covers a core phone task. How it works: it uses sandboxed services and capability checks optimized for Lumia ARMv7 profiles. User use: open it from the app list or a live tile.

## Terminal
What it does: provides the Terminal experience. Why it is needed: it covers a core phone task. How it works: it uses sandboxed services and capability checks optimized for Lumia ARMv7 profiles. User use: open it from the app list or a live tile.

## Notes
What it does: provides the Notes experience. Why it is needed: it covers a core phone task. How it works: it uses sandboxed services and capability checks optimized for Lumia ARMv7 profiles. User use: open it from the app list or a live tile.

## Recorder
What it does: provides the Recorder experience. Why it is needed: it covers a core phone task. How it works: it uses sandboxed services and capability checks optimized for Lumia ARMv7 profiles. User use: open it from the app list or a live tile.

## Alarm
What it does: provides the Alarm experience. Why it is needed: it covers a core phone task. How it works: it uses sandboxed services and capability checks optimized for Lumia ARMv7 profiles. User use: open it from the app list or a live tile.

## Weather
What it does: provides the Weather experience. Why it is needed: it covers a core phone task. How it works: it uses sandboxed services and capability checks optimized for Lumia ARMv7 profiles. User use: open it from the app list or a live tile.

## Diagnostics
What it does: provides the Diagnostics experience. Why it is needed: it covers a core phone task. How it works: it uses sandboxed services and capability checks optimized for Lumia ARMv7 profiles. User use: open it from the app list or a live tile.

## Data calculator
What it does: provides the Data calculator experience. Why it is needed: it covers a core phone task. How it works: it uses sandboxed services and capability checks optimized for Lumia ARMv7 profiles. User use: open it from the app list or a live tile.

## FM radio
What it does: provides the FM radio experience. Why it is needed: it covers a core phone task. How it works: it uses sandboxed services and capability checks optimized for Lumia ARMv7 profiles. User use: open it from the app list or a live tile.


## Compatibility containers
Bolun Phone OS now identifies XAP, APPX/MSIX, APK, EXE/PE, and ELF inputs before launch. XAP, APPX, and APK are ZIP-derived packages and are accepted only into sandboxed containers with explicit capability sets. ELF is handled by the native loader path when its machine type is known. EXE means PE executable support only; ARMv7 and ARM64 PE files may enter a compatibility container, while x86 and x86_64 PE files are reported as unsupported CPU targets rather than falsely advertised as runnable.

| Format | Status | Runtime boundary |
| --- | --- | --- |
| ELF | Partially implemented | Native loader path for known CPU ABIs. |
| XAP | Partially implemented | Sandboxed Silverlight-style container with declared filesystem and network capabilities. |
| APPX/MSIX | Partially implemented | Restricted WinRT-style container with filesystem, network, and device capabilities. |
| APK | Partially implemented | Android-runtime boundary with documented API limitations. |
| EXE/PE | Partially implemented | ARMv7/ARM64 compatibility container only; x86/x86_64 PE files are rejected as unsupported CPU targets. |
