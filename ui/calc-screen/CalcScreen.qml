// MIT License
// 
// Copyright (c) 2025 @Who
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

import QtQuick 2.15
import QtQuick.Controls

Rectangle {
    id: _calcScreen

    property string currentExpression: ""
    property int expressionTextSize: 10

    signal expressionChanged(isEmpty: bool)

    Flickable {
        id: _flick

        width: parent.width
        height: parent.height

        flickableDirection: Flickable.HorizontalFlick

        interactive: true

        contentHeight: _expressionText.height
        contentWidth: _expressionText.width

        // TODO: fix animation
        Behavior on contentX {
            NumberAnimation {
                duration: 100
            }
        }

        function autoHorizontalScroll() {
            if (_flick.contentWidth < _flick.width) {
                _flick.contentX = 0
            } else {
                _flick.contentX = _flick.contentWidth - _flick.width
            }
        }

        Text {
            id: _expressionText

            anchors {
                left: parent.left
                verticalCenter: parent.verticalCenter
            }

            font {
                pointSize: expressionTextSize
            }

            text: currentExpression
            onTextChanged: function () {
                expressionChanged(_expressionText.text === "")
            }
        }

        Connections {
            target: _expressionText
            function onTextChanged() {
                _flick.autoHorizontalScroll()
            }
        }
    }
}