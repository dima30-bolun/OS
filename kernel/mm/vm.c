#include "bolun/kernel.h"
#include <string.h>

static bolun_page_t *find_page(bolun_process_t *p, uintptr_t va)
{
    uintptr_t base = va & ~(uintptr_t)(BOLUN_PAGE_SIZE - 1u);
    for (size_t i = 0; i < p->page_count; i++) {
        if (p->pages[i].va == base) {
            return &p->pages[i];
        }
    }
    return 0;
}

int bolun_virtual_alloc(int pid, uintptr_t va, size_t bytes, uint32_t flags)
{
    if (pid <= 0 || pid >= BOLUN_MAX_PROCESSES || (va % BOLUN_PAGE_SIZE) != 0) {
        return -1;
    }
    bolun_process_t *p = &g_kernel.processes[pid];
    size_t pages = (bytes + BOLUN_PAGE_SIZE - 1u) / BOLUN_PAGE_SIZE;
    if (pages == 0 || p->page_count + pages > 128) {
        return -2;
    }
    for (size_t i = 0; i < pages; i++) {
        if (find_page(p, va + i * BOLUN_PAGE_SIZE)) {
            return -3;
        }
    }
    for (size_t i = 0; i < pages; i++) {
        p->pages[p->page_count++] = (bolun_page_t){
            .va = va + i * BOLUN_PAGE_SIZE,
            .pa = 0,
            .flags = flags,
            .refs = 1,
            .cow = false,
            .present = false
        };
    }
    return 0;
}

int bolun_virtual_free(int pid, uintptr_t va, size_t bytes)
{
    if (pid <= 0 || pid >= BOLUN_MAX_PROCESSES) {
        return -1;
    }
    bolun_process_t *p = &g_kernel.processes[pid];
    uintptr_t end = va + bytes;
    size_t w = 0;
    for (size_t i = 0; i < p->page_count; i++) {
        uintptr_t a = p->pages[i].va;
        if (a >= va && a < end) {
            continue;
        }
        p->pages[w++] = p->pages[i];
    }
    p->page_count = w;
    return 0;
}

int bolun_page_fault(int pid, uintptr_t va, bool write)
{
    if (pid <= 0 || pid >= BOLUN_MAX_PROCESSES) {
        return -1;
    }
    bolun_process_t *p = &g_kernel.processes[pid];
    bolun_page_t *page = find_page(p, va);
    if (!page) {
        return -2;
    }
    if (write && (page->flags & BOLUN_PAGE_WRITE) == 0) {
        return -3;
    }
    if (write && page->cow) {
        page->cow = false;
        page->refs = 1;
    }
    page->present = true;
    page->pa = (uintptr_t)(pid * 0x100000u + (page - p->pages) * BOLUN_PAGE_SIZE);
    return 0;
}

int bolun_mmu_map(int pid, uintptr_t va, uintptr_t pa, uint32_t flags)
{
    if (pid <= 0 || pid >= BOLUN_MAX_PROCESSES ||
        (va % BOLUN_PAGE_SIZE) != 0 || (pa % BOLUN_PAGE_SIZE) != 0) {
        return -1;
    }
    bolun_process_t *p = &g_kernel.processes[pid];
    bolun_page_t *page = find_page(p, va);
    if (!page) {
        if (p->page_count >= 128) {
            return -2;
        }
        page = &p->pages[p->page_count++];
        memset(page, 0, sizeof(*page));
        page->va = va;
        page->refs = 1;
    }
    page->pa = pa;
    page->flags = flags;
    page->present = true;
    return 0;
}

int bolun_mmu_protect(int pid, uintptr_t va, uint32_t flags)
{
    if (pid <= 0 || pid >= BOLUN_MAX_PROCESSES) {
        return -1;
    }
    bolun_page_t *page = find_page(&g_kernel.processes[pid], va);
    if (!page) {
        return -2;
    }
    page->flags = flags;
    return 0;
}

int bolun_mmu_translate(int pid, uintptr_t va, bool write, bool user, uintptr_t *pa)
{
    if (pid <= 0 || pid >= BOLUN_MAX_PROCESSES || !pa) {
        return -1;
    }
    bolun_page_t *page = find_page(&g_kernel.processes[pid], va);
    if (!page || !page->present) {
        return -2;
    }
    if (write && (page->flags & BOLUN_PAGE_WRITE) == 0) {
        return -3;
    }
    if (user && (page->flags & BOLUN_PAGE_USER) == 0) {
        return -4;
    }
    *pa = page->pa + (va & (BOLUN_PAGE_SIZE - 1u));
    return 0;
}
