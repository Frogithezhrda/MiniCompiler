#include "FileHandler.h"


FileHandler::FileHandler(const std::string& outputFile, const std::string& inputFile)
{
	this->m_inputFile = std::ifstream(inputFile);
	this->m_outputFile = std::ofstream(outputFile);

	readLines();
}

FileHandler::~FileHandler()
{
	this->m_inputFile.close();
	this->m_outputFile.close();
}

std::queue<std::string> FileHandler::getLines() const
{
	return m_lines;
}

void FileHandler::readLines()
{
	std::string line;
	while (std::getline(m_inputFile, line))
	{ 
		m_lines.push(line);
	}
}
