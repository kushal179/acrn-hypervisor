/*-
 * Copyright (c) 1989, 1990 William F. Jolitz
 * Copyright (c) 1990 The Regents of the University of California.
 * Copyright (c) 2017 Intel Corporation
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	from: @(#)segments.h	7.1 (Berkeley) 5/9/91
 * $FreeBSD$
 */

#ifndef CPU_H
#define CPU_H

/* Define page size */
#define CPU_PAGE_SHIFT          12
#define CPU_PAGE_SIZE           0x1000U
#define CPU_PAGE_MASK           0xFFFFFFFFFFFFF000UL

#define MMU_PTE_PAGE_SHIFT	CPU_PAGE_SHIFT
#define MMU_PDE_PAGE_SHIFT	21

/* Define CPU stack alignment */
#define CPU_STACK_ALIGN         16UL

/* CR0 register definitions */
#define CR0_PG                  (1U<<31)	/* paging enable */
#define CR0_CD                  (1U<<30)	/* cache disable */
#define CR0_NW                  (1U<<29)	/* not write through */
#define CR0_AM                  (1U<<18)	/* alignment mask */
#define CR0_WP                  (1U<<16)	/* write protect */
#define CR0_NE                  (1U<<5)	/* numeric error */
#define CR0_ET                  (1U<<4)	/* extension type */
#define CR0_TS                  (1U<<3)	/* task switched */
#define CR0_EM                  (1U<<2)	/* emulation */
#define CR0_MP                  (1U<<1)	/* monitor coprocessor */
#define CR0_PE                  (1U<<0)	/* protected mode enabled */

/* CR3 register definitions */
#define CR3_PWT                 (1U<<3)	/* page-level write through */
#define CR3_PCD                 (1U<<4)	/* page-level cache disable */

/* CR4 register definitions */
#define CR4_VME                 (1UL<<0)	/* virtual 8086 mode extensions */
#define CR4_PVI                 (1UL<<1)	/* protected mode virtual interrupts */
#define CR4_TSD                 (1UL<<2)	/* time stamp disable */
#define CR4_DE                  (1UL<<3)	/* debugging extensions */
#define CR4_PSE                 (1UL<<4)	/* page size extensions */
#define CR4_PAE                 (1UL<<5)	/* physical address extensions */
#define CR4_MCE                 (1UL<<6)	/* machine check enable */
#define CR4_PGE                 (1UL<<7)	/* page global enable */
#define CR4_PCE                 (1UL<<8)
/* performance monitoring counter enable */
#define CR4_OSFXSR              (1UL<<9)	/* OS support for FXSAVE/FXRSTOR */
#define CR4_OSXMMEXCPT          (1UL<<10)
/* OS support for unmasked SIMD floating point exceptions */
#define CR4_VMXE                (1UL<<13)	/* VMX enable */
#define CR4_SMXE                (1UL<<14)	/* SMX enable */
#define CR4_PCIDE               (1UL<<17)	/* PCID enable */
#define CR4_OSXSAVE             (1UL<<18)
#define CR4_SMEP                (1UL<<20)
#define CR4_SMAP                (1UL<<21)
/* XSAVE and Processor Extended States enable bit */


/*
 * Entries in the Interrupt Descriptor Table (IDT)
 */
#define IDT_DE      0U   /* #DE: Divide Error */
#define IDT_DB      1U   /* #DB: Debug */
#define IDT_NMI     2U   /* Nonmaskable External Interrupt */
#define IDT_BP      3U   /* #BP: Breakpoint */
#define IDT_OF      4U   /* #OF: Overflow */
#define IDT_BR      5U   /* #BR: Bound Range Exceeded */
#define IDT_UD      6U   /* #UD: Undefined/Invalid Opcode */
#define IDT_NM      7U   /* #NM: No Math Coprocessor */
#define IDT_DF      8U   /* #DF: Double Fault */
#define IDT_FPUGP   9U   /* Coprocessor Segment Overrun */
#define IDT_TS      10U  /* #TS: Invalid TSS */
#define IDT_NP      11U  /* #NP: Segment Not Present */
#define IDT_SS      12U  /* #SS: Stack Segment Fault */
#define IDT_GP      13U  /* #GP: General Protection Fault */
#define IDT_PF      14U  /* #PF: Page Fault */
#define IDT_MF      16U  /* #MF: FPU Floating-Point Error */
#define IDT_AC      17U  /* #AC: Alignment Check */
#define IDT_MC      18U  /* #MC: Machine Check */
#define IDT_XF      19U  /* #XF: SIMD Floating-Point Exception */
#define IDT_VE      20U  /* #VE: Virtualization Exception */

