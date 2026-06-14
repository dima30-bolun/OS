#include "bolun/kernel.h"
#include <string.h>

static bolun_vfs_node_t *find_node(const char *path)
{
    if (!path) {
        return 0;
    }
    for (int i = 0; i < BOLUN_MAX_VFS_NODES; i++) {
        bolun_vfs_node_t *node = &g_kernel.vfs_nodes[i];
        if (node->used && strcmp(node->path, path) == 0) {
            return node;
        }
    }
    return 0;
}

int bolun_vfs_create(const char *path, uint32_t mode)
{
    if (!path || path[0] != '/' || strlen(path) >= sizeof(g_kernel.vfs_nodes[0].path)) {
        return -1;
    }
    bolun_vfs_node_t *existing = find_node(path);
    if (existing) {
        existing->mode = mode;
        return 0;
    }
    for (int i = 0; i < BOLUN_MAX_VFS_NODES; i++) {
        bolun_vfs_node_t *node = &g_kernel.vfs_nodes[i];
        if (!node->used) {
            memset(node, 0, sizeof(*node));
            memcpy(node->path, path, strlen(path) + 1);
            node->mode = mode;
            node->used = true;
            node->version = 1;
            return 0;
        }
    }
    return -2;
}

int bolun_vfs_write(const char *path, const void *data, size_t len, size_t off)
{
    bolun_vfs_node_t *node = find_node(path);
    if (!node || !data || (node->mode & BOLUN_VFS_WRITE) == 0) {
        return -1;
    }
    if (off > sizeof(node->data) || len > sizeof(node->data) - off) {
        return -2;
    }
    memcpy(node->data + off, data, len);
    if (node->size < off + len) {
        node->size = off + len;
    }
    node->version++;
    return (int)len;
}

int bolun_vfs_read(const char *path, void *data, size_t len, size_t off)
{
    bolun_vfs_node_t *node = find_node(path);
    if (!node || !data || (node->mode & BOLUN_VFS_READ) == 0) {
        return -1;
    }
    if (off >= node->size) {
        return 0;
    }
    size_t readable = node->size - off;
    size_t n = len < readable ? len : readable;
    memcpy(data, node->data + off, n);
    return (int)n;
}

int bolun_vfs_snapshot(const char *from, const char *to)
{
    bolun_vfs_node_t *src = find_node(from);
    if (!src || bolun_vfs_create(to, src->mode) != 0) {
        return -1;
    }
    bolun_vfs_node_t *dst = find_node(to);
    if (!dst) {
        return -2;
    }
    memcpy(dst->data, src->data, src->size);
    dst->size = src->size;
    dst->version = src->version;
    return 0;
}

int bolun_page_cache_put(const char *path, uint32_t page_index, const void *data, size_t len, bool dirty)
{
    if (!path || !data || strlen(path) >= sizeof(g_kernel.page_cache[0].path) || len > BOLUN_PAGE_SIZE) {
        return -1;
    }
    bolun_page_cache_entry_t *slot = 0;
    for (int i = 0; i < BOLUN_MAX_PAGE_CACHE; i++) {
        bolun_page_cache_entry_t *entry = &g_kernel.page_cache[i];
        if (entry->used && entry->page_index == page_index && strcmp(entry->path, path) == 0) {
            slot = entry;
            break;
        }
        if (!entry->used && !slot) {
            slot = entry;
        }
    }
    if (!slot) {
        return -2;
    }
    memset(slot, 0, sizeof(*slot));
    memcpy(slot->path, path, strlen(path) + 1);
    memcpy(slot->data, data, len);
    slot->page_index = page_index;
    slot->valid = len;
    slot->dirty = dirty;
    slot->used = true;
    return 0;
}

int bolun_page_cache_get(const char *path, uint32_t page_index, void *data, size_t cap)
{
    if (!path || !data) {
        return -1;
    }
    for (int i = 0; i < BOLUN_MAX_PAGE_CACHE; i++) {
        bolun_page_cache_entry_t *entry = &g_kernel.page_cache[i];
        if (entry->used && entry->page_index == page_index && strcmp(entry->path, path) == 0) {
            size_t n = cap < entry->valid ? cap : entry->valid;
            memcpy(data, entry->data, n);
            return (int)n;
        }
    }
    return 0;
}
