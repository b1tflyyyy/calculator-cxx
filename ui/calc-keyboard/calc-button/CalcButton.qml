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
    id: _buttonContainer

    property string buttonText: ""
    property int buttonTextSize: 10

    property bool isIcon: false
    property string iconPath: ""

    // signature of handler -> function(containsMouse) { return "color" }
    property var colorHandler: null

    signal calcButtonClicked()

    function dynamicPointSize() {
        if (_buttonContainer.width <= 0 || _buttonContainer.height <= 0) {
            return _buttonContainer.buttonTextSize;
        }

        return Math.min(_buttonContainer.width, _buttonContainer.height) * 0.3
    }

    color: colorHandler(_buttonMouseArea.containsMouse)
    
    Behavior on color {
        ColorAnimation {
            duration: 100
        }
    }

    Loader {
        id: _loader

        anchors {
            centerIn: _buttonContainer 
        }

        sourceComponent: isIcon ? _iconComponent : _textComponent
    }

    Component { 
        id: _textComponent

        Text {
            id: _buttonText

            font {
                pointSize: dynamicPointSize()
            }

            OpacityAnimator on opacity {
                from: 0
                to: 1

                duration: 300
            }

            text: _buttonContainer.buttonText
        }
    }

    Component {
        id: _iconComponent 

        Image {
            id: _icon

            OpacityAnimator on opacity {
                from: 0
                to: 1

                duration: 300
            }

            height: _buttonContainer.height * 0.50
            width: _buttonContainer.width * 0.50

            fillMode: Image.PreserveAspectFit
            source: _buttonContainer.iconPath
        }
    }

    MouseArea {
        id: _buttonMouseArea

        anchors {
            fill: parent
        }

        onClicked: function() {
            calcButtonClicked()
        }
    }
}