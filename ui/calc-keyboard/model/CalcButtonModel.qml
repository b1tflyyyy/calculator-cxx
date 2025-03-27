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
    ListElement { text: "("; row: 0; col: 2; colorHandlerID: "operatorButtonHandler"; }
    ListElement { text: ")"; row: 0; col: 3; colorHandlerID: "operatorButtonHandler"; }

    // 1 row
    ListElement { text: "AC";  row: 1; col: 1; colorHandlerID: "operatorButtonHandler"; }
    ListElement { text: "+,-"; row: 1; col: 2; colorHandlerID: "operatorButtonHandler"; }
    ListElement { text: "/";   row: 1; col: 3; colorHandlerID: "operatorButtonHandler"; }

    // 2 row
    ListElement { text: "7"; row: 2; col: 0; colorHandlerID: "numericButtonHandler";  }
    ListElement { text: "8"; row: 2; col: 1; colorHandlerID: "numericButtonHandler";  }
    ListElement { text: "9"; row: 2; col: 2; colorHandlerID: "numericButtonHandler";  }
    ListElement { text: "*"; row: 2; col: 3; colorHandlerID: "operatorButtonHandler"; }

    // 3 row
    ListElement { text: "4"; row: 3; col: 0; colorHandlerID: "numericButtonHandler";  }
    ListElement { text: "5"; row: 3; col: 1; colorHandlerID: "numericButtonHandler";  }
    ListElement { text: "6"; row: 3; col: 2; colorHandlerID: "numericButtonHandler";  }
    ListElement { text: "-"; row: 3; col: 3; colorHandlerID: "operatorButtonHandler"; }

    // 4 row
    ListElement { text: "1"; row: 4; col: 0; colorHandlerID: "numericButtonHandler";  }
    ListElement { text: "2"; row: 4; col: 1; colorHandlerID: "numericButtonHandler";  }
    ListElement { text: "3"; row: 4; col: 2; colorHandlerID: "numericButtonHandler";  }
    ListElement { text: "+"; row: 4; col: 3; colorHandlerID: "operatorButtonHandler"; }    

    // 5 row
    ListElement { text: "0"; row: 5; col: 0; colorHandlerID: "numericButtonHandler";  }
    ListElement { text: "^"; row: 5; col: 1; colorHandlerID: "numericButtonHandler";  }
    ListElement { text: "."; row: 5; col: 2; colorHandlerID: "numericButtonHandler";  }
    ListElement { text: "="; row: 5; col: 3; colorHandlerID: "operatorButtonHandler"; }
}