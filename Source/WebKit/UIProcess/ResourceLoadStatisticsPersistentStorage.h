/*
 * Copyright (C) 2017-2018 Apple Inc. All rights reserved.
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

#include <wtf/Forward.h>
#include <wtf/MonotonicTime.h>
#include <wtf/RunLoop.h>
#include <wtf/WallTime.h>
#include <wtf/text/WTFString.h>

namespace WebCore {
class FileMonitor;
}

namespace WebKit {

class WebResourceLoadStatisticsStore;

class ResourceLoadStatisticsPersistentStorage {
public:
    enum class IsReadOnly { No, Yes };
    ResourceLoadStatisticsPersistentStorage(WebResourceLoadStatisticsStore&, const String& storageDirectoryPath, IsReadOnly);
    ~ResourceLoadStatisticsPersistentStorage();

    void initialize();
    void clear();

    void finishAllPendingWorkSynchronously();

    void ref();
    void deref();

    enum class ForceImmediateWrite {
        No,
        Yes,
    };
    void scheduleOrWriteMemoryStore(ForceImmediateWrite);

private:
    String storageDirectoryPath() const;
    String resourceLogFilePath() const;

    void startMonitoringDisk();
    void stopMonitoringDisk();
    void monitorDirectoryForNewStatistics();

    void writeMemoryStoreToDisk();
    void populateMemoryStoreFromDisk();
    void excludeFromBackup() const;
    void refreshMemoryStoreFromDisk();
    void asyncWriteTimerFired();

    WebResourceLoadStatisticsStore& m_memoryStore;
    const String m_storageDirectoryPath;
    RunLoop::Timer<ResourceLoadStatisticsPersistentStorage> m_asyncWriteTimer;
    std::unique_ptr<WebCore::FileMonitor> m_fileMonitor;
    WallTime m_lastStatisticsFileSyncTime;
    MonotonicTime m_lastStatisticsWriteTime;
    IsReadOnly m_isReadOnly { IsReadOnly::No };
    bool m_hasPendingWrite { false };
};

}
