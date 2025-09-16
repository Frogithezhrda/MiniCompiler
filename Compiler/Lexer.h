#pragma once

#include <iostream>

enum class TokenType { NUMBER, IDENTIFIER, PLUS, MINUS, MULTIPLY, DIVIDE, ASSIGN, SEMICOLON, LPAREN, RPAREN, IF, ELSE, WHILE, EOF_TOKEN, INVALID };
struct Token { TokenType type; std::string value; int line, column; };

class Lexer 
{ 
private:
	std::string input;
	int position; 
	int line;
	int column;
public:
	Token nextToken();
	bool isDigit(char c); 
	bool isAlpha(char c); 
	bool isAlnum(char c);
	void skipWhitespace(); 
	Token readNumber(); 
	Token readIdentifier(); 
};
