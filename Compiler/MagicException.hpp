#pragma once
#include <exception>
#include <string>
#include <iostream>

class MagicException : public std::exception
{
public:

    MagicException(const std::string& message)
    {
        this->m_message = "Signature Error: " + message + "\n";
    }

    virtual char const* what() const throw()
    {
        return m_message.c_str();
    }
private:
    std::string m_message;
};