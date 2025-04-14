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

#include <gtest/gtest.h>

#include <tokenizer.hpp>
#include <rpn-converter.hpp>
#include <rpn-evaluator.hpp>

class RPNEvaluatorTest : public ::testing::Test
{
protected:
    Tokenizer mTokenizer;
    RPNConverter mRPNConverter;
};

TEST_F(RPNEvaluatorTest, Addition)
{
    mTokenizer.Init(QStringLiteral("3+4"));
    mTokenizer.Run();

    const auto tokens{ mTokenizer.GetTokens() };
    const auto rpn_expression{ mRPNConverter.Convert(tokens) };
    const auto result{ RPNEvaluator::Evaluate(rpn_expression) };

    ASSERT_FALSE(mTokenizer.HasError());
    ASSERT_TRUE(mTokenizer.GetErrorMessage().isEmpty());
    ASSERT_TRUE(mRPNConverter.GetErrorMessage().isEmpty());
    ASSERT_FALSE(mRPNConverter.HasError());
    ASSERT_EQ(result, 7);
}

TEST_F(RPNEvaluatorTest, SubtractionAndMultiplication)
{
    mTokenizer.Init(QStringLiteral("8-3*2"));
    mTokenizer.Run();

    const auto tokens{ mTokenizer.GetTokens() };
    const auto rpn_expression{ mRPNConverter.Convert(tokens) };
    const auto result{ RPNEvaluator::Evaluate(rpn_expression) };

    ASSERT_FALSE(mTokenizer.HasError());
    ASSERT_TRUE(mTokenizer.GetErrorMessage().isEmpty());
    ASSERT_TRUE(mRPNConverter.GetErrorMessage().isEmpty());
    ASSERT_FALSE(mRPNConverter.HasError());

    ASSERT_EQ(result, 2);
}

TEST_F(RPNEvaluatorTest, DivisionAndAddition)
{
    mTokenizer.Init(QStringLiteral("10/2+3"));
    mTokenizer.Run();

    const auto tokens{ mTokenizer.GetTokens() };
    const auto rpn_expression{ mRPNConverter.Convert(tokens) };
    const auto result{ RPNEvaluator::Evaluate(rpn_expression) };

    ASSERT_FALSE(mTokenizer.HasError());
    ASSERT_TRUE(mTokenizer.GetErrorMessage().isEmpty());
    ASSERT_TRUE(mRPNConverter.GetErrorMessage().isEmpty());
    ASSERT_FALSE(mRPNConverter.HasError());

    ASSERT_EQ(result, 8);
}

TEST_F(RPNEvaluatorTest, ExponentiationTest)
{
    mTokenizer.Init(QStringLiteral("2^3"));
    mTokenizer.Run();

    const auto tokens{ mTokenizer.GetTokens() };
    const auto rpn_expression{ mRPNConverter.Convert(tokens) };
    const auto result{ RPNEvaluator::Evaluate(rpn_expression) };

    ASSERT_FALSE(mTokenizer.HasError());
    ASSERT_TRUE(mTokenizer.GetErrorMessage().isEmpty());
    ASSERT_TRUE(mRPNConverter.GetErrorMessage().isEmpty());
    ASSERT_FALSE(mRPNConverter.HasError());

    ASSERT_EQ(result, 8);
}

TEST_F(RPNEvaluatorTest, ParenthesesPrecedence)
{
    mTokenizer.Init(QStringLiteral("(2+3)*4"));
    mTokenizer.Run();
    
    const auto tokens{ mTokenizer.GetTokens() };
    const auto rpn_expression{ mRPNConverter.Convert(tokens) };
    const auto result{ RPNEvaluator::Evaluate(rpn_expression) };
    
    ASSERT_FALSE(mTokenizer.HasError());
    ASSERT_TRUE(mTokenizer.GetErrorMessage().isEmpty());
    ASSERT_TRUE(mRPNConverter.GetErrorMessage().isEmpty());
    ASSERT_FALSE(mRPNConverter.HasError());
    
    ASSERT_EQ(result, 20);
}

TEST_F(RPNEvaluatorTest, ComplexExpressionWithParentheses)
{
    mTokenizer.Init(QStringLiteral("(7-2)*(4+1)/3"));
    mTokenizer.Run();
    
    const auto tokens{ mTokenizer.GetTokens() };
    const auto rpn_expression{ mRPNConverter.Convert(tokens) };
    const auto result{ RPNEvaluator::Evaluate(rpn_expression) };
    
    ASSERT_FALSE(mTokenizer.HasError());
    ASSERT_TRUE(mTokenizer.GetErrorMessage().isEmpty());
    ASSERT_TRUE(mRPNConverter.GetErrorMessage().isEmpty());
    ASSERT_FALSE(mRPNConverter.HasError());
    
    ASSERT_NEAR(result, 8.33333, 0.0001);
}

