#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned char *read_all(const char *path, size_t *len) {
    FILE *f = fopen(path, "rb");
    if (!f) { perror(path); exit(2); }
    if (fseek(f, 0, SEEK_END) != 0) { perror("fseek"); exit(2); }
    long n = ftell(f);
    if (n < 0) { perror("ftell"); exit(2); }
    rewind(f);
    unsigned char *buf = malloc((size_t)n ? (size_t)n : 1u);
    if (!buf) { perror("malloc"); exit(2); }
    if (fread(buf, 1, (size_t)n, f) != (size_t)n) { perror("fread"); exit(2); }
    fclose(f);
    *len = (size_t)n;
    return buf;
}

static uint32_t fnv1a(const unsigned char *data, size_t len) {
    uint32_t h = 2166136261u;
    for (size_t i = 0; i < len; ++i) { h ^= data[i]; h *= 16777619u; }
    return h;
}

static int manifest_is_mainos_only(const char *text) {
    return strstr(text, "\"partitions_written\":[\"MainOS\"]") &&
           strstr(text, "\"EFIESP\"") && strstr(text, "\"UEFI\"") &&
           strstr(text, "\"MODEM\"");
}

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "usage: %s <kernel> <manifest> <output>\n", argv[0]);
        return 64;
    }
    size_t mlen = 0, klen = 0;
    char *manifest = (char *)read_all(argv[2], &mlen);
    if (!manifest_is_mainos_only(manifest)) {
        fprintf(stderr, "refusing image: manifest must restrict writes to MainOS and forbid firmware partitions\n");
        return 65;
    }
    unsigned char *kernel = read_all(argv[1], &klen);
    FILE *out = fopen(argv[3], "wb");
    if (!out) { perror(argv[3]); return 2; }
    const char magic[16] = "BOLUNMAINOS\0\0\0\0";
    uint32_t size = (uint32_t)klen, soc = 0x8930u, crc = fnv1a(kernel, klen);
    fwrite(magic, 1, 16, out);
    fwrite(&size, 4, 1, out);
    fwrite(&soc, 4, 1, out);
    fwrite(&crc, 4, 1, out);
    fwrite(kernel, 1, klen, out);
    fclose(out);
    printf("wrote %s bytes=%u checksum=%08x\n", argv[3], (unsigned)(klen + 28u), crc);
    free(manifest); free(kernel);
    return 0;
}
