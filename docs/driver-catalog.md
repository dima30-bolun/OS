# Portable driver catalog

The host build now compiles a catalog of 112 portable modules. Each module registers one driver and one device through the existing Driver Manager and Device Manager, and each module avoids undocumented register constants.

The catalog covers display, input, audio, video, storage, network protocols, USB, sensors, power, platform, GPU, filesystems, GUI surfaces, built-in applications, store/update services, and board-profile slices.
