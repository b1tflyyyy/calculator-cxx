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

#include <array>

#include <tokenizer/tokenizer.hpp>
#include <rpn-converter/rpn-converter.hpp>

#include <utils/logger/logger.hpp>

using Tc = Utils::Logger::Tc;
using Emp = Utils::Logger::Emp;

class RPNConverterTest : public ::testing::Test
{
protected:
    Tokenizer mTokenizer;
    RPNConverter mRPNConverter;
};

TEST_F(RPNConverterTest, BasicArithmetic)
{   
    std::array<Tokenizer::TokenPair, 5> expected_rpn
    {
        Tokenizer::TokenPair{ QStringLiteral("5"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral("4"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral("+"), Tokenizer::Token::Operator },
        Tokenizer::TokenPair{ QStringLiteral("3"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral("-"), Tokenizer::Token::Operator },
    };

    mTokenizer.Init(QStringLiteral("5+4-3"));
    mTokenizer.Run();

    const auto& tokens{ mTokenizer.GetTokens() };
    const auto rpn_tokens{ mRPNConverter.Convert(tokens) };

    ASSERT_EQ(std::size(expected_rpn), std::size(rpn_tokens));

    for (std::size_t i{}; i < std::size(expected_rpn); ++i)
    {
        ASSERT_EQ(expected_rpn[i], rpn_tokens[i]);
    }

    ASSERT_FALSE(mTokenizer.HasError());
    ASSERT_TRUE(mTokenizer.GetErrorMessage().isEmpty());
    ASSERT_TRUE(mRPNConverter.GetErrorMessage().isEmpty());
    ASSERT_FALSE(mRPNConverter.HasError());
}

TEST_F(RPNConverterTest, MultiplicationAndDivision)
{
    std::array<Tokenizer::TokenPair, 5> expected_rpn
    {
        Tokenizer::TokenPair{ QStringLiteral("8"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral("7"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral("*"), Tokenizer::Token::Operator },
        Tokenizer::TokenPair{ QStringLiteral("2"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral("/"), Tokenizer::Token::Operator },
    };

    mTokenizer.Init(QStringLiteral("8*7/2"));
    mTokenizer.Run();

    const auto& tokens{ mTokenizer.GetTokens() };
    const auto rpn_tokens{ mRPNConverter.Convert(tokens) };

    ASSERT_EQ(std::size(expected_rpn), std::size(rpn_tokens));

    for (std::size_t i{}; i < std::size(expected_rpn); ++i)
    {
        ASSERT_EQ(expected_rpn[i], rpn_tokens[i]);
    }

    ASSERT_FALSE(mTokenizer.HasError());
    ASSERT_TRUE(mTokenizer.GetErrorMessage().isEmpty());
    ASSERT_TRUE(mRPNConverter.GetErrorMessage().isEmpty());
    ASSERT_FALSE(mRPNConverter.HasError());
}

TEST_F(RPNConverterTest, ExponentOperator)
{
    std::array<Tokenizer::TokenPair, 3> expected_rpn
    {
        Tokenizer::TokenPair{ QStringLiteral("5"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral("2"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral("^"), Tokenizer::Token::Operator },
    };
    
    mTokenizer.Init(QStringLiteral("5^2"));
    mTokenizer.Run();
    
    const auto& tokens{ mTokenizer.GetTokens() };
    const auto rpn_tokens{ mRPNConverter.Convert(tokens) };
    
    ASSERT_EQ(std::size(expected_rpn), std::size(rpn_tokens));
    
    for (std::size_t i{}; i < std::size(expected_rpn); ++i)
    {
        ASSERT_EQ(expected_rpn[i], rpn_tokens[i]);
    }
    
    ASSERT_FALSE(mTokenizer.HasError());
    ASSERT_TRUE(mTokenizer.GetErrorMessage().isEmpty());
    ASSERT_TRUE(mRPNConverter.GetErrorMessage().isEmpty());
    ASSERT_FALSE(mRPNConverter.HasError());
}

TEST_F(RPNConverterTest, ComplexNestedExpression)
{
    std::array<Tokenizer::TokenPair, 11> expected_rpn
    {
        Tokenizer::TokenPair{ QStringLiteral("3"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral("4"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral("2"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral("1"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral("-"), Tokenizer::Token::Operator },
        Tokenizer::TokenPair{ QStringLiteral("*"), Tokenizer::Token::Operator },
        Tokenizer::TokenPair{ QStringLiteral("5"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral("2"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral("^"), Tokenizer::Token::Operator },
        Tokenizer::TokenPair{ QStringLiteral("/"), Tokenizer::Token::Operator },
        Tokenizer::TokenPair{ QStringLiteral("+"), Tokenizer::Token::Operator },
    };
    
    mTokenizer.Init(QStringLiteral("3+4*(2-1)/(5^2)"));
    mTokenizer.Run();
    
    const auto& tokens{ mTokenizer.GetTokens() };
    const auto rpn_tokens{ mRPNConverter.Convert(tokens) };
    
    ASSERT_EQ(std::size(expected_rpn), std::size(rpn_tokens));
    
    for (std::size_t i{}; i < std::size(expected_rpn); ++i)
    {
        ASSERT_EQ(expected_rpn[i], rpn_tokens[i]);
    }
    
    ASSERT_FALSE(mTokenizer.HasError());
    ASSERT_TRUE(mTokenizer.GetErrorMessage().isEmpty());
    ASSERT_TRUE(mRPNConverter.GetErrorMessage().isEmpty());
    ASSERT_FALSE(mRPNConverter.HasError());
}

TEST_F(RPNConverterTest, FloatingPointNumbers)
{
    std::array<Tokenizer::TokenPair, 3> expected_rpn
    {
        Tokenizer::TokenPair{ QStringLiteral("3.14"), Tokenizer::Token::FloatingPoint },
        Tokenizer::TokenPair{ QStringLiteral("2.5"), Tokenizer::Token::FloatingPoint },
        Tokenizer::TokenPair{ QStringLiteral("*"), Tokenizer::Token::Operator },
    };
    
    mTokenizer.Init(QStringLiteral("3.14*2.5"));
    mTokenizer.Run();
    
    const auto& tokens{ mTokenizer.GetTokens() };
    const auto rpn_tokens{ mRPNConverter.Convert(tokens) };
    
    ASSERT_EQ(std::size(expected_rpn), std::size(rpn_tokens));
    
    for (std::size_t i{}; i < std::size(expected_rpn); ++i)
    {
        ASSERT_EQ(expected_rpn[i], rpn_tokens[i]);
    }
    
    ASSERT_FALSE(mTokenizer.HasError());
    ASSERT_TRUE(mTokenizer.GetErrorMessage().isEmpty());
    ASSERT_TRUE(mRPNConverter.GetErrorMessage().isEmpty());
    ASSERT_FALSE(mRPNConverter.HasError());
}

TEST_F(RPNConverterTest, UnaryOperator)
{
    std::array<Tokenizer::TokenPair, 4> expected_rpn
    {
        Tokenizer::TokenPair{ QStringLiteral("-"), Tokenizer::Token::UnaryOperator },
        Tokenizer::TokenPair{ QStringLiteral("7"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral("3"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral("+"), Tokenizer::Token::Operator },
    };
    
    mTokenizer.Init(QStringLiteral("(-7)+3"));
    mTokenizer.Run();
    
    const auto& tokens{ mTokenizer.GetTokens() };
    const auto rpn_tokens{ mRPNConverter.Convert(tokens) };
    
    ASSERT_EQ(std::size(expected_rpn), std::size(rpn_tokens));
    
    for (std::size_t i{}; i < std::size(expected_rpn); ++i)
    {
        UT_CC_DEFAULT_LOGGER_INFO("rpn: {}", expected_rpn[i].first.toStdString());
        ASSERT_EQ(expected_rpn[i], rpn_tokens[i]);
    }
    
    ASSERT_FALSE(mTokenizer.HasError());
    ASSERT_TRUE(mTokenizer.GetErrorMessage().isEmpty());
    ASSERT_TRUE(mRPNConverter.GetErrorMessage().isEmpty());
    ASSERT_FALSE(mRPNConverter.HasError());
}

TEST_F(RPNConverterTest, ExponentOperatorPriority)
{
    std::array<Tokenizer::TokenPair, 5> expected_rpn
    {
        Tokenizer::TokenPair{ QStringLiteral("5"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral("2"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral("^"), Tokenizer::Token::Operator },
        Tokenizer::TokenPair{ QStringLiteral("3"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral("-"), Tokenizer::Token::Operator },
    };
    
    mTokenizer.Init(QStringLiteral("5^2-3"));
    mTokenizer.Run();
    
    const auto& tokens{ mTokenizer.GetTokens() };
    const auto rpn_tokens{ mRPNConverter.Convert(tokens) };
    
    ASSERT_EQ(std::size(expected_rpn), std::size(rpn_tokens));
    
    for (std::size_t i{}; i < std::size(expected_rpn); ++i)
    {
        UT_CC_DEFAULT_LOGGER_INFO("rpn: {}", expected_rpn[i].first.toStdString());
        ASSERT_EQ(expected_rpn[i], rpn_tokens[i]);
    }
    
    ASSERT_FALSE(mTokenizer.HasError());
    ASSERT_TRUE(mTokenizer.GetErrorMessage().isEmpty());
    ASSERT_TRUE(mRPNConverter.GetErrorMessage().isEmpty());
    ASSERT_FALSE(mRPNConverter.HasError());
}

TEST_F(RPNConverterTest, UnbalancedRightParenthesis)
{   
    mTokenizer.Init(QStringLiteral("(5+5))"));
    mTokenizer.Run();
    
    const auto& tokens{ mTokenizer.GetTokens() };
    const auto rpn_tokens{ mRPNConverter.Convert(tokens) };
    
    UT_CC_DEFAULT_LOGGER_COLOR_WARN(Tc::black, Tc::yellow, Emp::bold, 
        "RPN converter error: {}", mRPNConverter.GetErrorMessage().toStdString()
    );

    UT_CC_DEFAULT_LOGGER_COLOR_INFO(Tc::black, Tc::green, Emp::bold, 
        "Warning expected, OK"
    );

    ASSERT_FALSE(mTokenizer.HasError());
    ASSERT_TRUE(mTokenizer.GetErrorMessage().isEmpty());
    ASSERT_FALSE(mRPNConverter.GetErrorMessage().isEmpty());
    ASSERT_TRUE(mRPNConverter.HasError());
}

TEST_F(RPNConverterTest, UnbalancedLeftParenthesis)
{
    mTokenizer.Init(QStringLiteral("((5+5)"));
    mTokenizer.Run();
    
    const auto& tokens{ mTokenizer.GetTokens() };
    const auto rpn_tokens{ mRPNConverter.Convert(tokens) };
    
    UT_CC_DEFAULT_LOGGER_COLOR_WARN(Tc::black, Tc::yellow, Emp::bold,
        "RPN converter error: {}", mRPNConverter.GetErrorMessage().toStdString()
    );
    
    UT_CC_DEFAULT_LOGGER_COLOR_INFO(Tc::black, Tc::green, Emp::bold,
        "Warning expected, OK"
    );
    
    ASSERT_FALSE(mTokenizer.HasError());
    ASSERT_TRUE(mTokenizer.GetErrorMessage().isEmpty());
    ASSERT_FALSE(mRPNConverter.GetErrorMessage().isEmpty());
    ASSERT_TRUE(mRPNConverter.HasError());
}
