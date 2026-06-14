#include "bolun/kernel.h"
#include <assert.h>
#include <string.h>


static void test_irq_handler(int irq, void *ctx)
{
    int *seen = ctx;
    *seen += irq;
}

int main(void)
{
    bolun_kernel_boot();
    assert(bolun_hal_info()->arch == BOLUN_ARCH_ARMV7);
    assert(bolun_hal_info()->has_mmu);
    assert(bolun_hal_timer_deadline(5) == g_kernel.ticks + 5);

    int p = bolun_process_create(1, CAP_FS);
    assert(p > 1);
    assert(bolun_check_cap(p, CAP_FS));
    assert(!bolun_check_cap(p, CAP_NET));
    assert(bolun_virtual_alloc(p, 0x400000, 8192, BOLUN_PAGE_WRITE | BOLUN_PAGE_USER) == 0);
    assert(bolun_page_fault(p, 0x400123, true) == 0);
    uintptr_t pa = 0;
    assert(bolun_mmu_translate(p, 0x400123, true, true, &pa) == 0);
    assert(pa != 0);
    assert(bolun_mmu_protect(p, 0x400000, BOLUN_PAGE_USER) == 0);
    assert(bolun_mmu_translate(p, 0x400123, true, true, &pa) == -3);
    assert(bolun_mmu_map(p, 0x500000, 0x900000, BOLUN_PAGE_WRITE) == 0);
    assert(bolun_mmu_translate(p, 0x500000, false, true, &pa) == -4);

    int t = bolun_thread_create(p, 0x8000, 20);
    assert(t > 0);
    bolun_schedule_tick();
    assert(g_kernel.current_tid == t);

    bolun_mutex_t m;
    bolun_mutex_init(&m);
    assert(bolun_mutex_lock(&m, t) == 0);
    assert(bolun_mutex_unlock(&m, t) == 0);

    bolun_rwlock_t rw;
    bolun_rwlock_init(&rw);
    assert(bolun_rwlock_read_lock(&rw) == 0);
    assert(bolun_rwlock_read_unlock(&rw) == 0);
    assert(bolun_rwlock_write_lock(&rw, t) == 0);
    assert(bolun_rwlock_write_unlock(&rw, t) == 0);

    bolun_semaphore_t sem;
    bolun_semaphore_init(&sem, 1);
    assert(bolun_semaphore_wait(&sem) == 0);
    assert(bolun_semaphore_wait(&sem) == -2);
    bolun_semaphore_post(&sem);
    assert(bolun_semaphore_wait(&sem) == 0);

    bolun_event_t ev;
    bolun_event_init(&ev, false);
    assert(bolun_event_wait(&ev) == -2);
    bolun_event_signal(&ev);
    assert(bolun_event_wait(&ev) == 0);

    int irq_seen = 0;
    assert(bolun_irq_register(17, test_irq_handler, &irq_seen) == 0);
    assert(bolun_irq_dispatch(17) == 0);
    assert(irq_seen == 17);
    assert(bolun_irq_enable(17, false) == 0);
    assert(bolun_irq_dispatch(17) == -2);

    const char mtext[] = "hello";
    assert(bolun_ipc_send(1, p, mtext, sizeof(mtext)) == 0);
    char b[8];
    assert(bolun_ipc_recv(p, b, sizeof(b)) == (int)sizeof(mtext));
    assert(strcmp(b, mtext) == 0);

    size_t catalog_count = bolun_driver_catalog_count();
    assert(catalog_count >= 112);
    assert(bolun_driver_catalog_register_all() == (int)catalog_count);
    assert(bolun_driver_find("net-ipv4") != 0);
    assert(bolun_device_find("catalog-gui_desktop") != 0);

    size_t driver_count = bolun_lumia_driver_count();
    assert(driver_count == 37);
    assert(bolun_lumia_probe_all() == (int)driver_count);
    assert(bolun_driver_find("display") != 0);
    assert(bolun_driver_find("gpu") != 0);
    assert(bolun_driver_find("modem") != 0);
    assert(bolun_driver_find("buttons") != 0);
    const bolun_device_t *display = bolun_device_find("display");
    assert(display != 0 && display->online);
    const bolun_device_t *wifi = bolun_device_find("wi-fi");
    assert(wifi != 0 && wifi->online);
    assert(bolun_lumia_profile("Lumia 625H") != 0);
    assert(bolun_lumia_profile("Redmi 9A") != 0);
    assert(bolun_lumia_profile("Redmi 9C NFC") != 0);
    assert(bolun_service_register("power", 1) >= 0);
    assert(bolun_service_set_running("power", true) == 0);

    unsigned char fs_image[2048];
    assert(bolun_fs_format(fs_image, sizeof(fs_image), BOLUN_FS_FAT32) == 0);
    assert(bolun_fs_detect(fs_image, sizeof(fs_image)) == BOLUN_FS_FAT32);
    assert(bolun_fs_format(fs_image, sizeof(fs_image), BOLUN_FS_EXT4) == 0);
    assert(bolun_fs_detect(fs_image, sizeof(fs_image)) == BOLUN_FS_EXT4);

    unsigned char udp[32];
    assert(bolun_udp_build(udp, sizeof(udp), 68, 67, mtext, sizeof(mtext)) == 8 + (int)sizeof(mtext));
    unsigned char ip[64];
    assert(bolun_ipv4_build(ip, sizeof(ip), 0x0a000001u, 0x0a000002u, 17, udp, 8u + sizeof(mtext)) == 28 + (int)sizeof(mtext));
    assert(bolun_inet_checksum(ip, 20) == 0);

    assert(bolun_vfs_create("/system/config", BOLUN_VFS_READ | BOLUN_VFS_WRITE) == 0);
    assert(bolun_vfs_write("/system/config", mtext, sizeof(mtext), 0) == (int)sizeof(mtext));
    memset(b, 0, sizeof(b));
    assert(bolun_vfs_read("/system/config", b, sizeof(b), 0) == (int)sizeof(mtext));
    assert(strcmp(b, mtext) == 0);
    assert(bolun_vfs_snapshot("/system/config", "/system/config.snap") == 0);
    assert(bolun_page_cache_put("/system/config", 0, mtext, sizeof(mtext), true) == 0);
    memset(b, 0, sizeof(b));
    assert(bolun_page_cache_get("/system/config", 0, b, sizeof(b)) == (int)sizeof(mtext));
    assert(strcmp(b, mtext) == 0);

    bolun_process_exit(p, 7);
    assert(bolun_wait(1, p) == 7);
    return 0;
}
