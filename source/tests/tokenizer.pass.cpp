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

#include <array>
#include <string>

using Tc = Utils::Logger::Tc;
using Emp = Utils::Logger::Emp;

class TokenizerTest : public ::testing::Test
{
protected:
    Tokenizer mTokenizer;
};

[[maybe_unused]] static std::string_view GetTokenStr(Tokenizer::Token token)
{
    switch (token)
    {
    case Tokenizer::Token::Integer:          return "Integer";
    case Tokenizer::Token::FloatingPoint:    return "FloatingPoint";
    case Tokenizer::Token::LeftParenthesis:  return "LeftParenthesis";
    case Tokenizer::Token::RightParenthesis: return "RightParenthesis";
    case Tokenizer::Token::UnaryOperator:    return "UnaryOperator";
    case Tokenizer::Token::Operator:         return "Operator";
    default:                                 return "Unknown";
    }
}

[[maybe_unused]] static void PrintTokens(const std::vector<Tokenizer::TokenPair>& tokens)
{
    for (const auto& [lexeme, token] : tokens)
    {
        std::cout << lexeme.toStdString() << std::setw(10) << '[' << GetTokenStr(token) << ']' << '\n'; 
    }
}

TEST_F(TokenizerTest, TokenizeSimpleExpression) 
{
    std::array<Tokenizer::TokenPair, 3> expected_tokens
    {
        Tokenizer::TokenPair{ QStringLiteral("1"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral("+"), Tokenizer::Token::Operator },
        Tokenizer::TokenPair{ QStringLiteral("2"), Tokenizer::Token::Integer },
    };
    
    mTokenizer.Init(QStringLiteral("1+2"));
    mTokenizer.Run();

    const auto& tokens = mTokenizer.GetTokens();
    ASSERT_EQ(std::size(tokens), std::size(expected_tokens));

    for (std::size_t i{}; i < std::size(expected_tokens); ++i)
    {
        const auto& [token, lexeme]{ tokens[i] };
        const auto& [expected_token, expected_lexeme]{ expected_tokens[i] };
        
        ASSERT_EQ(token, expected_token);
        ASSERT_EQ(lexeme, expected_lexeme);
    }

    ASSERT_FALSE(mTokenizer.HasError());
    ASSERT_TRUE(mTokenizer.GetErrorMessage().isEmpty());
}

TEST_F(TokenizerTest, TokenizeComplexExpression)
{
    std::array<Tokenizer::TokenPair, 13> expected_tokens
    {
        Tokenizer::TokenPair{ QStringLiteral("("), Tokenizer::Token::LeftParenthesis },
        Tokenizer::TokenPair{ QStringLiteral("-"), Tokenizer::Token::UnaryOperator },
        Tokenizer::TokenPair{ QStringLiteral("2.22"), Tokenizer::Token::FloatingPoint },
        Tokenizer::TokenPair{ QStringLiteral(")"), Tokenizer::Token::RightParenthesis },
        Tokenizer::TokenPair{ QStringLiteral("+"), Tokenizer::Token::Operator },
        Tokenizer::TokenPair{ QStringLiteral("22"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral("+"), Tokenizer::Token::Operator },
        Tokenizer::TokenPair{ QStringLiteral("2"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral("^"), Tokenizer::Token::Operator },
        Tokenizer::TokenPair{ QStringLiteral("("), Tokenizer::Token::LeftParenthesis },
        Tokenizer::TokenPair{ QStringLiteral("-"), Tokenizer::Token::UnaryOperator },
        Tokenizer::TokenPair{ QStringLiteral("2"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral(")"), Tokenizer::Token::RightParenthesis }
    };
    
    mTokenizer.Init(QStringLiteral("(-2.22)+22+2^(-2)"));
    mTokenizer.Run();

    const auto& tokens = mTokenizer.GetTokens();
    ASSERT_EQ(std::size(tokens), std::size(expected_tokens));

    for (std::size_t i{}; i < std::size(expected_tokens); ++i)
    {
        const auto& [token, lexeme]{ tokens[i] };
        const auto& [expected_token, expected_lexeme]{ expected_tokens[i] };
        
        ASSERT_EQ(token, expected_token);
        ASSERT_EQ(lexeme, expected_lexeme);
    }
    
    ASSERT_FALSE(mTokenizer.HasError());
    ASSERT_TRUE(mTokenizer.GetErrorMessage().isEmpty());
}

TEST_F(TokenizerTest, TokenizeNestedExpression)
{
    std::array<Tokenizer::TokenPair, 44> expected_tokens
    {
        Tokenizer::TokenPair{ QStringLiteral("("), Tokenizer::Token::LeftParenthesis },
        Tokenizer::TokenPair{ QStringLiteral("("), Tokenizer::Token::LeftParenthesis },
        Tokenizer::TokenPair{ QStringLiteral("("), Tokenizer::Token::LeftParenthesis },
        Tokenizer::TokenPair{ QStringLiteral("("), Tokenizer::Token::LeftParenthesis },
        Tokenizer::TokenPair{ QStringLiteral("2"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral("+"), Tokenizer::Token::Operator },
        Tokenizer::TokenPair{ QStringLiteral("2"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral(")"), Tokenizer::Token::RightParenthesis },
        Tokenizer::TokenPair{ QStringLiteral(")"), Tokenizer::Token::RightParenthesis },
        Tokenizer::TokenPair{ QStringLiteral(")"), Tokenizer::Token::RightParenthesis },
        Tokenizer::TokenPair{ QStringLiteral(")"), Tokenizer::Token::RightParenthesis },
        Tokenizer::TokenPair{ QStringLiteral("/"), Tokenizer::Token::Operator },
        Tokenizer::TokenPair{ QStringLiteral("2"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral("*"), Tokenizer::Token::Operator },
        Tokenizer::TokenPair{ QStringLiteral("("), Tokenizer::Token::LeftParenthesis },
        Tokenizer::TokenPair{ QStringLiteral("-"), Tokenizer::Token::UnaryOperator },
        Tokenizer::TokenPair{ QStringLiteral("2"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral(")"), Tokenizer::Token::RightParenthesis },
        Tokenizer::TokenPair{ QStringLiteral("^"), Tokenizer::Token::Operator },
        Tokenizer::TokenPair{ QStringLiteral("333"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral("/"), Tokenizer::Token::Operator },
        Tokenizer::TokenPair{ QStringLiteral("663"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral("+"), Tokenizer::Token::Operator },
        Tokenizer::TokenPair{ QStringLiteral("2"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral("+"), Tokenizer::Token::Operator },
        Tokenizer::TokenPair{ QStringLiteral("4"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral("+"), Tokenizer::Token::Operator },
        Tokenizer::TokenPair{ QStringLiteral("6"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral("+"), Tokenizer::Token::Operator },
        Tokenizer::TokenPair{ QStringLiteral("4"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral("+"), Tokenizer::Token::Operator },
        Tokenizer::TokenPair{ QStringLiteral("3"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral("/"), Tokenizer::Token::Operator },
        Tokenizer::TokenPair{ QStringLiteral("("), Tokenizer::Token::LeftParenthesis },
        Tokenizer::TokenPair{ QStringLiteral("-"), Tokenizer::Token::UnaryOperator },
        Tokenizer::TokenPair{ QStringLiteral("4.4444444"), Tokenizer::Token::FloatingPoint },
        Tokenizer::TokenPair{ QStringLiteral(")"), Tokenizer::Token::RightParenthesis },
        Tokenizer::TokenPair{ QStringLiteral("*"), Tokenizer::Token::Operator },
        Tokenizer::TokenPair{ QStringLiteral("1"), Tokenizer::Token::Integer },
        Tokenizer::TokenPair{ QStringLiteral("^"), Tokenizer::Token::Operator },
        Tokenizer::TokenPair{ QStringLiteral("("), Tokenizer::Token::LeftParenthesis },
        Tokenizer::TokenPair{ QStringLiteral("-"), Tokenizer::Token::UnaryOperator },
        Tokenizer::TokenPair{ QStringLiteral("0.4324234"), Tokenizer::Token::FloatingPoint },
        Tokenizer::TokenPair{ QStringLiteral(")"), Tokenizer::Token::RightParenthesis }
    };

    mTokenizer.Init(QStringLiteral("((((2+2))))/2*(-2)^333/663+2+4+6+4+3/(-4.4444444)*1^(-0.4324234)"));
    mTokenizer.Run();

    const auto& tokens = mTokenizer.GetTokens();
    ASSERT_EQ(std::size(tokens), std::size(expected_tokens));

    for (std::size_t i{}; i < std::size(expected_tokens); ++i)
    {
        const auto& [token, lexeme]{ tokens[i] };
        const auto& [expected_token, expected_lexeme]{ expected_tokens[i] };

        ASSERT_EQ(token, expected_token);
        ASSERT_EQ(lexeme, expected_lexeme);
    }

    ASSERT_FALSE(mTokenizer.HasError());
    ASSERT_TRUE(mTokenizer.GetErrorMessage().isEmpty());
}

TEST_F(TokenizerTest, HandlesEmptyInput) 
{
    mTokenizer.Init(QStringLiteral(""));
    mTokenizer.Run();

    UT_CC_DEFAULT_LOGGER_COLOR_INFO(Tc::black,Tc::green, Emp::bold,
        "Warning expected, OK"
    );

    ASSERT_TRUE(mTokenizer.HasError());
    ASSERT_FALSE(mTokenizer.GetErrorMessage().isEmpty());
}

TEST_F(TokenizerTest, HandlesOnlySpaces) 
{
    mTokenizer.Init("   ");
    mTokenizer.Run(); 

    UT_CC_DEFAULT_LOGGER_COLOR_INFO(Tc::black,Tc::green, Emp::bold,
        "Warning expected, OK"
    );

    ASSERT_TRUE(mTokenizer.HasError());
    ASSERT_FALSE(mTokenizer.GetErrorMessage().isEmpty());
}

TEST_F(TokenizerTest, TokenizeExpressionWithInvalidCharacter)
{
    mTokenizer.Init("2+3$5"); 
    mTokenizer.Run();

    UT_CC_DEFAULT_LOGGER_COLOR_INFO(Tc::black,Tc::green, Emp::bold,
        "Warning expected, OK"
    );

    ASSERT_TRUE(mTokenizer.HasError());
    ASSERT_FALSE(mTokenizer.GetErrorMessage().isEmpty());
}

TEST_F(TokenizerTest, TokenizeExpressionWithMultipleDots)
{
    mTokenizer.Init("3..14+2");
    mTokenizer.Run();

    UT_CC_DEFAULT_LOGGER_COLOR_INFO(Tc::black,Tc::green, Emp::bold,
        "Warning expected, OK"
    );

    ASSERT_TRUE(mTokenizer.HasError());
    ASSERT_FALSE(mTokenizer.GetErrorMessage().isEmpty());
}

TEST_F(TokenizerTest, TokenizeExpressionWithConsecutiveOperators)
{
    mTokenizer.Init("5++3"); 
    mTokenizer.Run();

    UT_CC_DEFAULT_LOGGER_COLOR_INFO(Tc::black,Tc::green, Emp::bold,
        "Warning expected, OK"
    );

    ASSERT_TRUE(mTokenizer.HasError());
    ASSERT_FALSE(mTokenizer.GetErrorMessage().isEmpty());
}

TEST_F(TokenizerTest, TokenizeExpressionWithInvalidFloat)
{
    mTokenizer.Init("1.2.3+4"); 
    mTokenizer.Run();

    UT_CC_DEFAULT_LOGGER_COLOR_INFO(Tc::black,Tc::green, Emp::bold,
        "Warning expected, OK"
    );

    ASSERT_TRUE(mTokenizer.HasError());
    ASSERT_FALSE(mTokenizer.GetErrorMessage().isEmpty());
}

TEST_F(TokenizerTest, TokenizeExpressionWithLetter)
{
    mTokenizer.Init("5+a");
    mTokenizer.Run();

    UT_CC_DEFAULT_LOGGER_COLOR_INFO(Tc::black,Tc::green, Emp::bold,
        "Warning expected, OK"
    );

    ASSERT_TRUE(mTokenizer.HasError());
    ASSERT_FALSE(mTokenizer.GetErrorMessage().isEmpty());
}
