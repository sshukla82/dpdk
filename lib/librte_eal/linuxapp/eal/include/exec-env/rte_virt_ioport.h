/*
 *   This file is provided under a dual BSD/LGPLv2 license.  When using or
 *   redistributing this file, you may do so under either license.
 *
 *   GNU LESSER GENERAL PUBLIC LICENSE
 *
 *   Copyright(c) 2015 Cavium Networks. All rights reserved.
 *   All rights reserved.
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of version 2.1 of the GNU Lesser General Public License
 *   as published by the Free Software Foundation.
 *
 *   This program is distributed in the hope that it will be useful, but
 *   WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *   Contact Information:
 *   Cavium Networks
 *
 *
 *   BSD LICENSE
 *
 *   Copyright(c) 2015 Cavium Networks. All rights reserved.
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
#ifndef _RTE_VIRTIO_IOPORT_H_
#define _RTE_VIRTIO_IOPORT_H_

#define VIRT_IOPORT_DEV		"/dev/igb_ioport"

/**
 * Keeping pci_virt_ioport_size = 4k.
 * So maximum mmaped pci_iobar supported =
 * (virt_ioport_size/pci_dev->mem_resource[0].len)
 * where, pci_dev->mem_resource[0].len == virtio_pci_iobar_len i.e.. 32 byte
 *
 * Note: kernel could allow maximum 32 virtio-net-pci interface, that mean
 * maximum 32 PCI_IOBAR(s) where each PCI_IOBAR_LEN=0x20, so virtio_map_ioport()
 * func by theory gonna support 4k/0x20 ==> 128 PCI_IOBAR(s), more than
 * max-virtio-net-pci interface.
 */
#define PAGE_SIZE		4096
#define PCI_VIRT_IOPORT_SIZE	PAGE_SIZE
#define PCI_VIRT_IOBAR_LEN	32
#define PCI_VIRT_IOPORT_MAX	(PCI_VIRT_IOPORT_SIZE/PCI_VIRT_IOBAR_LEN)
				/* 128 max ioport */

#endif /* _RTE_VIRTIO_IOPORT_H_ */
