/*
 * Copyright (C) 2017 Apple Inc. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "BasicCredential.h"
#include "ExceptionOr.h"
#include <runtime/ArrayBuffer.h>
#include <wtf/Forward.h>

namespace WebCore {

class AuthenticatorResponse;
class DeferredPromise;

struct CredentialCreationOptions;
struct CredentialRequestOptions;

class PublicKeyCredential final : public BasicCredential {
public:
    static Ref<PublicKeyCredential> create(const String& id)
    {
        return adoptRef(*new PublicKeyCredential(id));
    }

    static Vector<Ref<BasicCredential>> collectFromCredentialStore(CredentialRequestOptions&&, bool);
    static ExceptionOr<RefPtr<BasicCredential>> discoverFromExternalSource(const CredentialRequestOptions&, bool);
    static RefPtr<BasicCredential> store(RefPtr<BasicCredential>&&, bool);
    static ExceptionOr<RefPtr<BasicCredential>> create(const CredentialCreationOptions&, bool);

    ArrayBuffer* rawId();
    AuthenticatorResponse* response();
    // Not support yet. Always throws.
    ExceptionOr<bool> getClientExtensionResults();

    static void isUserVerifyingPlatformAuthenticatorAvailable(Ref<DeferredPromise>&&);

private:
    PublicKeyCredential(const String&);

    RefPtr<ArrayBuffer> m_rawId;
    RefPtr<AuthenticatorResponse> m_response;
};

} // namespace WebCore
