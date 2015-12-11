/*
 *   BSD LICENSE
 *
 *   Copyright(c) 2015 Cavium Networks. All rights reserved.
 *   All rights reserved.
 *
 *   Copyright(c) 2010-2015 Intel Corporation. All rights reserved.
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Intel Corporation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _RTE_IO_ARM64_H_
#define _RTE_IO_ARM64_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "generic/rte_io.h"

/*
 * Generic IO read/write api for arm64: Refer TRM
 */
static inline void raw_writeb(uint8_t val, uint64_t addr)
{
	asm volatile("strb %w0, [%1]" : : "r" (val), "r" (addr));
}

static inline void raw_writew(uint16_t val, uint64_t addr)
{
	asm volatile("strh %w0, [%1]" : : "r" (val), "r" (addr));
}

static inline void raw_writel(uint32_t val, uint64_t addr)
{
	asm volatile("str %w0, [%1]" : : "r" (val), "r" (addr));
}

static inline uint8_t raw_readb(uint64_t addr)
{
	uint8_t val;
	asm volatile("ldrb %w0, [%1]" : "=r" (val) : "r" (addr));
	return val;
}

static inline uint16_t raw_readw(uint64_t addr)
{
	uint16_t val;
	asm volatile("ldrh %w0, [%1]" : "=r" (val) : "r" (addr));
	return val;
}

static inline uint32_t raw_readl(uint64_t addr)
{
	uint32_t val;
	asm volatile("ldr %w0, [%1]" : "=r" (val) : "r" (addr));
	return val;
}

/**
 * Emulate x86-style of ioport api implementation for arm/arm64. Included API
 * - {in, out}{b, w, l}()
 * - {in_p, out_p} {b, w, l} ()
 */

static inline uint8_t inb(unsigned long addr)
{
	return raw_readb(addr);
}

static inline uint16_t inw(unsigned long addr)
{
	return raw_readw(addr);
}

static inline uint32_t inl(unsigned long addr)
{
	return raw_readl(addr);
}

static inline void outb(uint8_t value, unsigned long addr)
{
	raw_writeb(value, addr);
}

static inline void outw(uint16_t value, unsigned long addr)
{
	raw_writew(value, addr);
}

static inline void outl(uint32_t value, unsigned long addr)
{
	raw_writel(value, addr);
}

static inline uint8_t inb_p(unsigned long addr)
{
	return inb(addr);
}

static inline uint16_t inw_p(unsigned long addr)
{
	return inw(addr);
}

static inline uint32_t inl_p(unsigned long addr)
{
	return inl(addr);
}

static inline void outb_p(uint8_t value, unsigned long addr)
{
	outb(value, addr);
}

static inline void outw_p(uint16_t value, unsigned long addr)
{
	outw(value, addr);
}

static inline void outl_p(uint32_t value, unsigned long addr)
{
	outl(value, addr);
}

#ifdef __cplusplus
}
#endif

#endif /* _RTE_IO_ARM64_H_ */
