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

    signal expressionChanged(expression: string)

    function deleteLastCharacter() {
        let trimmedText = currentExpression.slice(0, -1)
        _textMetrics.text = trimmedText

        if (_textMetrics.advanceWidth > _flick.width) {
            _deletingCharacterAnimation.to = _textMetrics.advanceWidth - _flick.width 
            _deletingCharacterAnimation.start()
        } else {
            currentExpression = trimmedText // delete the last character without animation
        }
    }

    function addCharacter(character: string) {
        currentExpression += character
        
        if (_flick.contentWidth > _flick.width) {
            _addingCharacterAnimation.to = _flick.contentWidth - _flick.width 
            _addingCharacterAnimation.start()
        }
    }

    function isDigit(character: string): bool {
        return character >= "0" && character <= "9"
    }

    function changeSign() {
        let i = currentExpression.length - 1
        
        // Get the starting position of the last number entered
        // expression: 2 + 2
        // idx:        0 1 2
        // result:       1
        while (i >= 0 && (isDigit(currentExpression[i]) || 
                          currentExpression[i] === "."  || 
                          currentExpression[i] === ")")) {
            i--
        }

        
        if (i === -1) { // if it is a positive number at the beginning
            let expr = currentExpression.slice(0, currentExpression.length)
            currentExpression = "(-" + expr + ")"
        } else {
            let expr = currentExpression.slice(i + 1, currentExpression.length) // whose expression sign is to be changed

            // if it is negative
            if (currentExpression.charAt(i) === "-" && currentExpression.charAt(i - 1) === "(") {
                let forward_part = currentExpression.slice(0, i - 1)
                currentExpression = forward_part + expr.slice(0, -1) // expr.slice(0, -1) remove extra right parenthesis at the end
            } else { // if it is positive
                let forward_part = currentExpression.slice(0, i + 1)
                currentExpression = forward_part + "(-" + expr + ")"
            }
        }
    }

    TextMetrics {
        id: _textMetrics

        font: _expressionText.font
        text: ""
    }

    Flickable {
        id: _flick

        property int animationDuration: 100

        width: parent.width
        height: parent.height

        flickableDirection: Flickable.HorizontalFlick

        interactive: true

        contentWidth: _expressionText.width
        contentHeight: _expressionText.height

        PropertyAnimation {
            id: _addingCharacterAnimation
            target: _flick  
            property: "contentX"
            duration: _flick.animationDuration
        }

        PropertyAnimation {
            id: _deletingCharacterAnimation
            target: _flick
            property: "contentX"
            duration: _flick.animationDuration
            onStopped: function () { // remove the last character after animation
                currentExpression = currentExpression.slice(0, -1)
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
                expressionChanged(_expressionText.text)
            }
        }
    }
}