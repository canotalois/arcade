/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** ErrorHandling
*/

#include "ErrorHandling.hpp"

ErrorHandling::Error::Error(const std::string& errorMsg, const std::string& errorWhereMsg) : _errorMsg(errorMsg), _errorWhereMsg(errorWhereMsg)
{
}

const char* ErrorHandling::Error::what() const noexcept
{
    return (this->_errorMsg.c_str());
}

const char* ErrorHandling::Error::where() const noexcept
{
    return (this->_errorWhereMsg.c_str());
}
