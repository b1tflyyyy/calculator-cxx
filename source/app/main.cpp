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

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>

#include <logger.hpp>
#include <qml-hash-map.hpp>

#include <math-evaluator-controller.hpp>

int main(int argc, char** argv)
{
    UT_CC_DEFAULT_LOGGER_INIT();
    
    UT_CC_DEFAULT_LOGGER_INFO(__PRETTY_FUNCTION__);
    UT_CC_DEFAULT_LOGGER_INFO("---- Initializing application ...");

    QGuiApplication gui_application{ argc, argv };
    QQmlApplicationEngine application_engine{};

    MathEvaluatorController math_evaluator_controller{};

    auto* ctx{ application_engine.rootContext() };
    ctx->setContextProperty(QStringLiteral("mathEvaluatorController"), &math_evaluator_controller);

    qmlRegisterType<Utils::QmlHashMap>("QmlHashMap", 1, 0, "HashMap");
    
    UT_CC_DEFAULT_LOGGER_INFO("---- Application engine loading MainWindow.qml ...");
    
    const QUrl url{ QStringLiteral("qrc:/main-window/MainWindow.qml") };
    application_engine.load(url);

    return QGuiApplication::exec();
}