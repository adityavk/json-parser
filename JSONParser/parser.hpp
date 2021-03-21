//
//  parser.hpp
//  JSONParser
//
//  Created by Aditya Vikram on 14/03/21.
//

#ifndef parser_h
#define parser_h

#include "lexer.hpp"
#include "JsonValue.h"

namespace JSONParser {

class Parser {
    using TokenVector = std::vector<Token>;
    using TokenConstIterator = TokenVector::const_iterator;
    using IteratorValuePair = std::pair<TokenConstIterator, JSONValue>;
    
    static constexpr bool isStringEqualToChar(const std::string& string, char c) noexcept {
        return string.length() == 1 && string[0] == c;
    }
    
    static JSONValue parsePrimitiveToken(const Token& token) {
        switch (token.type) {
            case TokenType::Null:
                return JSONValue();
            case TokenType::String:
                return JSONValue(token.value);
            case TokenType::Double:
                return JSONValue(std::stod(token.value));
            case TokenType::Int:
                return JSONValue(static_cast<uint64_t>(std::stoll(token.value)));
            case TokenType::Bool:
                return JSONValue((token.value == "true"));
            case TokenType::JsonFormatSpecifier:
            case TokenType::None:
                throw std::invalid_argument("Trying to parse a non-primitive token into JsonValue");
        }
        
    }
    
    // begin points to the token succeeding leftbrace in the lexer output
    static IteratorValuePair parseObject(TokenConstIterator begin, TokenConstIterator end) {
        auto it = begin;
        if (isStringEqualToChar((*it).value, rightBrace)) {
            return std::make_pair(it, JSONObject());
        }
        
        JSONObject object;
        
        while (it != end) {
            // Need at least 3 tokens now: colon, value and right brace.
            if ((end - it) < 3) {
                throw std::invalid_argument("Insufficent tokens in the input");
            }
            
            const auto firstToken = *it;
            if (firstToken.type != TokenType::String) {
                throw std::invalid_argument("Insufficent tokens in the input");
            }
            
            const auto secondToken = *(++it);
            if (secondToken.type != TokenType::JsonFormatSpecifier || !isStringEqualToChar(secondToken.value, colon)) {
                throw std::invalid_argument("Insufficent tokens in the input");
            }
            
            const auto parseResult = parseRecursive(++it, end);
            object.setMember(firstToken.value, std::move(parseResult.second));
            it = parseResult.first;
            if (it != end) {
                if (isStringEqualToChar((*it).value, comma)) {
                    ++it;
                } else if (isStringEqualToChar((*it).value, rightBrace)) {
                    return std::make_pair(++it, object);
                } else {
                    throw std::invalid_argument("No right bracket in the input");
                }
                continue;
            }
            
        }
        throw std::invalid_argument("No right bracket in the input");
    }
    
    // begin points to the token succeeding leftbracket in the lexer output
    static IteratorValuePair parseArray(TokenConstIterator begin, TokenConstIterator end) {
        auto it = begin;
        if (isStringEqualToChar((*it).value, rightBracket)) {
            return std::make_pair(it, JSONArray());
        }

        JSONArray array;

        while (it != end) {
            const auto parseResult = parseRecursive(it, end);
            array.addMember(parseResult.second);
            it = parseResult.first;
            if (it != end) {
                if (isStringEqualToChar((*it).value, comma)) {
                    ++it;
                } else if (isStringEqualToChar((*it).value, rightBracket)) {
                    return std::make_pair(++it, array);
                } else {
                    throw std::invalid_argument("No right bracket in the input");
                }
                continue;
            }
            
        }
        throw std::invalid_argument("No right bracket in the input");
    }
    
    static IteratorValuePair parseRecursive(TokenConstIterator begin, TokenConstIterator end) {
        if (begin == end || std::next(begin) == end) {
            return std::make_pair(begin, JSONValue());
        }
        
        const auto firstToken = *begin;
        
        if (firstToken.type != TokenType::JsonFormatSpecifier) {
            return std::make_pair(parseRecursive(std::next(begin), end).first, parsePrimitiveToken(firstToken)) ;
        }
        
        if (isStringEqualToChar(firstToken.value, leftBrace)) {
            return parseObject(std::next(begin), end);
        } else if (isStringEqualToChar(firstToken.value, leftBracket)) {
            return parseArray(std::next(begin), end);
        }
        return std::make_pair(begin, JSONValue());;
    }
public:
    static JSONObject parse(const std::string& inputString) {
        const auto lexedTokens = Lexer::lex(inputString);
        auto endIt = parseRecursive(lexedTokens.begin(), lexedTokens.end());
        if (endIt.first == lexedTokens.end() && endIt.second.isObject()) {
            return endIt.second.getObject();
        }
        throw std::invalid_argument("Unable to parse the input string");
    }
};

}

#endif /* parser_h */
