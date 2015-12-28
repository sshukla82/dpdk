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

#include "virtio_ioport.h"

#if defined(RTE_EXEC_ENV_LINUXAPP) && (defined(RTE_ARCH_ARM) || \
		defined(RTE_ARCH_ARM64))

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/mman.h>
#include <exec-env/rte_virt_ioport.h>

#include "virtio_logs.h"

/* start address of first pci_iobar slot (user-space virtual-addres) */
void *ioport_map;
/**
 * ioport map count,
 * Use-case: virtio-net-pci.
 * Keeps track of number of virtio-net-pci device mapped/unmapped. Max device
 * support by linux kernel is 31, so ioport_map_cnt can not be greater than 31.
 */
static int ioport_map_cnt;

static int
virtio_map_ioport(void **resource_addr)
{
	int fd;
	int ret = 0;

	/* avoid -Werror=unused-parameter, keep compiler happy */
	(void)resource_addr;
	fd = open(VIRT_IOPORT_DEV, O_RDWR);
	if (fd < 0) {
		PMD_INIT_LOG(ERR, "device file %s open error: %d\n",
			     VIRT_IOPORT_DEV, fd);
		ret = -1;
		goto out;
	}

	ioport_map = mmap(NULL, PCI_VIRT_IOPORT_SIZE,
			PROT_EXEC | PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);

	if (ioport_map == MAP_FAILED) {
		PMD_INIT_LOG(ERR, "mmap: failed to map bar Address=%p\n",
				*resource_addr);
		ret = -ENOMEM;
		goto out1;
	}

	PMD_INIT_LOG(INFO, "First pci_iobar mapped at %p\n", ioport_map);

out1:
	close(fd);
out:
	return ret;
}

static int
virtio_set_ioport_addr(void **resource_addr, unsigned long offset)
{
	int ret = 0;

	if (ioport_map_cnt >= PCI_VIRT_IOPORT_MAX) {
		ret = -1;
		PMD_INIT_LOG(ERR,
			     "ioport_map_cnt(%d) greater than"
			     "PCI_VIRT_IOPORT_MAX(%d)\n",
			     ioport_map_cnt, PCI_VIRT_IOPORT_MAX);
		return ret;
	}
	*resource_addr = (void *)((char *)ioport_map + (ioport_map_cnt)*offset);
	ioport_map_cnt++;

	PMD_INIT_LOG(DEBUG, "pci.resource_addr %p ioport_map_cnt %d\n",
			*resource_addr, ioport_map_cnt);
	return ret;
}

int virtio_ioport_init(struct rte_pci_resource *mem_resource)
{
	int ret = 0;

	(void)mem_resource;
	return 0;
	/**
	 * Map the all IOBAR entry from /proc/ioport to 4k page_size only once.
	 * Later virtio_set_ioport_addr() func will update correct bar_addr for
	 * each ioport (i.e..pci_dev->mem_resource[0].addr)
	 */
	if (!ioport_map) {
		ret = virtio_map_ioport(&mem_resource->addr);
		if (ret < 0)
			return ret;
		PMD_INIT_LOG(INFO, "ioport_map %p\n", ioport_map);
	}

	ret = virtio_set_ioport_addr(&mem_resource->addr, mem_resource->len);
	if (ret < 0)
		return ret;

	PMD_INIT_LOG(INFO, "resource_addr %p resource_len :%ld\n",
			mem_resource->addr, (unsigned long)mem_resource->len);
	return ret;
}

void virtio_ioport_unmap(void)
{
	/* unmap ioport memory */
	ioport_map_cnt--;
	if (!ioport_map_cnt)
		munmap(ioport_map, PCI_VIRT_IOPORT_SIZE);

	PMD_INIT_LOG(DEBUG, "unmapping ioport_mem %d\n", ioport_map_cnt);
}

#else /* !LINUXAPP && !ARM/64 */

int virtio_ioport_init(struct rte_pci_resource *mem_resource)
{
	(void)mem_resource;
	return 0;
}

void virtio_ioport_unmap(void)
{
	return;
}

#endif /* LINUXAPP, ARM/64 */