/*Bits in EFER special registers */
#define EFER_LMA 0x00000400U    /* Long mode active (R) */

/* CPU clock frequencies (FSB) */
#define CPU_FSB_83KHZ           83200
#define CPU_FSB_100KHZ          99840
#define CPU_FSB_133KHZ          133200
#define CPU_FSB_166KHZ          166400

/* Time conversions */
#define CPU_GHZ_TO_HZ           1000000000
#define CPU_GHZ_TO_KHZ          1000000
#define CPU_GHZ_TO_MHZ          1000
#define CPU_MHZ_TO_HZ           1000000
#define CPU_MHZ_TO_KHZ          1000

/* Boot CPU ID */
#define BOOT_CPU_ID             0U

/* hypervisor stack bottom magic('intl') */
#define SP_BOTTOM_MAGIC    0x696e746cUL

/* type of speculation control
 * 0 - no speculation control support
 * 1 - raw IBRS + IPBP support
 * 2 - with STIBP optimization support
 */
#define IBRS_NONE	0
#define IBRS_RAW	1
#define IBRS_OPT	2

#ifndef ASSEMBLER

/**********************************/
/* EXTERNAL VARIABLES             */
/**********************************/
extern uint8_t                _ld_bss_start[];
extern uint8_t                _ld_bss_end[];

/* In trampoline range, hold the jump target which trampline will jump to */
extern uint64_t               main_entry[1];

extern int ibrs_type;
extern spinlock_t trampoline_spinlock;

/*
 * To support per_cpu access, we use a special struct "per_cpu_region" to hold
 * the pattern of per CPU data. And we allocate memory for per CPU data
 * according to multiple this struct size and pcpu number.
 *
 *   +-------------------+------------------+---+------------------+
 *   | percpu for pcpu0  | percpu for pcpu1 |...| percpu for pcpuX |
 *   +-------------------+------------------+---+------------------+
 *   ^                   ^
 *   |                   |
 *   <per_cpu_region size>
 *
 * To access per cpu data, we use:
 *   per_cpu_base_ptr + sizeof(struct per_cpu_region) * curr_pcpu_id
 *   + offset_of_member_per_cpu_region
 * to locate the per cpu data.
 */

#define	PER_CPU_DATA_OFFSET(sym_addr)					\
	((uint64_t)(sym_addr) - (uint64_t)(_ld_cpu_data_start))

#define	PER_CPU_DATA_SIZE						\
	((uint64_t)_ld_cpu_data_end - (uint64_t)(_ld_cpu_data_start))

/* CPUID feature words */
#define	FEAT_1_ECX		0U     /* CPUID[1].ECX */
#define	FEAT_1_EDX		1U     /* CPUID[1].EDX */
#define	FEAT_7_0_EBX		2U     /* CPUID[EAX=7,ECX=0].EBX */
#define	FEAT_7_0_ECX		3U     /* CPUID[EAX=7,ECX=0].ECX */
#define	FEAT_7_0_EDX		4U     /* CPUID[EAX=7,ECX=0].EDX */
#define	FEAT_8000_0001_ECX	5U     /* CPUID[8000_0001].ECX */
#define	FEAT_8000_0001_EDX	6U     /* CPUID[8000_0001].EDX */
#define	FEAT_8000_0008_EBX	7U     /* CPUID[8000_0008].EAX */
#define	FEATURE_WORDS		8U
/**
 *The invalid cpu_id (INVALID_CPU_ID) is error
 *code for error handling, this means that
 *caller can't find a valid physical cpu
 *or virtual cpu.
 */
#define INVALID_CPU_ID 0xffffU
/**
 *The broadcast id (BROADCAST_CPU_ID)
 *used to notify all valid phyiscal cpu
 *or virtual cpu.
 */
#define BROADCAST_CPU_ID 0xfffeU

