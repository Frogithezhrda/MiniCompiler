#pragma once

#include "Token.h"
#include <functional>
#include <map>
#include "IndentationException.hpp"
#include <unordered_set>
#include <variant>


enum class VarType 
{
	Number,
	Half,
	Word
};

using Value = std::variant<int, float, std::string>;

struct Variable
{
	VarType type;
	std::string name;
	Value value;
};

class Parser
{
public:
	void parseLine(TokenLine& tokenLine);
	static Parser* getInstance();
private:
	Parser();
	double applyOperator(const int a, const int b, const TokenType op);
	Parser(const Parser&) = delete;
	Parser& operator=(const Parser&) = delete;

	std::unordered_map<std::string, Variable> m_variables;
	static Parser* instance;
};