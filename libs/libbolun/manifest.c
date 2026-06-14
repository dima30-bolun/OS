#include "bolun/appcompat.h"
#include "bolun/kernel.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static uint16_t rd16(const unsigned char *p)
{
    return (uint16_t)p[0] | ((uint16_t)p[1] << 8);
}

static uint32_t rd32(const unsigned char *p)
{
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
}

static bool ends_with_ci(const char *name, const char *suffix)
{
    if (!name || !suffix) {
        return false;
    }
    size_t nl = strlen(name);
    size_t sl = strlen(suffix);
    if (nl < sl) {
        return false;
    }
    const char *tail = name + nl - sl;
    for (size_t i = 0; i < sl; i++) {
        char a = tail[i];
        char b = suffix[i];
        if (a >= 'A' && a <= 'Z') {
            a = (char)(a + ('a' - 'A'));
        }
        if (b >= 'A' && b <= 'Z') {
            b = (char)(b + ('a' - 'A'));
        }
        if (a != b) {
            return false;
        }
    }
    return true;
}

static void set_reason(bolun_package_info_t *out, const char *reason)
{
    if (!out) {
        return;
    }
    snprintf(out->reason, sizeof(out->reason), "%s", reason ? reason : "");
}

int bolun_manifest_has_capability(const char *manifest, const char *cap)
{
    return manifest && cap && strstr(manifest, cap) != 0;
}

int bolun_xap_is_valid(const unsigned char *buf, unsigned len)
{
    return len > 4 && buf && buf[0] == 'P' && buf[1] == 'K';
}

bolun_cpu_abi_t bolun_pe_cpu_abi(const unsigned char *buf, size_t len)
{
    if (!buf || len < 0x40 || buf[0] != 'M' || buf[1] != 'Z') {
        return BOLUN_CPU_UNKNOWN;
    }
    uint32_t pe = rd32(buf + 0x3c);
    if (pe > len || len - pe < 6 || buf[pe] != 'P' || buf[pe + 1] != 'E') {
        return BOLUN_CPU_UNKNOWN;
    }
    switch (rd16(buf + pe + 4)) {
    case 0x01c0:
    case 0x01c2:
    case 0x01c4:
        return BOLUN_CPU_ARMV7;
    case 0xaa64:
        return BOLUN_CPU_ARM64;
    case 0x014c:
        return BOLUN_CPU_X86;
    case 0x8664:
        return BOLUN_CPU_X86_64;
    default:
        return BOLUN_CPU_UNKNOWN;
    }
}

int bolun_pe_is_arm(const unsigned char *buf, unsigned len)
{
    return bolun_pe_cpu_abi(buf, len) == BOLUN_CPU_ARMV7;
}

bolun_cpu_abi_t bolun_elf_cpu_abi(const unsigned char *buf, size_t len)
{
    if (!buf || len < 20 || buf[0] != 0x7f || buf[1] != 'E' || buf[2] != 'L' || buf[3] != 'F') {
        return BOLUN_CPU_UNKNOWN;
    }
    uint16_t machine = rd16(buf + 18);
    switch (machine) {
    case 0x03:
        return BOLUN_CPU_X86;
    case 0x28:
        return BOLUN_CPU_ARMV7;
    case 0x3e:
        return BOLUN_CPU_X86_64;
    case 0xb7:
        return BOLUN_CPU_ARM64;
    case 0xf3:
        return BOLUN_CPU_RISCV64;
    default:
        return BOLUN_CPU_UNKNOWN;
    }
}

bolun_package_format_t bolun_package_detect(const unsigned char *buf, size_t len, const char *name)
{
    if (buf && len >= 4 && buf[0] == 0x7f && buf[1] == 'E' && buf[2] == 'L' && buf[3] == 'F') {
        return BOLUN_PACKAGE_ELF;
    }
    if (buf && len >= 2 && buf[0] == 'M' && buf[1] == 'Z') {
        return BOLUN_PACKAGE_EXE;
    }
    if (buf && len >= 2 && buf[0] == 'P' && buf[1] == 'K') {
        if (ends_with_ci(name, ".xap")) {
            return BOLUN_PACKAGE_XAP;
        }
        if (ends_with_ci(name, ".appx") || ends_with_ci(name, ".msix")) {
            return BOLUN_PACKAGE_APPX;
        }
        if (ends_with_ci(name, ".apk")) {
            return BOLUN_PACKAGE_APK;
        }
    }
    return BOLUN_PACKAGE_UNKNOWN;
}

int bolun_package_inspect(const unsigned char *buf, size_t len, const char *name, bolun_package_info_t *out)
{
    if (!out) {
        return -1;
    }
    memset(out, 0, sizeof(*out));
    out->format = bolun_package_detect(buf, len, name);
    out->abi = BOLUN_CPU_UNKNOWN;
    out->supported = 0;
    out->required_caps = 0;

    switch (out->format) {
    case BOLUN_PACKAGE_XAP:
        out->abi = BOLUN_CPU_ARMV7;
        out->supported = 1;
        out->required_caps = CAP_FS | CAP_NET;
        set_reason(out, "XAP zip package accepted for sandboxed Silverlight-style container");
        return 0;
    case BOLUN_PACKAGE_APPX:
        out->abi = BOLUN_CPU_ARMV7;
        out->supported = 1;
        out->required_caps = CAP_FS | CAP_NET | CAP_DEVICE;
        set_reason(out, "APPX/MSIX zip package accepted for restricted WinRT-style container");
        return 0;
    case BOLUN_PACKAGE_APK:
        out->abi = BOLUN_CPU_ARMV7;
        out->supported = 1;
        out->required_caps = CAP_FS | CAP_NET;
        set_reason(out, "APK zip package accepted for Android-runtime boundary with API limitations");
        return 0;
    case BOLUN_PACKAGE_EXE:
        out->abi = bolun_pe_cpu_abi(buf, len);
        out->supported = out->abi == BOLUN_CPU_ARMV7 || out->abi == BOLUN_CPU_ARM64;
        out->required_caps = CAP_FS;
        set_reason(out, out->supported ? "PE executable is loadable only through an explicit compatibility container" : "PE executable CPU is unsupported by the current compatibility container");
        return out->supported ? 0 : 1;
    case BOLUN_PACKAGE_ELF:
        out->abi = bolun_elf_cpu_abi(buf, len);
        out->supported = out->abi != BOLUN_CPU_UNKNOWN;
        out->required_caps = CAP_FS;
        set_reason(out, out->supported ? "ELF executable is supported by the native loader path" : "ELF machine type is not recognized");
        return out->supported ? 0 : 1;
    default:
        set_reason(out, "package format is not recognized");
        return 1;
    }
}

const char *bolun_package_format_name(bolun_package_format_t format)
{
    switch (format) {
    case BOLUN_PACKAGE_XAP:
        return "xap";
    case BOLUN_PACKAGE_APPX:
        return "appx";
    case BOLUN_PACKAGE_APK:
        return "apk";
    case BOLUN_PACKAGE_EXE:
        return "exe";
    case BOLUN_PACKAGE_ELF:
        return "elf";
    default:
        return "unknown";
    }
}

const char *bolun_cpu_abi_name(bolun_cpu_abi_t abi)
{
    switch (abi) {
    case BOLUN_CPU_ARMV7:
        return "armv7";
    case BOLUN_CPU_ARM64:
        return "arm64";
    case BOLUN_CPU_X86:
        return "x86";
    case BOLUN_CPU_X86_64:
        return "x86_64";
    case BOLUN_CPU_RISCV64:
        return "riscv64";
    default:
        return "unknown";
    }
}
