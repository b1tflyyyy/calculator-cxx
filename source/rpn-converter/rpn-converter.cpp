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

#include "rpn-converter.hpp"

std::vector<Tokenizer::TokenPair> RPNConverter::Convert(const std::vector<Tokenizer::TokenPair>& input)
{
    UT_CC_DEFAULT_LOGGER_INFO(__PRETTY_FUNCTION__);
    mErrorMessage.clear();

    if (std::empty(input))
    {
        mErrorMessage = QStringLiteral("Input is empty");
        return {};
    }

    std::stack<std::pair<QString, Tokenizer::Token>> stack{};
    
    std::vector<Tokenizer::TokenPair> output{};
    output.reserve(static_cast<qsizetype>(std::size(input)));

    for (const auto& [lexeme, token] : input)
    {
        switch (token) 
        {
        case Tokenizer::Token::Integer: 
        case Tokenizer::Token::FloatingPoint: 
        case Tokenizer::Token::UnaryOperator:
        {
            UT_CC_DEFAULT_LOGGER_INFO("---- case: int, float, unary| lexeme: {} |", lexeme.toStdString());

            output.push_back({lexeme, token});
            break;
        }
        
        case Tokenizer::Token::Operator:
        {
            UT_CC_DEFAULT_LOGGER_INFO("---- case: operator| lexeme: {} |", lexeme.toStdString());
            
            const auto curr_priority{ GetOperatorPriority(lexeme) };   
            while (!std::empty(stack) && GetOperatorPriority(stack.top().first) >= curr_priority)
            {
                output.push_back(stack.top());
                stack.pop();         
            }
            
            stack.push({lexeme, token});
            break;
        }

        case Tokenizer::Token::LeftParenthesis:
        {
            UT_CC_DEFAULT_LOGGER_INFO("---- case: left parenthesis| lexeme: {} |", lexeme.toStdString());

            stack.push({lexeme, token});
            break;
        }

        case Tokenizer::Token::RightParenthesis:
        {
            UT_CC_DEFAULT_LOGGER_INFO("---- case: right parenthesis| lexeme: {} |", lexeme.toStdString());

            if (std::empty(stack))
            {
                mErrorMessage = QStringLiteral("extra right parenthesis");
                return {};
            }

            while (stack.top().second != Tokenizer::Token::LeftParenthesis)
            {
                output.push_back(stack.top());
                stack.pop();

                if (std::empty(stack))
                {
                    mErrorMessage = QStringLiteral("left parenthesis missing");
                    return {};
                }
            }

            stack.pop();
            break;
        }
        }
    }

    UT_CC_DEFAULT_LOGGER_INFO("end of input tokens");
    while (!std::empty(stack))
    {
        const auto& [lexeme, token]{ stack.top() };
        if (token == Tokenizer::Token::LeftParenthesis)
        {
            mErrorMessage = QStringLiteral("left parenthesis missing");
            return {};
        }

        output.push_back({lexeme, token});
        stack.pop();
    }

    return output;
}

bool RPNConverter::HasError() const noexcept
{
    return !mErrorMessage.isEmpty();
}

const QString& RPNConverter::GetErrorMessage() const noexcept
{
    return mErrorMessage;
}

inline std::int32_t RPNConverter::GetOperatorPriority(const QString& op) noexcept
{
    if (Utils::EqualsAnyOf(op, QStringLiteral("+"), QStringLiteral("-")))
    {
        return 1;
    }
    
    if (Utils::EqualsAnyOf(op, QStringLiteral("*"), QStringLiteral("/")))
    {
        return 2;
    }

    if (Utils::EqualsAnyOf(op, QStringLiteral("^")))
    {
        return 3;
    }

    return -1;
}