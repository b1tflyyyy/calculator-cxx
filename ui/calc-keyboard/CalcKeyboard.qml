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

GridLayout {
    id: _grid

    property int buttonRadius: 20
    property int buttonTextSize: 20

    columns: 4
    rows: 6

    columnSpacing: 5
    rowSpacing: 5

    CalcButtonColorHandler {
        id: _calcButtonColorHandler
    }

    Repeater {
        model: CalcButtonModel{}

        CalcButton {
            Layout.fillWidth: true
            Layout.fillHeight: true  

            Layout.row: model.row
            Layout.column: model.col

            colorHandler: _calcButtonColorHandler[model.colorHandlerID]
            radius: _grid.buttonRadius

            buttonText: model.text
            buttonTextSize: _grid.buttonTextSize

            onCalcButtonClicked: function() {
                // TODO: ...
                console.log(model.text)
            }
        }
    }
}
