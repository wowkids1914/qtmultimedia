// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick
import QtMultimedia
import QtTest

TestCase {
    name: "SoundEffect"

    SoundEffect {
        id: effect
    }

    function test_playing_returnsFalse_byDefault() {
        verify(!effect.playing)
    }

}
