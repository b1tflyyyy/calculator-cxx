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

#include "rpn-evaluator.hpp"

double RPNEvaluator::Evaluate(const std::vector<Tokenizer::TokenPair>& rpn_expression)
{
    std::stack<double> stack{};
    double sign{ 1.0 };

    for (std::size_t i{}; i < std::size(rpn_expression); ++i)
    {
        const auto& [lexeme, token]{ rpn_expression[i] };
        
        switch (token) 
        {
        case Tokenizer::Token::Integer:
        case Tokenizer::Token::FloatingPoint:
        {
            const auto num{ lexeme.toDouble() * sign };
            sign = 1.0;

            stack.push(num);
            break;
        }

        case Tokenizer::Token::UnaryOperator:
        {
            sign = -1.0;
            break;
        }

        case Tokenizer::Token::Operator:
        {
            const auto second_operand{ stack.top() };
            stack.pop();

            const auto first_operand{ stack.top() };
            stack.pop();

            if (lexeme == QStringLiteral("+"))
            {
                stack.push(second_operand + first_operand);
                break;
            }

            if (lexeme == QStringLiteral("-"))
            {
                stack.push(first_operand - second_operand);
                break;
            }

            if (lexeme == QStringLiteral("/"))
            {
                stack.push(first_operand / second_operand);
                break;
            }

            if (lexeme == QStringLiteral("*"))
            {
                stack.push(first_operand * second_operand);
                break;
            }

            if (lexeme == QStringLiteral("^"))
            {
                stack.push(std::pow(first_operand, second_operand));
                break;
            }

            break;
        }
        }
    }

    return stack.top();
}