/* CPU states defined */
enum cpu_state {
	CPU_STATE_RESET = 0,
	CPU_STATE_INITIALIZING,
	CPU_STATE_RUNNING,
	CPU_STATE_HALTED,
	CPU_STATE_DEAD,
};

struct cpu_state_info {
	uint8_t			 px_cnt;	/* count of all Px states */
	const struct cpu_px_data *px_data;
	uint8_t			 cx_cnt;	/* count of all Cx entries */
	const struct cpu_cx_data *cx_data;
};

struct cpuinfo_x86 {
	uint8_t family, model;
	uint8_t virt_bits;
	uint8_t phys_bits;
	uint32_t cpuid_level;
	uint32_t extended_cpuid_level;
	uint64_t physical_address_mask;
	uint32_t cpuid_leaves[FEATURE_WORDS];
	char model_name[64];
	struct cpu_state_info state_info;
};
#ifdef STACK_PROTECTOR
struct stack_canary {
	/* Gcc generates extra code, using [fs:40] to access canary */
	uint8_t reserved[40];
	uint64_t canary;
};
#endif

extern struct cpuinfo_x86 boot_cpu_data;

#define MAX_PSTATE	20U	/* max num of supported Px count */
#define MAX_CSTATE	8U	/* max num of supported Cx count */

/* We support MAX_CSTATE num of Cx, means have (MAX_CSTATE - 1) Cx entries,
 * i.e. supported Cx entry index range from 1 to MAX_CX_ENTRY.
 */
#define MAX_CX_ENTRY	(MAX_CSTATE - 1U)

/* Function prototypes */
void cpu_dead(uint16_t pcpu_id);
void trampoline_start16(void);
int32_t hv_main(uint16_t cpu_id);
bool is_vapic_supported(void);
bool is_vapic_intr_delivery_supported(void);
bool is_vapic_virt_reg_supported(void);
bool cpu_has_cap(uint32_t bit);
void load_cpu_state_data(void);
void start_cpus();
void stop_cpus();

/* Read control register */
#define CPU_CR_READ(cr, result_ptr)                         \
{                                                           \
	asm volatile ("mov %%" __CPP_STRING(cr) ", %0"      \
			: "=r"(*result_ptr));               \
}

/* Write control register */
#define CPU_CR_WRITE(cr, value)                             \
{                                                           \
	asm volatile ("mov %0, %%" __CPP_STRING(cr)         \
			: /* No output */                   \
			: "r"(value));                      \
}

/* Read MSR */
#define CPU_MSR_READ(reg, msr_val_ptr)                      \
{                                                           \
	uint32_t  msrl, msrh;                                 \
	asm volatile (" rdmsr ":"=a"(msrl),                 \
			"=d"(msrh) : "c" (reg));            \
	*msr_val_ptr = ((uint64_t)msrh<<32) | msrl;           \
}

/* Write MSR */
#define CPU_MSR_WRITE(reg, msr_val)                         \
{                                                           \
	uint32_t msrl, msrh;                                  \
	msrl = (uint32_t)msr_val;                             \
	msrh = (uint32_t)(msr_val >> 32);                     \
	asm volatile (" wrmsr " : : "c" (reg),              \
			"a" (msrl), "d" (msrh));            \
}

/* Disables interrupts on the current CPU */
#define CPU_IRQ_DISABLE()                                   \
{                                                           \
	asm volatile ("cli\n" : : : "cc");                  \
}

/* Enables interrupts on the current CPU */
#define CPU_IRQ_ENABLE()                                    \
{                                                           \
	asm volatile ("sti\n" : : : "cc");                  \
}

/* This macro writes the stack pointer. */
#define CPU_SP_WRITE(stack_ptr)                             \
{                                                           \
	uint64_t rsp = (uint64_t)stack_ptr & ~(CPU_STACK_ALIGN - 1UL);  \
	asm volatile ("movq %0, %%rsp" : : "r"(rsp));             \
}

/* Synchronizes all read accesses from memory */
#define CPU_MEMORY_READ_BARRIER()                           \
{                                                           \
	asm volatile ("lfence\n" : : : "memory");           \
}

/* Synchronizes all write accesses to memory */
#define CPU_MEMORY_WRITE_BARRIER()                          \
{                                                           \
	asm volatile ("sfence\n" : : : "memory");           \
}

