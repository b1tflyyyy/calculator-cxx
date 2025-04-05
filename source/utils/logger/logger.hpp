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

#pragma once 

#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/bundled/color.h>

namespace Utils 
{
    class Logger
    {
    public:
        using Emp = ::fmt::emphasis;
        using Tc = ::fmt::terminal_color;

        Logger() = default;
        ~Logger() noexcept = default;

        static void Init();
        static std::shared_ptr<spdlog::logger>& GetDefaultLogger();

    private:
        static std::shared_ptr<spdlog::logger> mDefaultLogger;
    };
};

#if defined (ENABLE_LOGS)
    #define UT_CC_DEFAULT_LOGGER_INIT()         ::Utils::Logger::Init()
    #define UT_CC_DEFAULT_LOGGER_ERROR(...)     ::Utils::Logger::GetDefaultLogger()->error(__VA_ARGS__)
    #define UT_CC_DEFAULT_LOGGER_WARN(...)      ::Utils::Logger::GetDefaultLogger()->warn(__VA_ARGS__)
    #define UT_CC_DEFAULT_LOGGER_CRITICAL(...)  ::Utils::Logger::GetDefaultLogger()->critical(__VA_ARGS__)
    #define UT_CC_DEFAULT_LOGGER_INFO(...)      ::Utils::Logger::GetDefaultLogger()->info(__VA_ARGS__)

    #define UT_CC_DEFAULT_LOGGER_COLOR_ERROR(background_color, foreground_color, text_style, ...) \
    ::Utils::Logger::GetDefaultLogger()->error(fmt::format(\
        ::fmt::bg(background_color) |                      \
        ::fmt::fg(foreground_color) |                      \
        ::fmt::emphasis(text_style),                       \
        __VA_ARGS__                                        \
    ))
    #define UT_CC_DEFAULT_LOGGER_COLOR_WARN(background_color, foreground_color, text_style, ...) \
    ::Utils::Logger::GetDefaultLogger()->warn(fmt::format(\
        ::fmt::bg(background_color) |                     \
        ::fmt::fg(foreground_color) |                     \
        ::fmt::emphasis(text_style),                      \
        __VA_ARGS__                                       \
    ))

    #define UT_CC_DEFAULT_LOGGER_COLOR_CRITICAL(background_color, foreground_color, text_style, ...) \
    ::Utils::Logger::GetDefaultLogger()->critical(fmt::format(\
        ::fmt::bg(background_color) |                         \
        ::fmt::fg(foreground_color) |                         \
        ::fmt::emphasis(text_style),                          \
        __VA_ARGS__                                           \
    ))

    #define UT_CC_DEFAULT_LOGGER_COLOR_INFO(background_color, foreground_color, text_style, ...) \
    ::Utils::Logger::GetDefaultLogger()->info(fmt::format(\
        ::fmt::bg(background_color) |                     \
        ::fmt::fg(foreground_color) |                     \
        ::fmt::emphasis(text_style),                      \
        __VA_ARGS__                                       \
    ))
#else 
    #define UT_CC_DEFAULT_LOGGER_INIT()         
    #define UT_CC_DEFAULT_LOGGER_ERROR(...)     
    #define UT_CC_DEFAULT_LOGGER_WARN(...)      
    #define UT_CC_DEFAULT_LOGGER_CRITICAL(...)  
    #define UT_CC_DEFAULT_LOGGER_INFO(...)      
    #define UT_CC_DEFAULT_LOGGER_COLOR_ERROR(...)
    #define UT_CC_DEFAULT_LOGGER_COLOR_WARN(...)
    #define UT_CC_DEFAULT_LOGGER_COLOR_CRITICAL(...)
    #define UT_CC_DEFAULT_LOGGER_COLOR_INFO(...)
#endif