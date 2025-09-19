#pragma once

#include "FileHandler.h"
#include <iostream>
#include "MagicException.hpp"
#include "IndentationException.hpp"
#include <map>
#include "Token.h"
#include "Parser.h"

class Parser;


constexpr const char* START_SIGNATURE = "#SKIPPY";

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
	bool isOperator(const char character) const;
};
