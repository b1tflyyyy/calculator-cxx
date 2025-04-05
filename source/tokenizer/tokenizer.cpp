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

#include "tokenizer.hpp"

QString Tokenizer::mIntermediateBuffer{};
Tokenizer::Token Tokenizer::mIntermediateToken{};

std::vector<Tokenizer::TokenPair> Tokenizer::mTokens{};

QString Tokenizer::mErrorMessage{};
bool Tokenizer::mErrorFlag{};

Tokenizer::Tokenizer() : 
    mFiniteStateMachine{ nullptr }
{ }

void Tokenizer::Init(const QString& input)
{
    UT_CC_DEFAULT_LOGGER_INFO(__PRETTY_FUNCTION__);

    auto input_generator{ Tokenizer::InputSequence(input) };
    mFiniteStateMachine.SetInputGenerator(std::move(input_generator));

    mFiniteStateMachine.AddState(Tokenizer::State::Init, Tokenizer::InitState);
    mFiniteStateMachine.AddState(Tokenizer::State::LeftParenthesis, Tokenizer::LeftParenthesis);
    mFiniteStateMachine.AddState(Tokenizer::State::RightParenthesis, Tokenizer::RightParenthesis);
    mFiniteStateMachine.AddState(Tokenizer::State::Unary, Tokenizer::Unary);
    mFiniteStateMachine.AddState(Tokenizer::State::Digit, Tokenizer::Digit);
    mFiniteStateMachine.AddState(Tokenizer::State::FloatingPoint, Tokenizer::FloatingPoint);
    mFiniteStateMachine.AddState(Tokenizer::State::Point, Tokenizer::Point);
    mFiniteStateMachine.AddState(Tokenizer::State::Operator, Tokenizer::Operator);
    mFiniteStateMachine.AddState(Tokenizer::State::Error, Tokenizer::Error);
    mFiniteStateMachine.AddState(Tokenizer::State::End, Tokenizer::End);

    Clear();
}

void Tokenizer::Run()
{
    UT_CC_DEFAULT_LOGGER_INFO(__PRETTY_FUNCTION__);
    mFiniteStateMachine.Run(Tokenizer::State::Init);
}   

const std::vector<Tokenizer::TokenPair>& Tokenizer::GetTokens() const noexcept { return mTokens; }

bool Tokenizer::HasError() const noexcept { return mErrorFlag; }
const QString& Tokenizer::GetErrorMessage() const noexcept { return mErrorMessage; }

Utils::InputGenerator<Tokenizer::Symbol> Tokenizer::InputSequence(const QString& input)
{
    for (const auto& ch : input)
    {
        co_yield ch;
    }
}

Utils::ResumableNoEncapsulation Tokenizer::InitState(FiniteStateMachine& finite_state_machine)
{
    UT_CC_DEFAULT_LOGGER_INFO(__PRETTY_FUNCTION__);

    auto transition_function = [](const auto& data) -> Tokenizer::State
    {
        const auto ch_1b{ data.toLatin1() };

        const bool is_left_parenthesis{ Utils::EqualsAnyOf(ch_1b, '(') };
        const bool is_digit{ static_cast<bool>(std::isdigit(ch_1b)) };

        if (is_left_parenthesis)
        {
            mTokens.emplace_back(data, Tokenizer::Token::LeftParenthesis);
            return Tokenizer::State::LeftParenthesis;
        }
        else if (is_digit)
        {
            mIntermediateToken = Tokenizer::Token::Integer;
            mIntermediateBuffer.push_back(data);

            return Tokenizer::State::Digit;
        }

        mErrorMessage = QStringLiteral("Expression must starts from left parenthesis or digit !!!");
        return Tokenizer::State::Error;
    };

    for (;;)
    {
        co_await finite_state_machine.GetConditionalAwaiter(std::move(transition_function));
    }
}

Utils::ResumableNoEncapsulation Tokenizer::LeftParenthesis(FiniteStateMachine& finite_state_machine)
{
    UT_CC_DEFAULT_LOGGER_INFO(__PRETTY_FUNCTION__);

    auto transition_function = [](const auto& data) -> Tokenizer::State
    {
        const auto ch_1b{ data.toLatin1() };

        const bool is_unary_operator{ Utils::EqualsAnyOf(ch_1b, '-') };
        const bool is_digit{ static_cast<bool>(std::isdigit(ch_1b)) };
        const bool is_left_parenthesis{ Utils::EqualsAnyOf(ch_1b, '(') };

        if (is_unary_operator)
        {
            mTokens.emplace_back(data, Tokenizer::Token::UnaryOperator);
            return Tokenizer::State::Unary;
        }
        else if (is_digit)
        {
            mIntermediateToken = Tokenizer::Token::Integer;
            mIntermediateBuffer.push_back(data);

            return Tokenizer::State::Digit;
        }
        else if (is_left_parenthesis)
        {
            mTokens.emplace_back(data, Tokenizer::Token::LeftParenthesis);
            return Tokenizer::State::LeftParenthesis;
        }

        mErrorMessage = QStringLiteral("After left parenthesis can be only unary operator or a digit !!!");
        return Tokenizer::State::Error;
    };

    for (;;)
    {
        co_await finite_state_machine.GetConditionalAwaiter(std::move(transition_function));
    }
}

