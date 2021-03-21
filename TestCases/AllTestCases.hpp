//
//  AllTestCases.hpp
//  JSONParser
//
//  Created by Aditya Vikram on 13/03/21.
//

#ifndef AllTestCases_h
#define AllTestCases_h
#include <chrono>
#include <string>
#include "lexer.hpp"

class TestClass {
public:
    static void runAllTests();
};

class LexerTestClass {
    static std::string generate(JSONParser::TokenType);
public:
    static uint64_t timeLexer(const int numIter, int numParts);
};

#endif /* AllTestCases_h */
