//
//  AllTestCases.cpp
//  JSONParser
//
//  Created by Aditya Vikram on 13/03/21.
//

#include "AllTestCases.hpp"
#include "lexer.hpp"
#include <iostream>

using namespace std;
using namespace JSONParser;

void lexString() {
    const std::string input("\"hello world\"fafnnk");
    cout<< "Lexed: "<< StringLexer::lex(input)<< "\n";
}

void lexEmptyString() {
    const std::string input("\"\"");
    cout<< "Empty lexed: "<< StringLexer::lex(input)<< "\n";
}

void lexStringNegative() {
    const std::string input("");
    cout<< "Not string lexed: "<< StringLexer::lex(input)<< "\n";
}

void lexTrue() {
    const std::string input("true");
    cout<< "True Lexed: "<< BoolLexer::lex(input)<< "\n";
}

void lexFalse() {
    const std::string input("false");
    cout<< "False Lexed: "<< BoolLexer::lex(input)<< "\n";
}

void lexTrueAnd() {
    const std::string input("trueAbc");
    cout<< "True And lexed: "<< BoolLexer::lex(input)<< "\n";
}

void lexFalseAnd() {
    const std::string input("falseAbc");
    cout<< "False And lexed: "<< BoolLexer::lex(input)<< "\n";
}

void lexBoolNegative() {
    const std::string input("abc");
    cout<< "Not bool lexed: "<< NullLexer::lex(input)<< "\n";
}

void lexNull() {
    const std::string input("null");
    cout<< "Null Lexed: "<< NullLexer::lex(input)<< "\n";
}

void lexNullAnd() {
    const std::string input("nullAbc");
    cout<< "Null And lexed: "<< NullLexer::lex(input)<< "\n";
}

void lexNullNegative() {
    const std::string input("abc");
    cout<< "Not null lexed: "<< NullLexer::lex(input)<< "\n";
}

void lexZero() {
    const std::string input("0");
    cout<< "Zero Lexed: "<< NumberLexer::lex(input)<< "\n";
}

void lexPositiveInteger() {
    const std::string input("2");
    cout<< "2 Lexed: "<< NumberLexer::lex(input)<< "\n";
}

void lexNegativeInteger() {
    const std::string input("-1");
    cout<< "-1 Lexed: "<< NumberLexer::lex(input)<< "\n";
}

void lexLongPositiveInteger() {
    const std::string input("2147915791750");
    cout<< "2147915791750 Lexed: "<< NumberLexer::lex(input)<< "\n";
}

void lexLongNegativeInteger() {
    const std::string input("-115710570175015015701");
    cout<< "-115710570175015015701 Lexed: "<< NumberLexer::lex(input)<< "\n";
}

void lexFloatingPointZero() {
    const std::string input("0.0");
    cout<< "0.0 Lexed: "<< NumberLexer::lex(input)<< "\n";
}

void lexLongerFloatingPointZero() {
    const std::string input("0.0000");
    cout<< "0.0000 Lexed: "<< NumberLexer::lex(input)<< "\n";
}

void lexPositiveFloatingPoint() {
    const std::string input("100.3");
    cout<< "100.3 Lexed: "<< NumberLexer::lex(input)<< "\n";
}

void lexNegativeFloatingPoint() {
    const std::string input("-1101.0");
    cout<< "-1101.0 Lexed: "<< NumberLexer::lex(input)<< "\n";
}

void lexLongPositiveFloatingPoint() {
    const std::string input("214.7915791750");
    cout<< "214.7915791750 Lexed: "<< NumberLexer::lex(input)<< "\n";
}

void lexLongNegativeFloatingPoint() {
    const std::string input("-115.710570175015015701");
    cout<< "-115.710570175015015701 Lexed: "<< NumberLexer::lex(input)<< "\n";
}

void lexZeroAnd() {
    const std::string input("0aava");
    cout<< "0 and Lexed: "<< NumberLexer::lex(input)<< "\n";
}

void lexPositiveIntegerAnd() {
    const std::string input("2a");
    cout<< "2 and Lexed: "<< NumberLexer::lex(input)<< "\n";
}

void lexNegativeIntegerAnd() {
    const std::string input("-1a");
    cout<< "-1 and Lexed: "<< NumberLexer::lex(input)<< "\n";
}

