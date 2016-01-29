/*
 *   BSD LICENSE
 *
 *   Copyright(c) 2016 Cavium Networks. All rights reserved.
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *    A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *    OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#ifndef _VIRTIO_IO_H_
#define _VIRTIO_IO_H_

#include <rte_common.h>
#include "virtio_vfio_io.h"

#if defined(RTE_ARCH_X86_64) || defined(RTE_ARCH_I686)

#ifdef __FreeBSD__
#include <sys/types.h>
#include <machine/cpufunc.h>

static inline void
outb_p(unsigned char data, unsigned int port)
{

	outb(port, (u_char)data);
}

static inline void
outw_p(unsigned short data, unsigned int port)
{
	outw(port, (u_short)data);
}

static inline void
outl_p(unsigned int data, unsigned int port)
{
	outl(port, (u_int)data);
}

#else
#include <sys/io.h>
#endif

#else /* ! X86 */

static inline uint8_t
inb(unsigned long addr __rte_unused)
{
	PMD_INIT_LOG(ERR, "inb() not supported for this RTE_ARCH\n");
	return 0;
}

static inline uint16_t
inw(unsigned long addr __rte_unused)
{
	PMD_INIT_LOG(ERR, "inw() not supported for this RTE_ARCH\n");
	return 0;
}

static inline uint32_t
inl(unsigned long addr __rte_unused)
{
	PMD_INIT_LOG(ERR, "in() not supported for this RTE_ARCH\n");
	return 0;
}

static inline void
outb_p(unsigned char data __rte_unused, unsigned int port __rte_unused)
{
	PMD_INIT_LOG(ERR, "outb_p() not supported for this RTE_ARCH\n");
	return;
}

static inline void
outw_p(unsigned short data __rte_unused, unsigned int port __rte_unused)
{
	PMD_INIT_LOG(ERR, "outw_p() not supported for this RTE_ARCH\n");
	return;
}

static inline void
outl_p(unsigned int data __rte_unused, unsigned int port __rte_unused)
{
	PMD_INIT_LOG(ERR, "outl_p() not supported for this RTE_ARCH\n");
	return;
}

#endif /* X86 */
#endif /* _VIRTIO_IO_H_ */
