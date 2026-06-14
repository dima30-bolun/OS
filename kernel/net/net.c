#include "bolun/kernel.h"
#include <stdint.h>
#include <string.h>

uint16_t bolun_inet_checksum(const void *data, unsigned len)
{
    const uint8_t *p = data;
    uint32_t sum = 0;
    while (len > 1) {
        sum += ((uint16_t)p[0] << 8) | p[1];
        p += 2;
        len -= 2;
    }
    if (len) {
        sum += (uint16_t)p[0] << 8;
    }
    while (sum >> 16) {
        sum = (sum & 0xffffu) + (sum >> 16);
    }
    return (uint16_t)~sum;
}

int bolun_dns_query_name(const char *host, unsigned char *out, unsigned cap)
{
    unsigned w = 0;
    unsigned start = 0;
    for (unsigned i = 0;; i++) {
        if (host[i] == '.' || host[i] == 0) {
            unsigned n = i - start;
            if (n > 63 || w + 1 + n >= cap) {
                return -1;
            }
            out[w++] = (unsigned char)n;
            memcpy(out + w, host + start, n);
            w += n;
            start = i + 1;
            if (host[i] == 0) {
                if (w >= cap) {
                    return -1;
                }
                out[w++] = 0;
                return (int)w;
            }
        }
    }
}

int bolun_ipv4_build(uint8_t *out, size_t cap, uint32_t src, uint32_t dst,
                     uint8_t proto, const void *payload, size_t payload_len)
{
    if (!out || (!payload && payload_len) || payload_len > 65515u || cap < 20u + payload_len) {
        return -1;
    }
    memset(out, 0, 20u + payload_len);
    out[0] = 0x45;
    out[2] = (uint8_t)((20u + payload_len) >> 8);
    out[3] = (uint8_t)(20u + payload_len);
    out[8] = 64;
    out[9] = proto;
    out[12] = (uint8_t)(src >> 24);
    out[13] = (uint8_t)(src >> 16);
    out[14] = (uint8_t)(src >> 8);
    out[15] = (uint8_t)src;
    out[16] = (uint8_t)(dst >> 24);
    out[17] = (uint8_t)(dst >> 16);
    out[18] = (uint8_t)(dst >> 8);
    out[19] = (uint8_t)dst;
    if (payload_len) {
        memcpy(out + 20, payload, payload_len);
    }
    uint16_t csum = bolun_inet_checksum(out, 20);
    out[10] = (uint8_t)(csum >> 8);
    out[11] = (uint8_t)csum;
    return (int)(20u + payload_len);
}

int bolun_udp_build(uint8_t *out, size_t cap, uint16_t src_port, uint16_t dst_port,
                    const void *payload, size_t payload_len)
{
    if (!out || (!payload && payload_len) || payload_len > 65527u || cap < 8u + payload_len) {
        return -1;
    }
    out[0] = (uint8_t)(src_port >> 8);
    out[1] = (uint8_t)src_port;
    out[2] = (uint8_t)(dst_port >> 8);
    out[3] = (uint8_t)dst_port;
    out[4] = (uint8_t)((8u + payload_len) >> 8);
    out[5] = (uint8_t)(8u + payload_len);
    out[6] = 0;
    out[7] = 0;
    if (payload_len) {
        memcpy(out + 8, payload, payload_len);
    }
    return (int)(8u + payload_len);
}
