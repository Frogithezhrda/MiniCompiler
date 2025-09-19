#include "Parser.h"

Parser* Parser::instance = nullptr;

std::map<TokenType, std::function<int(int, int)>> opMap = { {TokenType::PLUS, [](int x, int y) { return x + y; }},
    {TokenType::MINUS, [](int x, int y) { return x - y; }}, {TokenType::MULTIPLY, [](int x, int y) { return x * y; }}, {TokenType::DIVIDE, [](int x, int y) { 
        if (y == 0) throw IndentationException("Division by zero");
        return x / y; }} };


std::map<TokenType, int> orderMap = { {TokenType::PLUS, 1},
    {TokenType::MINUS, 1}, {TokenType::MULTIPLY, 2}, {TokenType::DIVIDE, 2} };

void Parser::parseLine(TokenLine& tokenLine)
{
    std::vector<int*> values;
    std::vector<std::pair<TokenType, std::pair<int, int>>> operationPairs;

    while (!tokenLine.tokens.empty())
    {   
        Token token = tokenLine.tokens.front();
        tokenLine.tokens.pop();
        // 1 + 2 * 3
        if (token.type == TokenType::NUMBER)
        {
            values.push_back(new int(std::stoi(token.value)));
            std::cout << token.value;
        }
        else if (token.type == TokenType::PLUS || token.type == TokenType::MINUS || token.type == TokenType::MULTIPLY || token.type == TokenType::DIVIDE)
        {
            if (values.empty())
            {
                throw IndentationException("Expression cannot start with an operator");
            }
            if (tokenLine.tokens.empty() || tokenLine.tokens.front().type != TokenType::NUMBER)
            {
                throw IndentationException("Operator must be followed by a number");
            }
            std::cout << " " << token.value << " ";
            values.push_back(new int(std::stoi(tokenLine.tokens.front().value)));
            std::cout << tokenLine.tokens.front().value;
            int currentSize = values.size();
            operationPairs.push_back({ token.type , {currentSize - 2, currentSize - 1} });
            tokenLine.tokens.pop();
        }
        else if (token.type == TokenType::TYPE)
        {
            if (token.value == "skipNumber")
            {

            }
            else if (token.value == "skipHalf")
            {

            }
            else if (token.value == "skipWord")
            {

            }
        }
    }
    std::sort(operationPairs.begin(), operationPairs.end(),
        [](const auto& a, const auto& b) {
            return orderMap[a.first] > orderMap[b.first];
        });

    for (auto& operation : operationPairs)
    {
        int* firstNumber = values[operation.second.first];
        int* secondNumber = values[operation.second.second];

        int* answer = new int(applyOperator(*firstNumber, *secondNumber, operation.first));

        for (int*& ptr : values)
        {
            if (ptr == firstNumber || ptr == secondNumber)
            {
                ptr = answer;
            }
        }

        if (firstNumber != secondNumber) 
        {
            delete firstNumber;
            delete secondNumber;
        }
        else //if they are the same pointer we must delete once because then error! 
        {
            delete firstNumber; 
        }
    }
    operationPairs.clear();
    std::cout << " = " << *values.front() << ";" << std::endl;


    //we must use an unoredered set because we cant delete the same value
    delete values.front();
    values.clear();
}

Parser* Parser::getInstance()
{
    if (instance == nullptr) 
    {
        instance = new Parser();
    }
    return instance;
}

Parser::Parser() {}


double Parser::applyOperator(const int a, const int b, const TokenType op)
{
    return opMap[op](a, b);
}

void Parser::parseOperators(const Token& currentToken, std::vector<double>& values, TokenLine& tokenLine)
{
}