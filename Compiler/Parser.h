#pragma once

#include "Token.h"
#include <functional>
#include <map>
#include "IndentationException.hpp"
#include <unordered_set>

class Parser
{
public:
	void parseLine(TokenLine& tokenLine);
	static Parser* getInstance();
private:
	Parser();
	double applyOperator(const int a, const int b, const TokenType op);
	void parseOperators(const Token& currentToken, std::vector<double>& values, TokenLine& tokenLine);
	Parser(const Parser&) = delete;
	Parser& operator=(const Parser&) = delete;


	static Parser* instance;
};