Utils::ResumableNoEncapsulation Tokenizer::RightParenthesis(FiniteStateMachine& finite_state_machine)
{
    UT_CC_DEFAULT_LOGGER_INFO(__PRETTY_FUNCTION__);

    auto transition_function = [](const auto& data) -> Tokenizer::State
    {
        const auto ch_1b{ data.toLatin1() };
        
        const bool is_operator{ Utils::EqualsAnyOf(ch_1b, '+', '-', '/', '*', '^') };
        const bool is_right_parenthesis{ Utils::EqualsAnyOf(ch_1b, ')') };

        if (is_operator)
        {
            mTokens.emplace_back(data, Tokenizer::Token::Operator);
            return Tokenizer::State::Operator;
        }
        else if (is_right_parenthesis)
        {
            mTokens.emplace_back(data, Tokenizer::Token::RightParenthesis);
            return Tokenizer::State::RightParenthesis;
        }

        mErrorMessage = QStringLiteral("After right parenthesis can be only operator !!!");
        return Tokenizer::State::Error;
    };

    for (;;)
    {
        co_await finite_state_machine.GetConditionalAwaiter(std::move(transition_function));
    }
}

Utils::ResumableNoEncapsulation Tokenizer::Unary(FiniteStateMachine& finite_state_machine)
{
    UT_CC_DEFAULT_LOGGER_INFO(__PRETTY_FUNCTION__);

    auto transition_function = [](const auto& data) -> Tokenizer::State
    {
        const auto ch_1b{ data.toLatin1() };
        const bool is_digit{ static_cast<bool>(std::isdigit(ch_1b)) };
        
        if (is_digit)
        {
            mIntermediateToken = Tokenizer::Token::Integer;
            mIntermediateBuffer.push_back(data);

            return Tokenizer::State::Digit;
        }

        mErrorMessage = QStringLiteral("After unary operator can be only digit !!!");
        return Tokenizer::State::Error;
    };

    for (;;)
    {
        co_await finite_state_machine.GetConditionalAwaiter(std::move(transition_function));
    }
}

Utils::ResumableNoEncapsulation Tokenizer::Digit(FiniteStateMachine& finite_state_machine)
{
    UT_CC_DEFAULT_LOGGER_INFO(__PRETTY_FUNCTION__);

    auto transition_function = [](const auto& data) -> Tokenizer::State 
    {
        const auto ch_1b{ data.toLatin1() };

        const bool is_digit{ static_cast<bool>(std::isdigit(ch_1b)) };
        const bool is_point{ Utils::EqualsAnyOf(ch_1b, '.') };
        const bool is_operator{ Utils::EqualsAnyOf(ch_1b, '+', '-', '/', '*', '^') };
        const bool is_right_parenthesis{ Utils::EqualsAnyOf(ch_1b, ')') };

        if (is_digit)
        {
            mIntermediateBuffer.push_back(data);
            return Tokenizer::State::Digit;
        }
        else if (is_point)
        {
            mIntermediateToken = Tokenizer::Token::FloatingPoint;
            mIntermediateBuffer.push_back(data);

            return Tokenizer::State::Point;
        }
        else if (is_operator)
        {
            mTokens.emplace_back(mIntermediateBuffer, mIntermediateToken);
            mIntermediateBuffer.clear();
            
            mTokens.emplace_back(data, Tokenizer::Token::Operator);
            return Tokenizer::State::Operator;
        }
        else if (is_right_parenthesis)
        {
            mTokens.emplace_back(mIntermediateBuffer, mIntermediateToken);
            mIntermediateBuffer.clear();

            mTokens.emplace_back(data, Tokenizer::Token::RightParenthesis);
            return Tokenizer::State::RightParenthesis;
        }

        mErrorMessage = QStringLiteral("After digit can be only point or operator !!!");
        return Tokenizer::State::Error;
    };

    for (;;)
    {
        co_await finite_state_machine.GetConditionalAwaiter(std::move(transition_function));
    }
}

