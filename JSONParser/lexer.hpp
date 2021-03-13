//
//  lexer.hpp
//  JSONParser
//
//  Created by Aditya Vikram on 13/03/21.
//

#ifndef lexer_h
#define lexer_h

#include <string>
#include <vector>
#include <stdexcept>
#include <cctype>
#include <algorithm>
#include <cstring>

namespace JSONParser {

constexpr char doubleQuote = '\"';
constexpr auto trueString = "true";
constexpr auto falseString = "false";
constexpr auto nullString = "null";
constexpr char negativeSign = '-';
constexpr char dot = '.';

class StringLexer {
public:
    static constexpr std::string_view lex(const std::string_view inputString) {
        if (inputString.length() == 0 || inputString[0] != doubleQuote) {
            return std::string_view();
        }
        auto stringBegin = inputString.begin() + 1;
        auto closingIt = std::find(stringBegin, inputString.end(), doubleQuote);
        if (closingIt != inputString.end()) {
            return std::string_view(
                                    (stringBegin != closingIt) ? &*stringBegin : nullptr,
                                    (closingIt - stringBegin)
                                );
        } else {
            throw std::out_of_range("Cannot find closing quote");
        }
    }
};

class NumberLexer {
public:
    static constexpr std::string_view lex(const std::string_view inputString) noexcept {
        if (inputString.length() == 0 ||
            (inputString[0] != negativeSign && !std::isdigit(inputString[0]))) {
            return std::string_view();
        }
        bool hasDot = false;
        char previousChar = inputString[0];
        auto it = std::next(inputString.begin());
        for (; it != inputString.end(); ++it) {
            if (std::isdigit(*it)) {
                previousChar = *it;
                continue;
            }
            if (*it == dot) {
                if (hasDot || previousChar == negativeSign) {
                    previousChar = dot;
                    break;
                }
                hasDot = true;
                previousChar = dot;
                continue;
            }
            break;
        }
        if (previousChar == dot) {
            --it;
        }
        const auto length = (it - inputString.begin());
        if (length > 1 || inputString[0] != negativeSign) {
            return std::string_view(inputString.data(), length);
        }
        return std::string_view();
    }
};

class BoolLexer {
public:
    static constexpr std::string_view lex(const std::string_view inputString) noexcept {
        if (inputString.rfind(trueString, 0) == 0) {
            return std::string_view(inputString.data(), strlen(trueString));
        }
        if (inputString.rfind(falseString, 0) == 0) {
            return std::string_view(inputString.data(), strlen(falseString));
        }
        return std::string_view();
    }
};


class NullLexer {
public:
    static constexpr std::string_view lex(const std::string_view inputString) noexcept {
        if (inputString.rfind(nullString, 0) == 0) {
            return std::string_view(inputString.data(), strlen(nullString));
        }
        return std::string_view();
    }
};

enum class TokenType {
    String,
    Number,
    Bool,
    Null,
    None
};

class Lexer {
    static constexpr std::pair<std::string_view, TokenType> tryLex(const std::string_view inputString) {
        auto lexedString = StringLexer::lex(inputString);
        if (lexedString.size() > 0) {
            return std::make_pair(lexedString, TokenType::String);
        }
        
        auto lexedNumber = NumberLexer::lex(inputString);
        if (lexedNumber.size() > 0) {
            return std::make_pair(lexedNumber, TokenType::Number);
        }
        
        auto lexedBool = BoolLexer::lex(inputString);
        if (lexedBool.size() > 0) {
            return std::make_pair(lexedBool, TokenType::Bool);
        }
        
        auto lexedNull = NullLexer::lex(inputString);
        if (lexedNull.size() > 0) {
            return std::make_pair(lexedNull, TokenType::Null);
        }
        return std::make_pair(std::string_view(), TokenType::None);
    }
public:
    static std::vector<std::string> lex(const std::string& inputString) {
        std::string_view inputStringView = inputString;
        std::vector<std::string> lexOutput;
        while (inputStringView.size() > 0) {
            auto [lexedString, tokenType] = tryLex(inputStringView);
            
            if (lexedString.size() == 0) {
                throw std::invalid_argument("Can't lex the input string");
            }

            lexOutput.emplace_back(lexedString);
            if (tokenType != TokenType::String) {
                inputStringView.remove_prefix(lexedString.size());
            } else {
                auto prefixSize = std::min(lexedString.size() + 2, inputStringView.size());
                inputStringView.remove_prefix(prefixSize);
            }
        }
        return lexOutput;
    }
};

}

#endif /* lexer_h */
