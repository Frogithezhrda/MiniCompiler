#include "FileHandler.h"


FileHandler::FileHandler(const std::string& outputFile, const std::string& inputFile)
{
	this->m_inputFile = std::ifstream(inputFile);
	this->m_outputFile = std::ofstream(outputFile);
	if (!m_outputFile || !m_inputFile) throw FileException("Couldn't Open One Of The Files!");
	this->m_currentIndex = 0;
	readLines();
}

FileHandler::~FileHandler()
{
	this->m_inputFile.close();
	this->m_outputFile.close();
}

bool FileHandler::endLine() const
{
	return peekChar() == END_LINE;
}

std::queue<std::string> FileHandler::getLines() const
{
	return m_lines;
}

char FileHandler::peekChar() const
{
	if (m_lines.empty()) throw EOFException("Reached end of file");

	std::string line = m_lines.front();

	if (m_currentIndex >= line.size() && !line.empty()) throw IndentationException("Must End With ;");

	return line[m_currentIndex];
}

std::string FileHandler::peekLine() const
{
	return !m_lines.empty() ? m_lines.front() : throw EOFException("EOF Defention Not In Must End with ;");
}

char FileHandler::nextChar()
{
	char value = peekChar();
	if (endLine())
	{
		nextLine();
	}
	m_currentIndex++;
	return value;
}

std::string FileHandler::nextLine()
{
	std::string line = m_lines.front();
	m_currentIndex = 0;
	m_lines.pop();
	return line;
}

void FileHandler::readLines()
{
	std::string line;
	while (std::getline(m_inputFile, line))
	{ 
		m_lines.push(line);
	}
}
