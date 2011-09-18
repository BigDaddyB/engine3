/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#include "ProtectedHeap.h"

#include <sys/ioctl.h>
#include <sys/mman.h>

#include <multimmap.h>

void initializeKernelStatics(int deviceFD);

ProtectedHeap::ProtectedHeap() {
	heapBase = reinterpret_cast<void*>(2 * MULTIMMAP_HEAP_SIZE);
	flags = MAP_SHARED;
	offset = MULTIMMAP_KERNEL_HEAP_OFFSET;

	protectionLevel = 1;

	//linitializeKernelStatics(deviceFD);
}

void ProtectedHeap::protect() {
	assert(protectionLevel > 0);

	if (protectionLevel > 1)
		protectionLevel--;
	else
		setKernelMemoryProtection(0);
}

void ProtectedHeap::unprotect() {
	if (protectionLevel == 0)
		setKernelMemoryProtection(1);
	else
		protectionLevel++;
}

void initializeKernelStatics(int deviceFD)
{
    multimmap_statics_info statics_info;

    statics_info.start = 0;
    statics_info.size = 512 * 1024 * 1024 / 2;

    if (ioctl(deviceFD, MULTIMMAP_INIT_KERNEL_STATICS, &statics_info) < 0) {
        perror("ioctl");
        fprintf(stderr, "Failed to initialize kernel statics!\n");
        abort();
    }
}

void ProtectedHeap::setKernelMemoryProtection(unsigned desiredKEL)
{
    struct multimmap_kernel_memory_info memory_info = {
        (unsigned long long) heapBase,
        0,
        &protectionLevel,
        desiredKEL
    };

    if (ioctl(deviceFD, MULTIMMAP_KERNEL_MEMORY_RW, &memory_info)<0) {
        perror("ioctl[MULTIMMAP_KERNEL_MEMORY_RW]");
        abort();
    }

    //printf("multimmap changed kernel memory protection to %u\n", protectionLevel);
}
