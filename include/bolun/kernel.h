#ifndef BOLUN_KERNEL_H
#define BOLUN_KERNEL_H
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#define BOLUN_MAX_PROCESSES 64
#define BOLUN_MAX_THREADS 128
#define BOLUN_MAX_HANDLES 256
#define BOLUN_PAGE_SIZE 4096u
typedef enum { BOLUN_READY, BOLUN_RUNNING, BOLUN_WAITING, BOLUN_BLOCKED, BOLUN_TERMINATED } bolun_state_t;
typedef enum { CAP_FS=1u<<0, CAP_NET=1u<<1, CAP_DEVICE=1u<<2, CAP_PHONE=1u<<3, CAP_SYSTEM=1u<<4 } bolun_cap_t;
typedef struct { uint32_t r[16]; uint32_t cpsr; uint32_t ttbr0; uint8_t asid; } armv7_context_t;
typedef struct { uintptr_t va; uintptr_t pa; uint32_t flags; uint16_t refs; bool cow; bool present; } bolun_page_t;
typedef struct { int id; int owner; uint32_t rights; void *object; } bolun_handle_t;
typedef struct { int tid; int pid; int priority; bolun_state_t state; uint64_t wake_tick; armv7_context_t ctx; } bolun_thread_t;
typedef struct { int pid; int parent; uint32_t caps; uint8_t asid; bolun_state_t state; bolun_page_t pages[128]; size_t page_count; bolun_handle_t handles[32]; int exit_code; } bolun_process_t;
typedef struct { bolun_process_t processes[BOLUN_MAX_PROCESSES]; bolun_thread_t threads[BOLUN_MAX_THREADS]; bolun_handle_t handles[BOLUN_MAX_HANDLES]; uint64_t ticks; int current_tid; } bolun_kernel_t;
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
#endif
