/*
 * Copyright (C) 2014-2017 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#pragma once

#include "AvailableMemory.h"
#include "Cache.h"
#include "Gigacage.h"
#include "Heap.h"
#include "IsoTLS.h"
#include "PerHeapKind.h"
#include "Scavenger.h"
#include "StaticMutex.h"

namespace bmalloc {
namespace api {

// Returns null on failure.
inline void* tryMalloc(size_t size, HeapKind kind = HeapKind::Primary)
{
    return Cache::tryAllocate(kind, size);
}

// Crashes on failure.
inline void* malloc(size_t size, HeapKind kind = HeapKind::Primary)
{
    return Cache::allocate(kind, size);
}

BEXPORT void* mallocOutOfLine(size_t size, HeapKind kind = HeapKind::Primary);

// Returns null on failure.
inline void* tryMemalign(size_t alignment, size_t size, HeapKind kind = HeapKind::Primary)
{
    return Cache::tryAllocate(kind, alignment, size);
}

// Crashes on failure.
inline void* memalign(size_t alignment, size_t size, HeapKind kind = HeapKind::Primary)
{
    return Cache::allocate(kind, alignment, size);
}

// Crashes on failure.
inline void* realloc(void* object, size_t newSize, HeapKind kind = HeapKind::Primary)
{
    return Cache::reallocate(kind, object, newSize);
}

// Returns null for failure
BEXPORT void* tryLargeMemalignVirtual(size_t alignment, size_t size, HeapKind kind = HeapKind::Primary);

inline void free(void* object, HeapKind kind = HeapKind::Primary)
{
    Cache::deallocate(kind, object);
}

BEXPORT void freeOutOfLine(void* object, HeapKind kind = HeapKind::Primary);

BEXPORT void freeLargeVirtual(void* object, HeapKind kind = HeapKind::Primary);

inline void scavengeThisThread()
{
    for (unsigned i = numHeaps; i--;)
        Cache::scavenge(static_cast<HeapKind>(i));
    IsoTLS::scavenge();
}

BEXPORT void scavenge();

BEXPORT bool isEnabled(HeapKind kind = HeapKind::Primary);
    
inline size_t availableMemory()
{
    return bmalloc::availableMemory();
}
    
#if BPLATFORM(IOS)
inline size_t memoryFootprint()
{
    return bmalloc::memoryFootprint();
}

inline double percentAvailableMemoryInUse()
{
    return bmalloc::percentAvailableMemoryInUse();
}
#endif

#if BOS(DARWIN)
BEXPORT void setScavengerThreadQOSClass(qos_class_t overrideClass);
#endif

} // namespace api
} // namespace bmalloc
