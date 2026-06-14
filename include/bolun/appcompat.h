#ifndef BOLUN_APPCOMPAT_H
#define BOLUN_APPCOMPAT_H

#include <stddef.h>
#include <stdint.h>

typedef enum {
    BOLUN_PACKAGE_UNKNOWN = 0,
    BOLUN_PACKAGE_XAP,
    BOLUN_PACKAGE_APPX,
    BOLUN_PACKAGE_APK,
    BOLUN_PACKAGE_EXE,
    BOLUN_PACKAGE_ELF
} bolun_package_format_t;

typedef enum {
    BOLUN_CPU_UNKNOWN = 0,
    BOLUN_CPU_ARMV7,
    BOLUN_CPU_ARM64,
    BOLUN_CPU_X86,
    BOLUN_CPU_X86_64,
    BOLUN_CPU_RISCV64
} bolun_cpu_abi_t;

typedef struct {
    bolun_package_format_t format;
    bolun_cpu_abi_t abi;
    uint32_t required_caps;
    int supported;
    char reason[96];
} bolun_package_info_t;

int bolun_manifest_has_capability(const char *manifest, const char *cap);
int bolun_xap_is_valid(const unsigned char *buf, unsigned len);
int bolun_pe_is_arm(const unsigned char *buf, unsigned len);
bolun_package_format_t bolun_package_detect(const unsigned char *buf, size_t len, const char *name);
bolun_cpu_abi_t bolun_pe_cpu_abi(const unsigned char *buf, size_t len);
bolun_cpu_abi_t bolun_elf_cpu_abi(const unsigned char *buf, size_t len);
int bolun_package_inspect(const unsigned char *buf, size_t len, const char *name, bolun_package_info_t *out);
const char *bolun_package_format_name(bolun_package_format_t format);
const char *bolun_cpu_abi_name(bolun_cpu_abi_t abi);

#endif
