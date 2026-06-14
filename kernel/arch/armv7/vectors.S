.syntax unified
.cpu cortex-a7
.arm
.global bolun_vector_reset
.global bolun_vector_undef
.global bolun_vector_svc
.global bolun_vector_prefetch_abort
.global bolun_vector_data_abort
.global bolun_vector_irq
.global bolun_vector_fiq
bolun_vector_reset: b bolun_vector_reset
bolun_vector_undef: b bolun_vector_undef
bolun_vector_svc: bx lr
bolun_vector_prefetch_abort: bx lr
bolun_vector_data_abort: bx lr
bolun_vector_irq: bx lr
bolun_vector_fiq: bx lr
