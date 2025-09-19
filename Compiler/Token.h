#pragma once

#include <string>
#include <queue>
#include <vector>
#include <iostream>

enum TokenType 
{
    NUMBER, IDENTIFIER, PLUS, MINUS, MULTIPLY, DIVIDE,
    ASSIGN, SEMICOLON, TYPE,
    IF, ELSE, WHILE, EOF_TOKEN, INVALID
};

struct Token 
{
    TokenType type;
    std::string value;
};

struct TokenLine 
{
    std::queue<Token> tokens;
};
