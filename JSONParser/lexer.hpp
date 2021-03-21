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
constexpr char comma = ',';
constexpr char colon = ':';
constexpr char leftBrace = '{';
constexpr char rightBrace = '}';
constexpr char leftBracket = '[';
constexpr char rightBracket = ']';
constexpr auto jSONFormatSpecifiers = {comma, colon, leftBrace, rightBrace, leftBracket, rightBracket};

struct StringLexer {
    static constexpr std::string_view lex(const std::string_view inputString) {
        if (inputString.length() == 0 || inputString[0] != doubleQuote) {
            return std::string_view();
        }
        const auto stringBegin = inputString.begin() + 1;
        const auto closingIt = std::find(stringBegin, inputString.end(), doubleQuote);
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

struct NumberLexer {
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

struct BoolLexer {
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


struct NullLexer {
    static constexpr std::string_view lex(const std::string_view inputString) noexcept {
        if (inputString.rfind(nullString, 0) == 0) {
            return std::string_view(inputString.data(), strlen(nullString));
        }
        return std::string_view();
    }
};

struct JsonFormatLexer {
    static constexpr std::string_view lex(const std::string_view inputString) noexcept {
        if (inputString.size() > 0 &&
            std::find(std::begin(jSONFormatSpecifiers), std::end(jSONFormatSpecifiers), inputString[0]) != std::end(jSONFormatSpecifiers)) {
            return std::string_view(inputString.data(), 1);
        }
        return std::string_view();
    }
};

enum class TokenType {
    String,
    Int,
    Double,
    Bool,
    Null,
    JsonFormatSpecifier,
    None
};

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
struct Token {
    std::string value;
    TokenType type;
    Token(const std::string& value, TokenType type): value(value), type(type) {}
};
#pragma clang diagnostic pop

class Lexer {
    static constexpr std::pair<std::string_view, TokenType> tryLex(const std::string_view inputString) {
        auto lexedString = StringLexer::lex(inputString);
        if (lexedString.size() > 0) {
            return std::make_pair(lexedString, TokenType::String);
        }
        
        auto lexedNumber = NumberLexer::lex(inputString);
        if (lexedNumber.size() > 0) {
            bool isDouble = (lexedNumber.find('.') != std::string_view::npos);
            return std::make_pair(lexedNumber, isDouble ? TokenType::Double : TokenType::Int);
        }
        
        auto lexedBool = BoolLexer::lex(inputString);
        if (lexedBool.size() > 0) {
            return std::make_pair(lexedBool, TokenType::Bool);
        }
        
        auto lexedNull = NullLexer::lex(inputString);
        if (lexedNull.size() > 0) {
            return std::make_pair(lexedNull, TokenType::Null);
        }
        
        auto lexedFormatSpecifier = JsonFormatLexer::lex(inputString);
        if (lexedFormatSpecifier.size() > 0) {
            return std::make_pair(lexedFormatSpecifier, TokenType::JsonFormatSpecifier);
        }
        
        return std::make_pair(std::string_view(), TokenType::None);
    }
public:
    static std::vector<Token> lex(const std::string& inputString) {
        std::string_view inputStringView = inputString;
        std::vector<Token> lexOutput;
        while (inputStringView.size() > 0) {
            // Remove whitespaces from begining
            auto it = inputStringView.begin();
            while (it != inputStringView.end() && std::isspace(*it)) {
                ++it;
            }
            inputStringView.remove_prefix(it - inputStringView.begin());
            
            if (inputStringView.size() == 0) {
                break;
            }
            
            auto [lexedString, tokenType] = tryLex(inputStringView);
            
            if (lexedString.size() == 0) {
                throw std::invalid_argument("Can't lex the input string");
            }

            lexOutput.emplace_back(std::string(lexedString), tokenType);
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
