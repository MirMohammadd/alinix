/**
 * MIT License
 *
 * Copyright (c) 2024 Heisenberg
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * @author Heisenberg

 */
#ifndef _CPU_CONTEXT_H_
#define _CPU_CONTEXT_H_

#include <lib/types.h>
#include <lib/status.h>

struct cpu_state;

/*
 * The type of the functions passed as arguments to the Kernel thread
 * related functions.
 */
typedef void (cpu_kstate_function_arg1_t(uint32_t arg1));

void cpu_kstate_init(struct cpu_state **kctxt,
		cpu_kstate_function_arg1_t *start_func,
		uint32_t start_arg,
		uint32_t stack_base,
		uint32_t stack_size);

void cpu_context_switch(struct cpu_state **from_ctxt,
		struct cpu_state *to_ctxt);

#endif // _CPU_CONTEXT_H_