Utils::ResumableNoEncapsulation Tokenizer::FloatingPoint(FiniteStateMachine& finite_state_machine)
{
    UT_CC_DEFAULT_LOGGER_INFO(__PRETTY_FUNCTION__);

    auto transition_function = [](const auto& data) -> Tokenizer::State
    {
        const auto ch_1b{ data.toLatin1() };
        
        const bool is_digit{ static_cast<bool>(std::isdigit(ch_1b)) };
        const bool is_right_parenthesis{ Utils::EqualsAnyOf(ch_1b, ')') };
        const bool is_operator{ Utils::EqualsAnyOf(ch_1b, '+', '-', '/', '*', '^') };
    
        if (is_digit)
        {
            mIntermediateBuffer.push_back(data);
            return Tokenizer::State::FloatingPoint;
        }
        else if (is_right_parenthesis)
        {
            mTokens.emplace_back(mIntermediateBuffer, mIntermediateToken);
            mIntermediateBuffer.clear();
        
            mTokens.emplace_back(data, Tokenizer::Token::RightParenthesis);
            return Tokenizer::State::RightParenthesis;
        }
        else if (is_operator)
        {
            mTokens.emplace_back(mIntermediateBuffer, mIntermediateToken);
            mIntermediateBuffer.clear();
        
            mTokens.emplace_back(data, Tokenizer::Token::Operator);
            return Tokenizer::State::Operator;            
        }

        mErrorMessage = QStringLiteral("After floating point can be only digit, right parenthesis or operator !!!");
        return Tokenizer::State::Error;
    };

    for (;;)
    {
        co_await finite_state_machine.GetConditionalAwaiter(std::move(transition_function));
    }
}

Utils::ResumableNoEncapsulation Tokenizer::Point(FiniteStateMachine& finite_state_machine)
{
    UT_CC_DEFAULT_LOGGER_INFO(__PRETTY_FUNCTION__);

    auto transition_function = [](const auto& data) -> Tokenizer::State
    {
        const auto ch_1b{ data.toLatin1() };
        const bool is_digit{ static_cast<bool>(std::isdigit(ch_1b)) };

        if (is_digit) 
        {
            mIntermediateBuffer.push_back(data); 
            return Tokenizer::State::FloatingPoint; 
        }

        mErrorMessage = QStringLiteral("After point can be only digit");
        return Tokenizer::State::Error;
    };

    for (;;)
    {
        co_await finite_state_machine.GetConditionalAwaiter(std::move(transition_function));
    }
}

Utils::ResumableNoEncapsulation Tokenizer::Operator(FiniteStateMachine& finite_state_machine)
{
    UT_CC_DEFAULT_LOGGER_INFO(__PRETTY_FUNCTION__);

    auto transition_function = [](const auto& data) -> Tokenizer::State
    {
        const auto ch_1b{ data.toLatin1() };

        const bool is_left_parenthesis{ Utils::EqualsAnyOf(ch_1b, '(') };
        const bool is_digit{ static_cast<bool>(std::isdigit(ch_1b)) };

        if (is_left_parenthesis)
        {
            mTokens.emplace_back(data, Tokenizer::Token::LeftParenthesis);
            return Tokenizer::State::LeftParenthesis;
        }
        else if (is_digit)
        {
            mIntermediateToken = Tokenizer::Token::Integer;
            mIntermediateBuffer.push_back(data);

            return Tokenizer::State::Digit;
        }

        mErrorMessage = QStringLiteral("After operator can be only digit or left parenthesis");
        return Tokenizer::State::Error;
    };

    for (;;)
    {
        co_await finite_state_machine.GetConditionalAwaiter(std::move(transition_function));
    }
}

Utils::ResumableNoEncapsulation Tokenizer::Error([[maybe_unused]] FiniteStateMachine& finite_state_machine)
{
    UT_CC_DEFAULT_LOGGER_INFO(__PRETTY_FUNCTION__);
    UT_CC_DEFAULT_LOGGER_COLOR_WARN(Tc::black, Tc::yellow, Emp::bold, 
        "Tokenization error: {}", mErrorMessage.toStdString()
    );

    mErrorFlag = true;
    co_return;
}

Utils::ResumableNoEncapsulation Tokenizer::End(FiniteStateMachine& finite_state_machine)
{
    UT_CC_DEFAULT_LOGGER_INFO(__PRETTY_FUNCTION__);

    const auto previous_state{ finite_state_machine.GetPreviousState() };
    if (!Utils::EqualsAnyOf(previous_state, Tokenizer::State::Digit, Tokenizer::State::FloatingPoint, Tokenizer::State::RightParenthesis))
    {
        auto error_func = []() -> Tokenizer::State 
        {
            mErrorMessage = QStringLiteral("Expression should ends only on digit or right parenthesis");
            return Tokenizer::State::Error;
        };
        
        co_await finite_state_machine.GetUnconditionalAwaiter(std::move(error_func));
    }

    if (!mIntermediateBuffer.isEmpty())
    {
        mTokens.emplace_back(mIntermediateBuffer, mIntermediateToken);
    }

    co_return;
}

inline void Tokenizer::Clear()
{
    mErrorFlag = false;
    mErrorMessage.clear();

    mIntermediateBuffer.clear();
    mIntermediateToken = Tokenizer::Token::Integer;

    mTokens.clear();
}
