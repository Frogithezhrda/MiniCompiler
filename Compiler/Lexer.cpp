#include "Lexer.h"

Lexer::Lexer(const std::shared_ptr<FileHandler> handler)
{
	Token token;
	TokenLine tokenLine;
	m_fileHandler = handler;
	if (!readMagic())
	{
		throw MagicException("Not A Skippy File!");
	}
	while (token.type != TokenType::EOF_TOKEN)
	{
		token = nextToken();
		if (token.type == TokenType::SEMICOLON)
		{
			Parser::getInstance()->parseLine(tokenLine);
			tokenLine = TokenLine();
			continue;
		}
		tokenLine.tokens.push(token);
	}
}

Token Lexer::nextToken() const
{
	Token token;
	std::map<char, TokenType> tokenMap = { {'+', TokenType::PLUS}, {'-', TokenType::MINUS}, {'*', TokenType::MULTIPLY}, {'/', TokenType::DIVIDE} };
	try
	{
		skipBlank();
		token.value = std::string().empty();

		char currentChar = m_fileHandler->peekChar();
		if (std::isdigit(currentChar))  
		{
			return readNumber();
		}
		else if (std::isalpha(currentChar))  
		{
			return readIdentifier();
		}
		else if(m_fileHandler->endLine())
		{
			m_fileHandler->nextLine();
			token.type = TokenType::SEMICOLON;
			return token;
		}
		else if (isOperator(currentChar))
		{

			m_fileHandler->nextChar();
			skipBlank();

			char nextChar = m_fileHandler->peekChar();

			token.type = tokenMap[currentChar];
			token.value = currentChar;
			if (m_fileHandler->endLine() || nextChar == '\0')
			{
				throw IndentationException("Operator and after that an ; is forbidden!");
			}

			return token;
		}
	}
	catch (const EOFException&)
	{
		token.type = TokenType::EOF_TOKEN;
		return token;
	}
	throw IndentationException("Cannot Read That Type of Character!");
}

void Lexer::skipBlank() const
{
	while (m_fileHandler->peekChar() == '\n' || m_fileHandler->peekChar() == '\0')
	{
		m_fileHandler->nextLine();  
	}
	while (m_fileHandler->peekChar() == ' ')
	{
		m_fileHandler->nextChar();
	}
}


Token Lexer::readNumber() const
{
	std::string value;
	Token token;
	while (std::isdigit(m_fileHandler->peekChar()) && !m_fileHandler->endLine())  
	{
		value += m_fileHandler->nextChar();
	}
	token.type = TokenType::NUMBER;
	token.value = value;
	return token;
}

Token Lexer::readIdentifier() const
{
	std::string value;
	Token token;
	while (std::isalnum(m_fileHandler->peekChar()) || m_fileHandler->peekChar() == '_')
	{
		value += m_fileHandler->nextChar();
	}
	token.type = TokenType::IDENTIFIER;
	if (value == "skipNumber" || value == "skipHalf" || value == "skipWord")
	{
		token.type = TokenType::TYPE;
	}
	token.value = value;
	return token;
}

bool Lexer::readMagic() const
{
	if(m_fileHandler->peekLine() == START_SIGNATURE)
	{
		m_fileHandler->nextLine();
		return true;
	}
	return false;
}

bool Lexer::isOperator(const char character) const
{
	return character == '+' || character == '-' || character == '*' || character == '/';
}
