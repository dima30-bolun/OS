#include "bolun/kernel.h"

void bolun_mutex_init(bolun_mutex_t *m)
{
    if (m) {
        m->locked = 0;
        m->owner_tid = 0;
    }
}

int bolun_mutex_lock(bolun_mutex_t *m, int tid)
{
    if (!m || tid <= 0) {
        return -1;
    }
    if (__sync_bool_compare_and_swap(&m->locked, 0, 1)) {
        m->owner_tid = tid;
        return 0;
    }
    return m->owner_tid == tid ? 0 : -2;
}

int bolun_mutex_unlock(bolun_mutex_t *m, int tid)
{
    if (!m || m->owner_tid != tid) {
        return -1;
    }
    m->owner_tid = 0;
    __sync_lock_release(&m->locked);
    return 0;
}

void bolun_spin_init(bolun_spinlock_t *s)
{
    if (s) {
        s->locked = 0;
    }
}

int bolun_spin_lock(bolun_spinlock_t *s)
{
    if (!s) {
        return -1;
    }
    for (unsigned i = 0; i < 100000; i++) {
        if (__sync_bool_compare_and_swap(&s->locked, 0, 1)) {
            return 0;
        }
    }
    return -2;
}

void bolun_spin_unlock(bolun_spinlock_t *s)
{
    if (s) {
        __sync_lock_release(&s->locked);
    }
}

void bolun_rwlock_init(bolun_rwlock_t *rw)
{
    if (rw) {
        rw->readers = 0;
        rw->writer_tid = 0;
    }
}

int bolun_rwlock_read_lock(bolun_rwlock_t *rw)
{
    if (!rw || rw->writer_tid != 0) {
        return -1;
    }
    rw->readers++;
    return 0;
}

int bolun_rwlock_read_unlock(bolun_rwlock_t *rw)
{
    if (!rw || rw->readers <= 0) {
        return -1;
    }
    rw->readers--;
    return 0;
}

int bolun_rwlock_write_lock(bolun_rwlock_t *rw, int tid)
{
    if (!rw || tid <= 0 || rw->readers != 0 || rw->writer_tid != 0) {
        return -1;
    }
    rw->writer_tid = tid;
    return 0;
}

int bolun_rwlock_write_unlock(bolun_rwlock_t *rw, int tid)
{
    if (!rw || rw->writer_tid != tid) {
        return -1;
    }
    rw->writer_tid = 0;
    return 0;
}

void bolun_semaphore_init(bolun_semaphore_t *s, int count)
{
    if (s) {
        s->count = count < 0 ? 0 : count;
    }
}

int bolun_semaphore_wait(bolun_semaphore_t *s)
{
    if (!s) {
        return -1;
    }
    if (s->count <= 0) {
        return -2;
    }
    s->count--;
    return 0;
}

void bolun_semaphore_post(bolun_semaphore_t *s)
{
    if (s) {
        s->count++;
    }
}

void bolun_event_init(bolun_event_t *e, bool signaled)
{
    if (e) {
        e->signaled = signaled;
    }
}

int bolun_event_wait(bolun_event_t *e)
{
    if (!e) {
        return -1;
    }
    if (!e->signaled) {
        return -2;
    }
    e->signaled = false;
    return 0;
}

void bolun_event_signal(bolun_event_t *e)
{
    if (e) {
        e->signaled = true;
    }
}
