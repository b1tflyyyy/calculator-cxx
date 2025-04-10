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
import QtQuick.Layouts

import "model"
import "calc-button"
import "calc-button/handlers"

import QmlHashMap 1.0

GridLayout {
    id: _grid

    property int buttonRadius: 20
    property int buttonTextSize: 20

    signal buttonClicked(name: string, value: string)

    columns: 4
    rows: 6

    columnSpacing: 5
    rowSpacing: 5

    CalcButtonColorHandler {
        id: _calcButtonColorHandler
    }

    HashMap {
        id: _buttonHashMap
    }

    Repeater {
        model: CalcButtonModel{}

        CalcButton {
            id: _button

            Layout.fillWidth: true
            Layout.fillHeight: true  

            Layout.row: model.row
            Layout.column: model.col

            colorHandler: _calcButtonColorHandler[model.colorHandlerID]
            radius: _grid.buttonRadius

            buttonText: model.value
            buttonTextSize: _grid.buttonTextSize

            showIcon: false
            iconPath: model.iconPath

            onCalcButtonClicked: function() {
                buttonClicked(model.name, model.value)                
            }

            Component.onCompleted: function() {
                _buttonHashMap.Insert(model.name, this)
            }
        }
    }

    function showAllClear(showIcon: bool) {
        let button = _buttonHashMap.Get("all_clear")
        button.showIcon = !showIcon
    }
}