/* Synchronizes all read and write accesses to/from memory */
#define CPU_MEMORY_BARRIER()                                \
{                                                           \
	asm volatile ("mfence\n" : : : "memory");           \
}

/* Write the task register */
#define CPU_LTR_EXECUTE(ltr_ptr)                            \
{                                                           \
	asm volatile ("ltr %%ax\n" : : "a"(ltr_ptr));       \
}

/* Read time-stamp counter / processor ID */
#define CPU_RDTSCP_EXECUTE(timestamp_ptr, cpu_id_ptr)       \
{                                                           \
	uint32_t  tsl, tsh;                                   \
	asm volatile ("rdtscp":"=a"(tsl), "=d"(tsh),        \
			"=c"(*cpu_id_ptr));                 \
	*timestamp_ptr = ((uint64_t)tsh << 32) | tsl;         \
}

/* Define variable(s) required to save / restore architecture interrupt state.
 * These variable(s) are used in conjunction with the ESAL_AR_INT_ALL_DISABLE()
 * and ESAL_AR_INT_ALL_RESTORE() macros to hold any data that must be preserved
 * in order to allow these macros to function correctly.
 */
#define         CPU_INT_CONTROL_VARS                uint64_t    cpu_int_value

/* Macro to save rflags register */
#define CPU_RFLAGS_SAVE(rflags_ptr)                     \
{                                                       \
	asm volatile (" pushf");                        \
	asm volatile (" pop %0"                         \
			: "=r" (*(rflags_ptr))          \
			: /* No inputs */);             \
}

/* Macro to restore rflags register */
#define CPU_RFLAGS_RESTORE(rflags)                      \
{                                                       \
	asm volatile (" push %0\n\t"			\
			"popf	\n\t": : "r" (rflags)	\
			:"cc");				\
}

/* This macro locks out interrupts and saves the current architecture status
 * register / state register to the specified address.  This function does not
 * attempt to mask any bits in the return register value and can be used as a
 * quick method to guard a critical section.
 * NOTE:  This macro is used in conjunction with CPU_INT_ALL_RESTORE
 *        defined below and CPU_INT_CONTROL_VARS defined above.
 */

#define CPU_INT_ALL_DISABLE()                       \
{                                                   \
	CPU_RFLAGS_SAVE(&cpu_int_value);            \
	CPU_IRQ_DISABLE();                          \
}

/* This macro restores the architecture status / state register used to lockout
 * interrupts to the value provided.  The intent of this function is to be a
 * fast mechanism to restore the interrupt level at the end of a critical
 * section to its original level.
 * NOTE:  This macro is used in conjunction with CPU_INT_ALL_DISABLE
 *        and CPU_INT_CONTROL_VARS defined above.
 */
#define CPU_INT_ALL_RESTORE()                       \
{                                                   \
	CPU_RFLAGS_RESTORE(cpu_int_value);          \
}

/* Macro to get CPU ID */
static inline uint16_t get_cpu_id(void)
{
	uint32_t tsl, tsh, cpu_id;

	asm volatile ("rdtscp":"=a" (tsl), "=d"(tsh), "=c"(cpu_id)::);
	return (uint16_t)cpu_id;
}

static inline uint64_t cpu_rsp_get(void)
{
	uint64_t ret;

	asm volatile("movq %%rsp, %0"
			:  "=r"(ret));
	return ret;
}

static inline uint64_t cpu_rbp_get(void)
{
	uint64_t ret;

	asm volatile("movq %%rbp, %0"
			:  "=r"(ret));
	return ret;
}



static inline uint64_t
msr_read(uint32_t reg_num)
{
	uint64_t msr_val;

	CPU_MSR_READ(reg_num, &msr_val);
	return msr_val;
}

static inline void
msr_write(uint32_t reg_num, uint64_t value64)
{
	CPU_MSR_WRITE(reg_num, value64);
}

static inline void
write_xcr(int reg, uint64_t val)
{
	uint32_t low, high;

	low = (uint32_t)val;
	high = (uint32_t)(val >> 32);
	asm volatile("xsetbv" : : "c" (reg), "a" (low), "d" (high));
}
#else /* ASSEMBLER defined */

#endif /* ASSEMBLER defined */

#endif /* CPU_H */
