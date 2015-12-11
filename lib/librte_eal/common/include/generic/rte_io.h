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

#ifndef _RTE_IO_H_
#define _RTE_IO_H_

/**
 * @file
 *
 * IO operations.
 *
 * This file defines an API for IO rd/wr inline-functions, API's of the style
 * {in , out}[bwl] and {in_p, out_p} [bwl].  which are architecture-dependent.
 * Used by non-x86 archs. In particular used by arm/arm64 arch.
 */

#include <stdint.h>

#if defined(RTE_ARCH_X86_64) || defined(RTE_ARCH_I686)
#include <sys/io.h>
#else

/**
 * Emulate x86-style of ioport api implementation for arm/arm64. Included API
 * - {in, out}{b, w, l}()
 * - {in_p, out_p} {b, w, l} ()
 */

static inline uint8_t inb(unsigned long addr);
static inline uint16_t inw(unsigned long addr);
static inline uint32_t inl(unsigned long addr);

static inline void outb(uint8_t value, unsigned long addr);
static inline void outw(uint16_t value, unsigned long addr);
static inline void outl(uint32_t value, unsigned long addr);

static inline uint8_t inb_p(unsigned long addr);
static inline uint16_t inw_p(unsigned long addr);
static inline uint32_t inl_p(unsigned long addr);

static inline void outb_p(uint8_t value, unsigned long addr);
static inline void outw_p(uint16_t value, unsigned long addr);
static inline void outl_p(uint32_t value, unsigned long addr);

#endif

#endif /* _RTE_IO_H_ */

