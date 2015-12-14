/*-
 * GPL LICENSE SUMMARY
 *
 *   Copyright(c) 2015 Cavium Networks. All rights reserved.
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of version 2 of the GNU General Public License as
 *   published by the Free Software Foundation.
 *
 *   This program is distributed in the hope that it will be useful, but
 *   WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 *   The full GNU General Public License is included in this distribution
 *   in the file called LICENSE.GPL.
 *
 *   Contact Information:
 *   Cavium Networks
 */

#ifndef _IGBUIO_IOPORT_MISC_H_
#define _IGBUIO_IOPORT_MISC_H_

unsigned long igbuio_iomap(unsigned long addr);
int igbuio_ioport_register(void);
void igbuio_ioport_unregister(void);

#if defined(RTE_ARCH_ARM) || defined(RTE_ARCH_ARM64)
#ifdef CONFIG_HAS_IOPORT_MAP
/*
 * mmap driver to map x86-style PCI_IOBAR (i.e..cat /proc/ioport pci-bar-memory)
 * from kernel-space virtual address to user-space virtual address. This module
 * required for non-x86 archs example arm/arm64, as those archs donot do
 * IO_MAP_IO types access, Infact supports memory-mapped-IO. That is because
 * arm/arm64 doesn't support direct IO instruction, so the design approach is to
 * map `cat /proc/ioport` PCI_IOBAR's kernel-space virtual-addr to user-space
 * virtual-addr. Therefore the need for mmap-driver.
 */
#include <linux/fs.h>		/* file_operations */
#include <linux/miscdevice.h>
#include <linux/mm.h>		/* VM_IO */
#include <linux/uaccess.h>
#include <asm/page.h>
#include <asm/io.h>
#include <linux/sched.h>
#include <linux/pid.h>

void *__iomem mapped_io; /* ioport addr of `cat /proc/ioport` */

static int igbuio_ioport_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct page *npage;
	int ret = 0;

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	npage = vmalloc_to_page(mapped_io);
	ret = remap_pfn_range(vma, vma->vm_start,
				page_to_pfn(npage),
				vma->vm_end - vma->vm_start,
				vma->vm_page_prot);
	if (ret) {
		pr_info("Error: Failed to remap pfn=%lu error=%d\n",
			page_to_pfn(npage), ret);
	}
	return 0;
}

static const struct file_operations igbuio_ioport_fops = {
	.mmap		= igbuio_ioport_mmap,
};

static struct miscdevice igbuio_ioport_dev = {
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= "igb_ioport",
	.fops	= &igbuio_ioport_fops
};

unsigned long igbuio_iomap(unsigned long addr)
{
	mapped_io = ioport_map(addr, 0);
	return (unsigned long)(uintptr_t)mapped_io;
}

int igbuio_ioport_register(void)
{
	int ret;
	ret = misc_register(&igbuio_ioport_dev);
	if (ret < 0) {
		pr_info("Error: failed to register ioport map driver (%d)\n",
				ret);
		return ret;
	}
	return ret;
}

void igbuio_ioport_unregister(void)
{
	misc_deregister(&igbuio_ioport_dev);
}

#else /* !CONFIG_HAS_IOPORT_MAP */

#error "CONFIG_HAS_IOPORT_MAP not supported for $RTE_ARCH"

#endif /* CONFIG_HAS_IOPORT_MAP */

#else /* !RTE_ARCH_ARM, !RTE_ARCH_ARM64 */

unsigned long igbuio_iomap(unsigned long addr)
{
	/* non-arm case : simply return addr */
	return addr;
}

int igbuio_ioport_register(void)
{
	/* non-arm case : do nothing */
	return 0;
}

void igbuio_ioport_unregister(void)
{
	/* non-arm case : do nothing */
	return;
}

#endif /* RTE_ARCH_ARM , RTE_ARCH_ARM64 */

#endif /* _IGBUIO_IOPORT_MISC_H_ */
