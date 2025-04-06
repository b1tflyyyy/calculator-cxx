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

/*
    Keyboard -> 6(rows) x 4(cols)
          0    1    2    3
    0 -> ' '; ' '; '('; ')';
    1 -> ' '; AC'; '+,-'; '/';
    2 -> '7'; '8'; '9'; '*'
    3 -> '4'; '5'; '6'; '-'
    4 -> '1'; '2'; '3'; '+'
    5 -> '0'; '^'; '.'; '='
*/

ListModel {
    id: _calcButtonModel

    // 0 row
    ListElement { name: "left_parenthesis";  value: "("; isIcon: false; iconPath: ""; row: 0; col: 2; colorHandlerID: "operatorButtonHandler"; }
    ListElement { name: "right_parenthesis"; value: ")"; isIcon: false; iconPath: ""; row: 0; col: 3; colorHandlerID: "operatorButtonHandler"; }

    // 1 row
    ListElement { name: "all_clear"; value: "AC";  isIcon: false; iconPath: "qrc:/resources/delete.png"; row: 1; col: 1; colorHandlerID: "operatorButtonHandler"; }
    ListElement { name: "sign";      value: "+,-"; isIcon: false; iconPath: "";                          row: 1; col: 2; colorHandlerID: "operatorButtonHandler"; }
    ListElement { name: "division";  value: "/";   isIcon: false; iconPath: "";                          row: 1; col: 3; colorHandlerID: "operatorButtonHandler"; }

    // 2 row
    ListElement { name: "seven";          value: "7"; isIcon: false; iconPath: ""; row: 2; col: 0; colorHandlerID: "numericButtonHandler";  }
    ListElement { name: "eight";          value: "8"; isIcon: false; iconPath: ""; row: 2; col: 1; colorHandlerID: "numericButtonHandler";  }
    ListElement { name: "nine";           value: "9"; isIcon: false; iconPath: ""; row: 2; col: 2; colorHandlerID: "numericButtonHandler";  }
    ListElement { name: "multiplication"; value: "*"; isIcon: false; iconPath: ""; row: 2; col: 3; colorHandlerID: "operatorButtonHandler"; }

    // 3 row
    ListElement { name: "four";        value: "4"; isIcon: false; iconPath: ""; row: 3; col: 0; colorHandlerID: "numericButtonHandler";  }
    ListElement { name: "five";        value: "5"; isIcon: false; iconPath: ""; row: 3; col: 1; colorHandlerID: "numericButtonHandler";  }
    ListElement { name: "six";         value: "6"; isIcon: false; iconPath: ""; row: 3; col: 2; colorHandlerID: "numericButtonHandler";  }
    ListElement { name: "subtraction"; value: "-"; isIcon: false; iconPath: ""; row: 3; col: 3; colorHandlerID: "operatorButtonHandler"; }

    // 4 row
    ListElement { name: "one";      value: "1"; isIcon: false; iconPath: ""; row: 4; col: 0; colorHandlerID: "numericButtonHandler";  }
    ListElement { name: "two";      value: "2"; isIcon: false; iconPath: ""; row: 4; col: 1; colorHandlerID: "numericButtonHandler";  }
    ListElement { name: "three";    value: "3"; isIcon: false; iconPath: ""; row: 4; col: 2; colorHandlerID: "numericButtonHandler";  }
    ListElement { name: "addition"; value: "+"; isIcon: false; iconPath: ""; row: 4; col: 3; colorHandlerID: "operatorButtonHandler"; }    

    // 5 row
    ListElement { name: "zero";  value: "0"; isIcon: false; iconPath: ""; row: 5; col: 0; colorHandlerID: "numericButtonHandler";  }
    ListElement { name: "power"; value: "^"; isIcon: false; iconPath: ""; row: 5; col: 1; colorHandlerID: "numericButtonHandler";  }
    ListElement { name: "point"; value: "."; isIcon: false; iconPath: ""; row: 5; col: 2; colorHandlerID: "numericButtonHandler";  }
    ListElement { name: "equal"; value: "="; isIcon: false; iconPath: ""; row: 5; col: 3; colorHandlerID: "operatorButtonHandler"; }
}