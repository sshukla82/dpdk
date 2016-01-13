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
#ifndef _VIRTIO_VFIO_RW_H_
#define _VIRTIO_VFIO_RW_H_

#if defined(RTE_EAL_VFIO) && defined(RTE_LIBRTE_EAL_LINUXAPP)

#include <stdint.h>
#include <rte_pci.h>
#include "virtio_logs.h"

/* vfio rd/rw virtio apis */
static inline void ioport_inb(const struct rte_pci_device *pci_dev,
			      uint8_t reg, uint8_t *val)
{
	if (rte_eal_pci_read_bar(pci_dev, (uint8_t *)val, sizeof(uint8_t), reg,
				 0) <= 0) {
		PMD_DRV_LOG(ERR, "Can't read from PCI bar space");
		return;
	}
}

static inline void ioport_inw(const struct rte_pci_device *pci_dev,
			      uint16_t reg, uint16_t *val)
{
	if (rte_eal_pci_read_bar(pci_dev, (uint16_t *)val, sizeof(uint16_t),
				 reg, 0) <= 0) {
		PMD_DRV_LOG(ERR, "Can't read from PCI bar space");
		return;
	}
}

static inline void ioport_inl(const struct rte_pci_device *pci_dev,
			      uint32_t reg, uint32_t *val)
{
	if (rte_eal_pci_read_bar(pci_dev, (uint32_t *)val, sizeof(uint32_t),
				 reg, 0) <= 0) {
		PMD_DRV_LOG(ERR, "Can't read from PCI bar space");
		return;
	}
}

static inline void ioport_outb_p(const struct rte_pci_device *pci_dev,
				 uint8_t reg, uint8_t val)
{
	if (rte_eal_pci_write_bar(pci_dev, (uint8_t *)&val, sizeof(uint8_t),
				  reg, 0) <= 0) {
		PMD_DRV_LOG(ERR, "Can't write to PCI bar space");
		return;
	}
}


static inline void ioport_outw_p(const struct rte_pci_device *pci_dev,
				 uint16_t reg, uint16_t val)
{
	if (rte_eal_pci_write_bar(pci_dev, (uint16_t *)&val, sizeof(uint16_t),
				  reg, 0) <= 0) {
		PMD_DRV_LOG(ERR, "Can't write to PCI bar space");
		return;
	}
}


static inline void ioport_outl_p(const struct rte_pci_device *pci_dev,
				 uint32_t reg, uint32_t val)
{
	if (rte_eal_pci_write_bar(pci_dev, (uint32_t *)&val, sizeof(uint32_t),
				  reg, 0) <= 0) {
		PMD_DRV_LOG(ERR, "Can't write to PCI bar space");
		return;
	}
}

#endif /* RTE_EAL_VFIO && RTE_XX_EAL_LINUXAPP */
#endif /* _VIRTIO_VFIO_RW_H_ */
