#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static void write_file(const char *path, const char *text)
{
    FILE *f = fopen(path, "wb");
    assert(f != 0);
    fputs(text, f);
    fclose(f);
}

int main(void)
{
    write_file("out/tests/kernel.bin", "kernel");
    int good = system("out/tools/mkmainos out/tests/kernel.bin packaging/mainos.json out/tests/policy-mainos.img >/dev/null");
    assert(good == 0);

    write_file("out/tests/bad-manifest.json", "{\"partitions_written\":[\"MainOS\"],\"partitions_forbidden\":[\"EFIESP\"]}");
    int bad_manifest = system("out/tools/mkmainos out/tests/kernel.bin out/tests/bad-manifest.json out/tests/bad-mainos.img >/dev/null 2>/dev/null");
    assert(bad_manifest != 0);

    write_file("out/tests/no-contents.json", "{\"partitions_written\":[\"MainOS\"],\"partitions_forbidden\":[\"UEFI\",\"EFIESP\",\"MODEM\",\"DPP\",\"SBL\",\"RPM\",\"TZ\",\"WINSECAPP\",\"NV\",\"RECOVERY\",\"DATA\",\"CALIBRATION\",\"RADIO\",\"BLUETOOTH\",\"WIFI\",\"DSP\"],\"preserve_bootloader\":true,\"preserve_uefi\":true,\"preserve_secure_boot\":true,\"preserve_partition_table\":true,\"no_trust_chain_bypass\":true}");
    int bad_contents = system("out/tools/mkmainos out/tests/kernel.bin out/tests/no-contents.json out/tests/no-contents-mainos.img >/dev/null 2>/dev/null");
    assert(bad_contents != 0);

    int bad_name = system("out/tools/mkmainos out/tests/kernel.bin packaging/mainos.json out/tests/whole-device.img >/dev/null 2>/dev/null");
    assert(bad_name != 0);
    return 0;
}
