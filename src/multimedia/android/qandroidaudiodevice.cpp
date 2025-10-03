// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include "qandroidaudiodevice_p.h"

#include "qopenslesengine_p.h"
#include <algorithm>

QT_BEGIN_NAMESPACE

QOpenSLESDeviceInfo::QOpenSLESDeviceInfo(QByteArray device,
                                         QString desc,
                                         QAudioDevice::Mode mode,
                                         bool isDefaultDevice)
    : QAudioDevicePrivate(std::move(device), mode, std::move(desc))
    , m_engine(QOpenSLESEngine::instance())
{
    isDefault = isDefaultDevice;

    auto channels = m_engine->supportedChannelCounts(mode);
    if (channels.size()) {
        minimumChannelCount = channels.first();
        maximumChannelCount = channels.last();
    }

    auto sampleRates = m_engine->supportedSampleRates(mode);
    if (sampleRates.size()) {
        minimumSampleRate = sampleRates.first();
        maximumSampleRate = sampleRates.last();
    }

    supportedSampleFormats = m_engine->supportedSampleFormats(mode);

    preferredFormat.setChannelCount(std::clamp(2, minimumChannelCount, maximumChannelCount));
    preferredFormat.setSampleRate(std::clamp(48000, minimumSampleRate, maximumSampleRate));
    QAudioFormat::SampleFormat f = QAudioFormat::Int16;
    if (!supportedSampleFormats.contains(f))
        f = supportedSampleFormats.value(0, QAudioFormat::Unknown);
    preferredFormat.setSampleFormat(f);
}

QT_END_NAMESPACE
