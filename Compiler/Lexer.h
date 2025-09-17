#pragma once

#include "FileHandler.h"
#include <iostream>
#include "MagicException.hpp"
#include "IndentationException.hpp"

enum class TokenType { NUMBER, IDENTIFIER, PLUS, MINUS, MULTIPLY, DIVIDE, ASSIGN, SEMICOLON, LPAREN, RPAREN, IF, ELSE, WHILE, EOF_TOKEN, INVALID };

struct Token 
{ 
	TokenType type; 
	std::string value; 
};

constexpr const char* START_SIGNATURE = "#SKIPPY";
constexpr const char* END_SIGNATURE = "#SKIP";

class Lexer 
{ 
public:
	Lexer(const std::shared_ptr<FileHandler> handler);

	Token nextToken() const;
	void skipBlank() const;
	Token readNumber() const;
	Token readIdentifier() const;
	bool readMagic() const;
private:
	std::shared_ptr<FileHandler> m_fileHandler;
};
