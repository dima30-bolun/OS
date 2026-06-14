#ifndef BOLUN_KERNEL_H
#define BOLUN_KERNEL_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define BOLUN_MAX_PROCESSES 64
#define BOLUN_MAX_THREADS 128
#define BOLUN_MAX_HANDLES 256
#define BOLUN_MAX_DRIVERS 64
#define BOLUN_MAX_SERVICES 64
#define BOLUN_MAX_DEVICES 128
#define BOLUN_MAX_VFS_NODES 128
#define BOLUN_MAX_PAGE_CACHE 64
#define BOLUN_PAGE_SIZE 4096u
#define BOLUN_VFS_READ 1u
#define BOLUN_VFS_WRITE 2u

typedef enum {
    BOLUN_READY,
    BOLUN_RUNNING,
    BOLUN_WAITING,
    BOLUN_BLOCKED,
    BOLUN_TERMINATED
} bolun_state_t;

typedef enum {
    CAP_FS = 1u << 0,
    CAP_NET = 1u << 1,
    CAP_DEVICE = 1u << 2,
    CAP_PHONE = 1u << 3,
    CAP_SYSTEM = 1u << 4
} bolun_cap_t;

typedef enum {
    BOLUN_ARCH_ARMV7,
    BOLUN_ARCH_ARMV8,
    BOLUN_ARCH_ARM64,
    BOLUN_ARCH_X86,
    BOLUN_ARCH_X86_64,
    BOLUN_ARCH_RISCV64
} bolun_arch_t;

typedef enum {
    BOLUN_BUS_ROOT,
    BOLUN_BUS_DEVICE_TREE,
    BOLUN_BUS_ACPI,
    BOLUN_BUS_PCI,
    BOLUN_BUS_USB,
    BOLUN_BUS_GPIO,
    BOLUN_BUS_I2C,
    BOLUN_BUS_SPI,
    BOLUN_BUS_UART,
    BOLUN_BUS_DMA,
    BOLUN_BUS_RTC,
    BOLUN_BUS_PWM
} bolun_bus_t;

typedef struct {
    uint32_t r[16];
    uint32_t cpsr;
    uint32_t ttbr0;
    uint8_t asid;
} armv7_context_t;

typedef struct {
    uintptr_t va;
    uintptr_t pa;
    uint32_t flags;
    uint16_t refs;
    bool cow;
    bool present;
} bolun_page_t;

typedef struct {
    int id;
    int owner;
    uint32_t rights;
    void *object;
} bolun_handle_t;

typedef struct {
    int tid;
    int pid;
    int priority;
    bolun_state_t state;
    uint64_t wake_tick;
    armv7_context_t ctx;
} bolun_thread_t;

typedef struct {
    int pid;
    int parent;
    uint32_t caps;
    uint8_t asid;
    bolun_state_t state;
    bolun_page_t pages[128];
    size_t page_count;
    bolun_handle_t handles[32];
    int exit_code;
} bolun_process_t;

typedef struct { volatile int locked; int owner_tid; } bolun_mutex_t;
typedef struct { volatile int locked; } bolun_spinlock_t;
typedef struct { int readers; int writer_tid; } bolun_rwlock_t;
typedef struct { int count; } bolun_semaphore_t;
typedef struct { bool signaled; } bolun_event_t;

typedef struct {
    const char *name;
    const char *device_class;
    uint32_t required_caps;
    bool active;
} bolun_driver_t;

typedef struct {
    const char *name;
    int owner_pid;
    bool running;
} bolun_service_t;

typedef struct {
    const char *model;
    uint32_t soc_id;
    bolun_arch_t arch;
    uint32_t ram_mb;
    const char *display;
    const char *modem;
} bolun_hw_profile_t;

typedef struct {
    const char *name;
    bolun_bus_t bus;
    const char *compatible;
    const char *driver_class;
    bool online;
} bolun_device_t;

typedef struct {
    bolun_arch_t arch;
    uint32_t cores;
    uint64_t timer_hz;
    bool has_mmu;
    bool has_nx;
    bool has_aslr;
} bolun_hal_info_t;

typedef struct {
    char path[64];
    uint32_t mode;
    uint8_t data[512];
    size_t size;
    uint64_t version;
    bool used;
} bolun_vfs_node_t;

typedef struct {
    char path[64];
    uint32_t page_index;
    uint8_t data[BOLUN_PAGE_SIZE];
    size_t valid;
    bool dirty;
    bool used;
} bolun_page_cache_entry_t;

