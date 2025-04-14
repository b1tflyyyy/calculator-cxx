# MIT License
# 
# Copyright (c) 2025 @Who
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required(VERSION 3.22)

# Standard config
# -----------------------------------------------------------------------
project(calculator LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG bin/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE bin/Release)

add_compile_options(-Wall -Wextra)

# Add modules
# -----------------------------------------------------------------------
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Include modules
# -----------------------------------------------------------------------
include(QtAutoGeneration)

# Custom options
# -----------------------------------------------------------------------
option(ENABLE_LOGS "Enable debug logs" ON)

if (ENABLE_LOGS)
    add_compile_definitions(ENABLE_LOGS)
endif()

# Print custom options
# -----------------------------------------------------------------------
message(STATUS "Enable logs: ${ENABLE_LOGS}")

# Sub dirs ...
# -----------------------------------------------------------------------
add_subdirectory(source)
add_subdirectory(third-party)