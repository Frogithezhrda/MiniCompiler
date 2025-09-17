#include "Lexer.h"

Lexer::Lexer(const std::shared_ptr<FileHandler> handler)
{
	m_fileHandler = handler;
	if (!readMagic())
	{
		throw MagicException("Not A Skippy File!");
	}
	while (nextToken().type != TokenType::EOF_TOKEN);
}

Token Lexer::nextToken() const
{
	Token token;
	
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
	while (std::isspace(m_fileHandler->peekChar()) || m_fileHandler->peekChar() == '\0')
	{
		m_fileHandler->nextLine();  
	}
}


Token Lexer::readNumber() const
{
	std::string value;
	Token token;
	while (std::isdigit(m_fileHandler->peekChar()) || !m_fileHandler->endLine())  
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
