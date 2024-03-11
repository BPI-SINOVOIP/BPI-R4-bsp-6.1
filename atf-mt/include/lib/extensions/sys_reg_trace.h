/*
 * Copyright (c) 2021-2023, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SYS_REG_TRACE_H
#define SYS_REG_TRACE_H

#include <context.h>

#if ENABLE_SYS_REG_TRACE_FOR_NS

#if __aarch64__
void sys_reg_trace_enable(cpu_context_t *context);
void sys_reg_trace_disable(cpu_context_t *context);
void sys_reg_trace_init_el2_unused(void);
#else
void sys_reg_trace_init_el3(void);
#endif /* __aarch64__ */

#else /* !ENABLE_SYS_REG_TRACE_FOR_NS */

#if __aarch64__
static inline void sys_reg_trace_enable(cpu_context_t *context)
{
}
static inline void sys_reg_trace_disable(cpu_context_t *context)
{
}
static inline void sys_reg_trace_init_el2_unused(void)
{
}
#else
static inline void sys_reg_trace_init_el3(void)
{
}
#endif /* __aarch64__ */

#endif /* ENABLE_SYS_REG_TRACE_FOR_NS */

#endif /* SYS_REG_TRACE_H */
