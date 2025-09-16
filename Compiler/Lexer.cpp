#include "Lexer.h"

Token Lexer::nextToken()
{
	return Token();
}

bool Lexer::isDigit(char c)
{
	return false;
}

bool Lexer::isAlpha(char c)
{
	return false;
}

bool Lexer::isAlnum(char c)
{
	return false;
}

void Lexer::skipWhitespace()
{
}

Token Lexer::readNumber()
{
	Token token;
	token.type = TokenType::NUMBER;
	token.value
	return Token();
}

Token Lexer::readIdentifier()
{
	return Token();
}
