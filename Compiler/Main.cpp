#include "Lexer.h"

constexpr const int ARG_COUNT = 3;

int main(int argc, char** argv)
{
	if (ARG_COUNT != argc)
	{
		std::cout << "Need Output And Input File";
	}
	else
	{
		try
		{
			Lexer lexer(std::make_shared<FileHandler>(argv[1], argv[2]));
			std::cout << "Compiled!";
		}
		catch (const std::exception& exception)
		{
			std::cerr << exception.what();
		}
	}
}