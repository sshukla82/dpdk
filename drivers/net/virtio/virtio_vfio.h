/*
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
#ifndef _VIRTIO_VFIO_H_
#define _VIRTIO_VFIO_H_

#ifdef RTE_EAL_VFIO
#include <stdio.h>
#include <stdint.h>
#include <rte_pci.h>

#include "virtio_logs.h"

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
		PMD_DRV_LOG(ERR, "Can't read from PCI bar space");
		return;
	}
}


static inline void ioport_outw_p(const struct rte_pci_device *pci_dev,
				 uint16_t reg, uint16_t val)
{
	if (rte_eal_pci_write_bar(pci_dev, (uint16_t *)&val, sizeof(uint16_t),
				  reg, 0) <= 0) {
		PMD_DRV_LOG(ERR, "Can't read from PCI bar space");
		return;
	}
}


static inline void ioport_outl_p(const struct rte_pci_device *pci_dev,
				 uint32_t reg, uint32_t val)
{
	if (rte_eal_pci_write_bar(pci_dev, (uint32_t *)&val, sizeof(uint32_t),
				  reg, 0) <= 0) {
		PMD_DRV_LOG(ERR, "Can't read from PCI bar space");
		return;
	}
}

#define VIRTIO_READ_REG_1(hw, reg)				\
({								\
	uint8_t ret;						\
	ioport_inb(((hw)->pci_dev), reg, &ret);			\
	ret;							\
})

#define VIRTIO_WRITE_REG_1(hw, reg, val)			\
({								\
	ioport_outb_p(((hw)->pci_dev), reg, (uint8_t)val);	\
})

#define VIRTIO_READ_REG_2(hw, reg)				\
({								\
	uint16_t ret;						\
	ioport_inw(((hw)->pci_dev), reg, &ret);			\
	ret;							\
})

#define VIRTIO_WRITE_REG_2(hw, reg, val)			\
({								\
	ioport_outw_p(((hw)->pci_dev), reg, (uint16_t)(val));\
})

#define VIRTIO_READ_REG_4(hw, reg)				\
({								\
	uint32_t ret;						\
	ioport_inl(((hw)->pci_dev), reg, &ret);			\
	ret;							\
})

#define VIRTIO_WRITE_REG_4(hw, reg, val)			\
({								\
	ioport_outl_p(((hw)->pci_dev), reg, (uint32_t)(val));\
})

#else /* !RTE_EAL_VFIO */

#error "vfio not supported!!! pl. enable vfio config for your platform"
#endif /* RTE_EAL_VFIO */
#endif /* _VIRTIO_VFIO_H_ */
