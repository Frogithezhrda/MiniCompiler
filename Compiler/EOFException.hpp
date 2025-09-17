#pragma once
#include <exception>
#include <string>
#include <iostream>

class EOFException : public std::exception
{
public:

    EOFException(const std::string& message)
    {
        this->m_message = "EOF Error: " + message + "\n";
    }

    virtual char const* what() const throw()
    {
        return m_message.c_str();
    }
private:
    std::string m_message;
};