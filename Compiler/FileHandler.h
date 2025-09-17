#pragma once
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include "FileException.hpp"
#include "EOFException.hpp"
#include "IndentationException.hpp"

constexpr const char END_LINE = ';';

class FileHandler
{
public:
	FileHandler(const std::string& outputFile, const std::string& inputFile);
	~FileHandler();

	bool endLine() const;
	std::queue<std::string> getLines() const;
	char peekChar() const;
	std::string peekLine() const;

	char nextChar();
	std::string nextLine();
private:
	std::ofstream m_outputFile;
	std::ifstream m_inputFile;
	std::queue<std::string> m_lines;
	int m_currentIndex;

	void readLines();
};