void lexLongPositiveIntegerAnd() {
    const std::string input("2147915791750abcdafaf");
    cout<< "2147915791750 and Lexed: "<< NumberLexer::lex(input)<< "\n";
}

void lexLongNegativeIntegerAnd() {
    const std::string input("-115710570175015015701afgag");
    cout<< "-115710570175015015701 and Lexed: "<< NumberLexer::lex(input)<< "\n";
}

void lexFloatingPointZeroAnd() {
    const std::string input("0.0a");
    cout<< "0.0 and Lexed: "<< NumberLexer::lex(input)<< "\n";
}

void lexLongerFloatingPointZeroAnd() {
    const std::string input("0.0000ava");
    cout<< "0.0000 and Lexed: "<< NumberLexer::lex(input)<< "\n";
}

void lexPositiveFloatingPointAnd() {
    const std::string input("100.3gwg");
    cout<< "100.3 and Lexed: "<< NumberLexer::lex(input)<< "\n";
}

void lexNegativeFloatingPointAnd() {
    const std::string input("-1101.0e.");
    cout<< "-1101.0 and Lexed: "<< NumberLexer::lex(input)<< "\n";
}

void lexLongPositiveFloatingPointAnd() {
    const std::string input("214.7915791750mlamf.");
    cout<< "214.7915791750 and Lexed: "<< NumberLexer::lex(input)<< "\n";
}

void lexLongNegativeFloatingPointAnd() {
    const std::string input("-115.710570175015015701afgag");
    cout<< "-115.710570175015015701 and Lexed: "<< NumberLexer::lex(input)<< "\n";
}

void lexEndingWithDot() {
    const std::string input("-115.");
    cout<< "-115. Lexed: "<< NumberLexer::lex(input)<< "\n";
}

void lexEndingWithDotAnd() {
    const std::string input("-115.adfa");
    cout<< "-115. and Lexed: "<< NumberLexer::lex(input)<< "\n";
}

void lexTwoMinus() {
    const std::string input("--1");
    cout<< "--1 Lexed: "<< NumberLexer::lex(input)<< "\n";
}

void lexMinusDot() {
    const std::string input("-.123afaf");
    cout<< "-.123afaf and Lexed: "<< NumberLexer::lex(input)<< "\n";
}

void lexTwoDotsTogether() {
    const std::string input("1..afaf");
    cout<< "1..afaf and Lexed: "<< NumberLexer::lex(input)<< "\n";
}

template<typename T>
void print(const std::vector<T>& vec) {
    cout<< "Printing vector: ";
    for (const auto& element : vec) {
        cout<< element << ", ";
    }
    cout<< "\n";
}



void lexEverything() {
    print(Lexer::lex("1.0null4.3true\"wow, lol.g agnonn\"false"));
    print(Lexer::lex("1.0null4.3truefalse\"wow, lol.g agnonn\""));
    print(Lexer::lex("\"wow, lol.g agnonn\"1.04.3true\"wow, lol.g agnonn\"falsenull"));
    print(Lexer::lex("1.0null4.3true\"wow, lol.g agnonn\"falsetrue"));
}

void TestClass::runAllTests() {
    lexString();
    lexEmptyString();
    lexStringNegative();
    lexTrue();
    lexFalse();
    lexTrueAnd();
    lexFalseAnd();
    lexBoolNegative();
    lexNull();
    lexNullAnd();
    lexNullNegative();
    lexZero();
    lexPositiveInteger();
    lexNegativeInteger();
    lexLongPositiveInteger();
    lexLongNegativeInteger();
    lexFloatingPointZero();
    lexLongerFloatingPointZero();
    lexPositiveFloatingPoint();
    lexNegativeFloatingPoint();
    lexLongPositiveFloatingPoint();
    lexLongNegativeFloatingPoint();
    lexZeroAnd();
    lexPositiveIntegerAnd();
    lexNegativeIntegerAnd();
    lexLongPositiveIntegerAnd();
    lexLongNegativeIntegerAnd();
    lexFloatingPointZeroAnd();
    lexLongerFloatingPointZeroAnd();
    lexPositiveFloatingPointAnd();
    lexNegativeFloatingPointAnd();
    lexLongPositiveFloatingPointAnd();
    lexLongNegativeFloatingPointAnd();
    lexEndingWithDot();
    lexEndingWithDotAnd();
    lexTwoMinus();
    lexMinusDot();
    lexTwoDotsTogether();
    lexEverything();
}
