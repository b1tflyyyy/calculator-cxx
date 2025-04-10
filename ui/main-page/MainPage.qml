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

import "../calc-keyboard"
import "../calc-screen"

Rectangle {
    id: _mainPage

    anchors {
        fill: parent 
    }

    CalcScreen {
        id: _calcScreen

        anchors {
            top: parent.top
            left: parent.left
        }

        height: parent.height * 0.30
        width: parent.width

        color: "transparent"
    
        expressionTextSize: 48

        onExpressionChanged: function (expression) {
            _calcKeyboard.showAllClear(expression === "") // show AC if expression is empty
        }
    }

    CalcKeyboard {
        id: _calcKeyboard

        anchors {
            top: _calcScreen.bottom
        }

        height: parent.height * 0.70
        width: parent.width

        onButtonClicked: function (name, value) {
            if (name === "all_clear") {
                if (_calcScreen.currentExpression !== "") {
                    _calcScreen.deleteLastCharacter()
                } else {
                    _calcScreen.currentExpression = ""
                }
            } else {
                _calcScreen.addCharacter(value)
            }
        }
    }
}