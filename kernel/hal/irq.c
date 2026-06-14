#include "bolun/kernel.h"

typedef struct {
    bolun_irq_handler_t handler;
    void *ctx;
    bool enabled;
    uint64_t count;
} irq_slot_t;

static irq_slot_t irq_table[BOLUN_MAX_IRQS];

int bolun_irq_register(int irq, bolun_irq_handler_t handler, void *ctx)
{
    if (irq < 0 || irq >= BOLUN_MAX_IRQS || !handler) {
        return -1;
    }
    irq_table[irq].handler = handler;
    irq_table[irq].ctx = ctx;
    irq_table[irq].enabled = true;
    irq_table[irq].count = 0;
    return 0;
}

int bolun_irq_enable(int irq, bool enabled)
{
    if (irq < 0 || irq >= BOLUN_MAX_IRQS || !irq_table[irq].handler) {
        return -1;
    }
    irq_table[irq].enabled = enabled;
    return 0;
}

int bolun_irq_dispatch(int irq)
{
    if (irq < 0 || irq >= BOLUN_MAX_IRQS || !irq_table[irq].handler) {
        return -1;
    }
    if (!irq_table[irq].enabled) {
        return -2;
    }
    irq_table[irq].count++;
    irq_table[irq].handler(irq, irq_table[irq].ctx);
    return 0;
}