typedef struct {
    bolun_process_t processes[BOLUN_MAX_PROCESSES];
    bolun_thread_t threads[BOLUN_MAX_THREADS];
    bolun_handle_t handles[BOLUN_MAX_HANDLES];
    bolun_driver_t drivers[BOLUN_MAX_DRIVERS];
    bolun_service_t services[BOLUN_MAX_SERVICES];
    bolun_device_t devices[BOLUN_MAX_DEVICES];
    bolun_vfs_node_t vfs_nodes[BOLUN_MAX_VFS_NODES];
    bolun_page_cache_entry_t page_cache[BOLUN_MAX_PAGE_CACHE];
    bolun_hal_info_t hal;
    uint64_t ticks;
    int current_tid;
} bolun_kernel_t;

extern bolun_kernel_t g_kernel;

void bolun_kernel_boot(void);
void bolun_panic(const char *reason);
void armv7_switch(armv7_context_t *from, const armv7_context_t *to);
int bolun_process_create(int parent, uint32_t caps);
int bolun_thread_create(int pid, uintptr_t entry, int priority);
void bolun_process_exit(int pid, int code);
int bolun_wait(int parent, int child);
void bolun_schedule_tick(void);
int bolun_virtual_alloc(int pid, uintptr_t va, size_t bytes, uint32_t flags);
int bolun_virtual_free(int pid, uintptr_t va, size_t bytes);
int bolun_page_fault(int pid, uintptr_t va, bool write);
int bolun_syscall(int nr, uintptr_t a, uintptr_t b, uintptr_t c, uintptr_t d);
int bolun_ipc_send(int src, int dst, const void *data, size_t len);
int bolun_ipc_recv(int pid, void *data, size_t cap);
int bolun_open_handle(int pid, void *object, uint32_t rights);
bool bolun_check_cap(int pid, uint32_t cap);
void bolun_mutex_init(bolun_mutex_t *m);
int bolun_mutex_lock(bolun_mutex_t *m, int tid);
int bolun_mutex_unlock(bolun_mutex_t *m, int tid);
void bolun_spin_init(bolun_spinlock_t *s);
int bolun_spin_lock(bolun_spinlock_t *s);
void bolun_spin_unlock(bolun_spinlock_t *s);
void bolun_rwlock_init(bolun_rwlock_t *rw);
int bolun_rwlock_read_lock(bolun_rwlock_t *rw);
int bolun_rwlock_read_unlock(bolun_rwlock_t *rw);
int bolun_rwlock_write_lock(bolun_rwlock_t *rw, int tid);
int bolun_rwlock_write_unlock(bolun_rwlock_t *rw, int tid);
void bolun_semaphore_init(bolun_semaphore_t *s, int count);
int bolun_semaphore_wait(bolun_semaphore_t *s);
void bolun_semaphore_post(bolun_semaphore_t *s);
void bolun_event_init(bolun_event_t *e, bool signaled);
int bolun_event_wait(bolun_event_t *e);
void bolun_event_signal(bolun_event_t *e);
int bolun_driver_register(const char *name, const char *device_class, uint32_t required_caps);
const bolun_driver_t *bolun_driver_find(const char *device_class);
int bolun_device_register(const char *name, bolun_bus_t bus, const char *compatible, const char *driver_class);
const bolun_device_t *bolun_device_find(const char *name);
int bolun_device_bind_all(void);
int bolun_service_register(const char *name, int owner_pid);
int bolun_service_set_running(const char *name, bool running);
const bolun_hw_profile_t *bolun_lumia_profile(const char *model);
size_t bolun_lumia_driver_count(void);
int bolun_lumia_probe_all(void);
void bolun_hal_init(bolun_arch_t arch, uint32_t cores, uint64_t timer_hz, bool has_mmu);
const bolun_hal_info_t *bolun_hal_info(void);
uint64_t bolun_hal_timer_deadline(uint64_t ticks_from_now);
int bolun_vfs_create(const char *path, uint32_t mode);
int bolun_vfs_write(const char *path, const void *data, size_t len, size_t off);
int bolun_vfs_read(const char *path, void *data, size_t len, size_t off);
int bolun_vfs_snapshot(const char *from, const char *to);
int bolun_page_cache_put(const char *path, uint32_t page_index, const void *data, size_t len, bool dirty);
int bolun_page_cache_get(const char *path, uint32_t page_index, void *data, size_t cap);

#endif
