/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts 1.3

Rectangle {
    id: root
    width: 400
    height: 150
    color: "#00ffffff"
    antialiasing: true

    Material.theme: Material.Light
    Material.accent: Material.Purple

    Text {
        id : t1
        x : 10
        y : 10
        text: "Focal-Length (f): "
        font.family: "Calibri"
        font.pixelSize: 18
        font.italic: false
        font.bold: false
        smooth: false
    }
    Text {
        id : t2
        x : 10
        y : 40
        text: "Height (h): "
        font.family: "Calibri"
        smooth: false
        enabled: true
        font.pixelSize: 18
    }
    Text {
        id : t3
        x : 10
        y : 70
        text: "Distance (d3): "
        font.family: "Calibri"
        font.pixelSize: 18
    }
    Slider {
        id: sl1
        x : 130; y : 7
        width: 150
        height: 30
        //style: touchStyle
        value: 0.5

        Text {
            id: text1
            x: 156
            y: 7
            text: Number(sl1.value * 100).toFixed(1)  + " mm"
            font.family: "Calibri"
            textFormat: Text.PlainText
            font.pixelSize: 16
        }
    }
    Slider {
        id: sl2
        x : 130; y : 39
        width: 150
        height: 30
        //style: touchStyle
        value: 0.5

        Text {
            id: text2
            x: 156
            y: 7
            text: Number(sl2.value * 100).toFixed(1) + " mm"
            font.family: "Calibri"
            textFormat: Text.PlainText
            font.pixelSize: 16
        }
    }
    Slider {
        id: sl3
        x : 130; y : 69
        width: 150
        height: 30
        //style: touchStyle
        value: 0.5

        Text {
            id: text3
            x: 156
            y: 7
            text: Number(sl3.value * 100).toFixed(1) + " mm"
            font.family: "Calibri"
            textFormat: Text.PlainText
            font.pixelSize: 16
        }
    }

    // binding
    Binding
    {
        target: opt
        property: "focallength"
        value:sl1.value
    }
    Binding
    {
        target: opt
        property: "height"
        value:sl2.value
    }
    Binding
    {
        target: opt
        property: "distance3"
        value:sl3.value
    }

    Component { id: touchStyle; SliderStyle {} }




}
