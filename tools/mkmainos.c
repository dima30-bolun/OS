#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *forbidden_partitions[] = {
    "UEFI", "EFIESP", "MODEM", "DPP", "SBL", "RPM", "TZ", "WINSECAPP", "NV",
    "RECOVERY", "DATA", "CALIBRATION", "RADIO", "BLUETOOTH", "WIFI", "DSP"
};

static const char *required_mainos_components[] = {
    "kernel", "hal", "drivers", "system_libraries", "system_services", "graphical_shell",
    "window_system", "filesystem", "network_stack", "system_apps", "sdk", "api",
    "runtime", "package_manager", "app_store", "diagnostics", "documentation"
};

static unsigned char *read_all(const char *path, size_t *len)
{
    FILE *f = fopen(path, "rb");
    if (!f) {
        perror(path);
        exit(2);
    }
    if (fseek(f, 0, SEEK_END) != 0) {
        perror("fseek");
        exit(2);
    }
    long n = ftell(f);
    if (n < 0) {
        perror("ftell");
        exit(2);
    }
    rewind(f);
    unsigned char *buf = malloc((size_t)n ? (size_t)n + 1u : 1u);
    if (!buf) {
        perror("malloc");
        exit(2);
    }
    if (fread(buf, 1, (size_t)n, f) != (size_t)n) {
        perror("fread");
        exit(2);
    }
    fclose(f);
    buf[(size_t)n] = 0;
    *len = (size_t)n;
    return buf;
}

static uint32_t fnv1a(const unsigned char *data, size_t len)
{
    uint32_t h = 2166136261u;
    for (size_t i = 0; i < len; ++i) {
        h ^= data[i];
        h *= 16777619u;
    }
    return h;
}

static int contains_json_string(const char *text, const char *value)
{
    char needle[96];
    if (snprintf(needle, sizeof(needle), "\"%s\"", value) >= (int)sizeof(needle)) {
        return 0;
    }
    return strstr(text, needle) != 0;
}

static int manifest_is_mainos_only(const char *text)
{
    if (!text || !strstr(text, "\"partitions_written\"") || !contains_json_string(text, "MainOS")) {
        return 0;
    }
    if (!strstr(text, "\"partitions_forbidden\"")) {
        return 0;
    }
    for (size_t i = 0; i < sizeof(forbidden_partitions) / sizeof(forbidden_partitions[0]); i++) {
        if (!contains_json_string(text, forbidden_partitions[i])) {
            return 0;
        }
    }
    if (!strstr(text, "\"mainos_contents\"")) {
        return 0;
    }
    for (size_t i = 0; i < sizeof(required_mainos_components) / sizeof(required_mainos_components[0]); i++) {
        if (!contains_json_string(text, required_mainos_components[i])) {
            return 0;
        }
    }
    return strstr(text, "\"preserve_bootloader\"") && strstr(text, "\"preserve_uefi\"") &&
           strstr(text, "\"preserve_secure_boot\"") && strstr(text, "\"preserve_partition_table\"") &&
           strstr(text, "\"no_trust_chain_bypass\"");
}

static int output_name_is_mainos_image(const char *path)
{
    return path && strstr(path, "mainos") != 0 && strstr(path, ".img") != 0;
}

int main(int argc, char **argv)
{
    if (argc != 4) {
        fprintf(stderr, "usage: %s <kernel> <manifest> <output-mainos.img>\n", argv[0]);
        return 64;
    }
    if (!output_name_is_mainos_image(argv[3])) {
        fprintf(stderr, "refusing image: output name must make the MainOS-only target explicit\n");
        return 66;
    }
    size_t mlen = 0;
    size_t klen = 0;
    char *manifest = (char *)read_all(argv[2], &mlen);
    if (!manifest_is_mainos_only(manifest)) {
        fprintf(stderr, "refusing image: manifest must restrict writes to MainOS, forbid firmware/service partitions, and list required MainOS contents\n");
        free(manifest);
        return 65;
    }
    unsigned char *kernel = read_all(argv[1], &klen);
    FILE *out = fopen(argv[3], "wb");
    if (!out) {
        perror(argv[3]);
        free(manifest);
        free(kernel);
        return 2;
    }
    const char magic[16] = "BOLUNMAINOS\0\0\0\0";
    uint32_t size = (uint32_t)klen;
    uint32_t soc = 0x8930u;
    uint32_t crc = fnv1a(kernel, klen);
    fwrite(magic, 1, 16, out);
    fwrite(&size, 4, 1, out);
    fwrite(&soc, 4, 1, out);
    fwrite(&crc, 4, 1, out);
    fwrite(kernel, 1, klen, out);
    fclose(out);
    printf("wrote %s bytes=%u checksum=%08x\n", argv[3], (unsigned)(klen + 28u), crc);
    free(manifest);
    free(kernel);
    return 0;
}
