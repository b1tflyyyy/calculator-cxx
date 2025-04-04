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

#include <unordered_map>

#include "input-generator.hpp"

#include "custom-awaiters/conditional-awaiter.hpp"
#include "custom-awaiters/unconditional-awaiter.hpp"

namespace Utils 
{
    using CoroutineHandle = std::coroutine_handle<>;

    template <typename TState, typename TData>
    class FiniteStateMachine
    {
    public:
        using InputGenerator = InputGenerator<TData>;

        explicit FiniteStateMachine(std::nullptr_t) :
            mInputGenerator{ nullptr }
        { }

        FiniteStateMachine(InputGenerator&& input_generator) : 
            mInputGenerator{ std::move(input_generator) }
        { }

        ~FiniteStateMachine() noexcept = default;

        void SetInputGenerator(InputGenerator&& input_generator)
        {
            mInputGenerator = std::move(input_generator);
        }

        void Run(TState initial_state)
        {
            mCurrentState = initial_state;
            mStates[initial_state].resume();
        }

        template <typename TStateGenerator>
        void AddState(TState state, TStateGenerator state_handler)
        {
            mStates[state] = state_handler(*this).GetInternalHandle();
        }

        [[nodiscard]] CoroutineHandle operator[](TState state) 
        {   
            mCurrentState = state;
            return mStates[state]; 
        }
        
        [[nodiscard]] auto GetCurrentState() const noexcept { return mCurrentState; }
        [[nodiscard]] auto GetPreviousState() const noexcept { return mPreviousState; }
        [[nodiscard]] auto GetData() const noexcept { return mInputGenerator.GetValue(); }

        template <typename TTransitionFunction>
        [[nodiscard]] auto GetConditionalAwaiter(TTransitionFunction&& transition_function)
        {
            return ConditionalAwaiter<TTransitionFunction, TState, decltype(*this)>{ std::move(transition_function), *this };
        }

        template <typename TTransitionFunction>
        [[nodiscard]] auto GetUnconditionalAwaiter(TTransitionFunction&& transition_function)
        {
            return UnconditionalAwaiter<TTransitionFunction, TState, decltype(*this)>{ std::move(transition_function), *this };
        }

        [[nodiscard]] bool GoNext()
        {
            mPreviousState = mCurrentState;
            return mInputGenerator.Next();
        }

    private:
        TState mCurrentState;
        TState mPreviousState;

        InputGenerator mInputGenerator;
        std::unordered_map<TState, CoroutineHandle> mStates;
    };
}