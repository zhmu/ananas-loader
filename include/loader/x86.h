#ifndef __LOADER_X86_H__
#define __LOADER_X86_H__

#include <loader/types.h>

struct LOADER_MODULE;
struct BOOTINFO;

struct REALMODE_REGS {
	uint32_t	eax;
	uint32_t	ebx;
	uint32_t	ecx;
	uint32_t	edx;
	uint32_t	ebp;
	uint32_t	esi;
	uint32_t	edi;
	uint32_t	esp;
	uint16_t	ds;
	uint16_t	es;
	uint16_t	ss;
	uint32_t	eflags;
#define EFLAGS_CF	(1 << 0)		/* Carry flag */
#define EFLAGS_PF	(1 << 2)		/* Parity flag */
#define EFLAGS_AF	(1 << 4)		/* Auxiliary carry flag */
#define EFLAGS_ZF	(1 << 6)		/* Zero flag */
#define EFLAGS_SF	(1 << 7)		/* Sign flag */
#define EFLAGS_IF	(1 << 9)		/* Interrupt flag */
#define EFLAGS_DF	(1 << 10)		/* Direction flag */
	uint8_t		interrupt;
	uint16_t	cs;
	uint16_t	ip;
} __attribute__((packed));

#define MAKE_SEGMENT(x) (((addr_t)x) >> 4)
#define MAKE_OFFSET(x)  (((addr_t)x) & 0xf)

extern void  realcall(struct REALMODE_REGS*);
extern void* entry;
extern void* rm_stack;
extern void* realmode_buffer;

void x86_realmode_init(struct REALMODE_REGS* regs);
void x86_realmode_push16(struct REALMODE_REGS* regs, uint16_t value);
#ifdef DEBUG_CALLS
void x86_realmode_call(struct REALMODE_REGS*);
#else
#define x86_realmode_call(x) \
	realcall(x)
#endif
void x86_64_exec(struct LOADER_MODULE* mod, struct BOOTINFO* bootinfo);
void x86_64_launch(uint64_t elf_start_addr, struct BOOTINFO* bootinfo);

#endif /* __LOADER_X86_H__ */
