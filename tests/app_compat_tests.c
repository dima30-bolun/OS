#include "bolun/appcompat.h"
#include "bolun/kernel.h"
#include <assert.h>
#include <string.h>

static void make_pe(unsigned char *buf, unsigned machine)
{
    memset(buf, 0, 128);
    buf[0] = 'M';
    buf[1] = 'Z';
    buf[0x3c] = 0x40;
    buf[0x40] = 'P';
    buf[0x41] = 'E';
    buf[0x44] = (unsigned char)(machine & 0xffu);
    buf[0x45] = (unsigned char)(machine >> 8);
}

static void make_elf(unsigned char *buf, unsigned machine)
{
    memset(buf, 0, 64);
    buf[0] = 0x7f;
    buf[1] = 'E';
    buf[2] = 'L';
    buf[3] = 'F';
    buf[18] = (unsigned char)(machine & 0xffu);
    buf[19] = (unsigned char)(machine >> 8);
}

int main(void)
{
    bolun_package_info_t info;
    unsigned char zip[] = { 'P', 'K', 3, 4, 0, 0 };
    assert(bolun_package_inspect(zip, sizeof(zip), "game.xap", &info) == 0);
    assert(info.format == BOLUN_PACKAGE_XAP && info.supported && (info.required_caps & CAP_FS));
    assert(bolun_package_inspect(zip, sizeof(zip), "tool.appx", &info) == 0);
    assert(info.format == BOLUN_PACKAGE_APPX && info.supported && (info.required_caps & CAP_DEVICE));
    assert(bolun_package_inspect(zip, sizeof(zip), "chat.apk", &info) == 0);
    assert(info.format == BOLUN_PACKAGE_APK && info.supported);

    unsigned char pe[128];
    make_pe(pe, 0x01c4);
    assert(bolun_package_inspect(pe, sizeof(pe), "native.exe", &info) == 0);
    assert(info.format == BOLUN_PACKAGE_EXE && info.abi == BOLUN_CPU_ARMV7 && info.supported);
    make_pe(pe, 0x8664);
    assert(bolun_package_inspect(pe, sizeof(pe), "desktop.exe", &info) == 1);
    assert(info.format == BOLUN_PACKAGE_EXE && info.abi == BOLUN_CPU_X86_64 && !info.supported);

    unsigned char elf[64];
    make_elf(elf, 0x28);
    assert(bolun_package_inspect(elf, sizeof(elf), "app", &info) == 0);
    assert(info.format == BOLUN_PACKAGE_ELF && info.abi == BOLUN_CPU_ARMV7 && info.supported);
    make_elf(elf, 0xf3);
    assert(bolun_package_inspect(elf, sizeof(elf), "rvapp", &info) == 0);
    assert(info.abi == BOLUN_CPU_RISCV64);

    assert(strcmp(bolun_package_format_name(BOLUN_PACKAGE_APK), "apk") == 0);
    assert(strcmp(bolun_cpu_abi_name(BOLUN_CPU_ARM64), "arm64") == 0);
    return 0;
}
