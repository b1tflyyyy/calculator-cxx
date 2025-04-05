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
    The UnconditionalAwaiter class doesn't check availability of character from InputGenerator.
    Just moves to the specified state.
*/

#pragma once 

#include <utility>
#include <coroutine>

namespace Utils 
{
    using CoroutineHandle = std::coroutine_handle<>;

    template <typename TTransitionFunction, typename TState, typename TFiniteStateMachine>
    class UnconditionalAwaiter : public TTransitionFunction
    {
    public: 
        UnconditionalAwaiter(TTransitionFunction&& transition_function, TFiniteStateMachine& finite_state_machine) :
            TTransitionFunction{ std::move(transition_function) }, mFiniteStateMachine{ finite_state_machine }
        { }

        ~UnconditionalAwaiter() noexcept = default;

        bool await_ready() const noexcept { return false; }
        bool await_resume() const noexcept { return false; }

        CoroutineHandle await_suspend(CoroutineHandle) noexcept 
        { 
            return mFiniteStateMachine[TTransitionFunction::operator()()]; 
        }

    private:
        TFiniteStateMachine& mFiniteStateMachine;
    };
}