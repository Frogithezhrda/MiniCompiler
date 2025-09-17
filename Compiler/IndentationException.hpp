#pragma once
#include <exception>
#include <string>
#include <iostream>

class IndentationException : public std::exception
{
public:

    IndentationException(const std::string& message)
    {
        this->m_message = "Indentation Error: " + message + "\n";
    }

    virtual char const* what() const throw()
    {
        return m_message.c_str();
    }
private:
    std::string m_message;
};