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

/*
    Coroutine resumable no encapsulation generator.
    Used for states inside FSM(Finite-State Machine).

    Has access to coroutine handle. 
*/

#include <coroutine>
#include <exception>

namespace Utils
{
    class ResumableNoEncapsulation
    {
    public: 
        struct promise_type
        {
            using CoroutineHandle = std::coroutine_handle<promise_type>;

            promise_type() = default;
            ~promise_type() noexcept = default;

            std::suspend_always initial_suspend() noexcept { return {}; }
            std::suspend_always final_suspend() noexcept { return {}; }

            void return_void() { }
            void unhandled_exception() { std::rethrow_exception(std::current_exception()); }

            ResumableNoEncapsulation get_return_object() { return CoroutineHandle::from_promise(*this); }
        };

        ResumableNoEncapsulation(promise_type::CoroutineHandle handle) :
            mHandle{ handle }
        { }

        ~ResumableNoEncapsulation() noexcept
        {
            if (mHandle)
            {
                mHandle.destroy();
            }
        }

        ResumableNoEncapsulation(const ResumableNoEncapsulation&) = delete;
        ResumableNoEncapsulation& operator=(const ResumableNoEncapsulation&) = delete;

        ResumableNoEncapsulation(ResumableNoEncapsulation&& other) noexcept :
            mHandle{ other.mHandle }
        {
            other.mHandle = nullptr;
        }

        ResumableNoEncapsulation& operator=(ResumableNoEncapsulation&& other) noexcept
        {
            if (this != &other)
            {
                mHandle = other.mHandle;
                other.mHandle = nullptr;
            }

            return *this;
        }

        [[nodiscard]] bool Resume()
        {
            if (mHandle && !mHandle.done())
            {
                mHandle.resume();
            }

            return !mHandle.done();
        }

        [[nodiscard]] promise_type::CoroutineHandle GetInternalHandle()
        {
            auto tmp_handle{ mHandle };
            mHandle = nullptr;

            return tmp_handle;
        }

    private:
        promise_type::CoroutineHandle mHandle;
    };
}