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

#include <cstdint>
#include <vector>

#include <QString>

#include <finite-state-machine.hpp>
#include <resumable-no-encapsulation.hpp>

#include <logger.hpp>
#include <custom-predicates.hpp>

class Tokenizer
{
public:
    enum class State : std::int16_t
    {
        Init,
        LeftParenthesis,
        RightParenthesis,
        Unary,
        Digit,
        FloatingPoint,
        Point, 
        Operator,
        Error,
        End
    };

    enum class Token : std::int16_t
    {
        Integer,
        FloatingPoint,
        LeftParenthesis,
        RightParenthesis,
        UnaryOperator,
        Operator,
    };
    
    using Symbol = QChar;
    using TokenPair = std::pair<QString, Token>;
    using FiniteStateMachine = Utils::FiniteStateMachine<State, Symbol>;

public:
    Tokenizer();
    ~Tokenizer() noexcept = default;

    void Init(const QString& input);
    void Run();

    [[nodiscard]] const std::vector<TokenPair>& GetTokens() const noexcept;
    
    [[nodiscard]] bool HasError() const noexcept;
    [[nodiscard]] const QString& GetErrorMessage() const noexcept;

private:
    static Utils::InputGenerator<Symbol> InputSequence(const QString& input);

    static Utils::ResumableNoEncapsulation InitState(FiniteStateMachine& finite_state_machine);
    static Utils::ResumableNoEncapsulation LeftParenthesis(FiniteStateMachine& finite_state_machine);
    static Utils::ResumableNoEncapsulation RightParenthesis(FiniteStateMachine& finite_state_machine);
    static Utils::ResumableNoEncapsulation Unary(FiniteStateMachine& finite_state_machine);
    static Utils::ResumableNoEncapsulation Digit(FiniteStateMachine& finite_state_machine);
    static Utils::ResumableNoEncapsulation FloatingPoint(FiniteStateMachine& finite_state_machine);
    static Utils::ResumableNoEncapsulation Point(FiniteStateMachine& finite_state_machine);
    static Utils::ResumableNoEncapsulation Operator(FiniteStateMachine& finite_state_machine);
    static Utils::ResumableNoEncapsulation Error(FiniteStateMachine& finite_state_machine);
    static Utils::ResumableNoEncapsulation End(FiniteStateMachine& finite_state_machine);

    static inline void Clear();

private:
    static QString mIntermediateBuffer;
    static Token mIntermediateToken;
    
    static std::vector<TokenPair> mTokens;

    static QString mErrorMessage;
    static bool mErrorFlag; 
    
    FiniteStateMachine mFiniteStateMachine;
};