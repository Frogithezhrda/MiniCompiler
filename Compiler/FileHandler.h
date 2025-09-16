#pragma once
#include <iostream>
#include <fstream>
#include <queue>
#include <string>

class FileHandler
{
public:
	FileHandler(const std::string& outputFile, const std::string& inputFile);
	~FileHandler();

	std::queue<std::string> getLines() const;

private:
	std::ofstream m_outputFile;
	std::ifstream m_inputFile;
	std::queue<std::string> m_lines;
	

	void readLines();
};
