/*
 * Copyright (C) 2011 Apple Inc.  All rights reserved.
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
 *
 * This file handles shared library symbol export decorations. It is recommended
 * that all WebKit projects use these definitions so that symbol exports work
 * properly on all platforms and compilers that WebKit builds under.
 */

#pragma once

#include <wtf/ExportMacros.h>

#if USE(EXPORT_MACROS)

#if defined(BUILDING_JavaScriptCore) || defined(STATICALLY_LINKED_WITH_JavaScriptCore)
#define JS_EXPORT_PRIVATE WTF_EXPORT
#else
#define JS_EXPORT_PRIVATE WTF_IMPORT
#endif

// FIXME: We should replace JS_EXPORTDATA with JS_EXPORT_PRIVATE.
#define JS_EXPORTDATA JS_EXPORT_PRIVATE

#else // !USE(EXPORT_MACROS)

#define JS_EXPORTDATA
#define JS_EXPORT_PRIVATE

#endif // USE(EXPORT_MACROS)
