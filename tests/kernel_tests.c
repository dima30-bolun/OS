#include "bolun/kernel.h"
#include <assert.h>
#include <string.h>


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
    assert(bolun_virtual_alloc(p, 0x400000, 8192, 3) == 0);
    assert(bolun_page_fault(p, 0x400123, true) == 0);

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

    const char mtext[] = "hello";
    assert(bolun_ipc_send(1, p, mtext, sizeof(mtext)) == 0);
    char b[8];
    assert(bolun_ipc_recv(p, b, sizeof(b)) == (int)sizeof(mtext));
    assert(strcmp(b, mtext) == 0);

    size_t driver_count = bolun_lumia_driver_count();
    assert(driver_count == 36);
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
    assert(bolun_service_register("power", 1) >= 0);
    assert(bolun_service_set_running("power", true) == 0);

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