TEST_F(RPNEvaluatorTest, AdditionWithNegatives) 
{
    mTokenizer.Init(QStringLiteral("(-3)+3"));
    mTokenizer.Run();

    const auto tokens{mTokenizer.GetTokens()};
    const auto rpn_expression{mRPNConverter.Convert(tokens)};
    const auto result{RPNEvaluator::Evaluate(rpn_expression)};

    ASSERT_FALSE(mTokenizer.HasError());
    ASSERT_TRUE(mTokenizer.GetErrorMessage().isEmpty());
    ASSERT_TRUE(mRPNConverter.GetErrorMessage().isEmpty());
    ASSERT_FALSE(mRPNConverter.HasError());

    ASSERT_EQ(result, 0);
}

TEST_F(RPNEvaluatorTest, ReversedAdditionWithNegatives)
{
    mTokenizer.Init(QStringLiteral("3+(-3)"));
    mTokenizer.Run();

    const auto tokens{mTokenizer.GetTokens()};
    const auto rpn_expression{mRPNConverter.Convert(tokens)};
    const auto result{RPNEvaluator::Evaluate(rpn_expression)};

    ASSERT_FALSE(mTokenizer.HasError());
    ASSERT_TRUE(mTokenizer.GetErrorMessage().isEmpty());
    ASSERT_FALSE(mRPNConverter.HasError());

    ASSERT_EQ(result, 0);
}

TEST_F(RPNEvaluatorTest, NegativeExponent) 
{
    mTokenizer.Init(QStringLiteral("4^(-3)"));
    mTokenizer.Run();

    const auto tokens{mTokenizer.GetTokens()};
    const auto rpn_expression{mRPNConverter.Convert(tokens)};
    const auto result{RPNEvaluator::Evaluate(rpn_expression)};

    ASSERT_FALSE(mTokenizer.HasError());
    ASSERT_TRUE(mRPNConverter.GetErrorMessage().isEmpty());
    ASSERT_FALSE(mRPNConverter.HasError());

    ASSERT_DOUBLE_EQ(result, 0.015625);
}

TEST_F(RPNEvaluatorTest, SubtractionWithNegativeResult) 
{
    mTokenizer.Init(QStringLiteral("5-8"));
    mTokenizer.Run();

    const auto tokens{mTokenizer.GetTokens()};
    const auto rpn_expression{mRPNConverter.Convert(tokens)};
    const auto result{RPNEvaluator::Evaluate(rpn_expression)};

    ASSERT_FALSE(mTokenizer.HasError());
    ASSERT_TRUE(mRPNConverter.GetErrorMessage().isEmpty());
    ASSERT_FALSE(mRPNConverter.HasError());

    ASSERT_EQ(result, -3);
}

TEST_F(RPNEvaluatorTest, MultiplicationWithNegatives) 
{
    mTokenizer.Init(QStringLiteral("(-4)*(-2.5)"));
    mTokenizer.Run();

    const auto tokens{mTokenizer.GetTokens()};
    const auto rpn_expression{mRPNConverter.Convert(tokens)};
    const auto result{RPNEvaluator::Evaluate(rpn_expression)};

    ASSERT_FALSE(mTokenizer.HasError());
    ASSERT_TRUE(mRPNConverter.GetErrorMessage().isEmpty());
    ASSERT_FALSE(mRPNConverter.HasError());

    ASSERT_DOUBLE_EQ(result, 10.0);
}

TEST_F(RPNEvaluatorTest, ComplexExpressionWithNegatives) 
{
    mTokenizer.Init(QStringLiteral("((-2)+5)*3^(1-4)"));
    mTokenizer.Run();

    const auto tokens{mTokenizer.GetTokens()};
    const auto rpn_expression{mRPNConverter.Convert(tokens)};
    const auto result{RPNEvaluator::Evaluate(rpn_expression)};

    ASSERT_FALSE(mTokenizer.HasError());
    ASSERT_TRUE(mRPNConverter.GetErrorMessage().isEmpty());
    ASSERT_FALSE(mRPNConverter.HasError());

    ASSERT_DOUBLE_EQ(result, 3 * std::pow(3, -3));
}