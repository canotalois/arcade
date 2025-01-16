/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** ErrorHandling
*/

#pragma once
#include <stdexcept>
#include <iostream>

class ErrorHandling {
    public:
        class Error : public std::exception {
            private:
                std::string _errorMsg;
                std::string _errorWhereMsg;
            public:
                Error(const std::string& errorMsg = "", const std::string& errorWhereMsg = "");
                const char* what() const noexcept;
                const char* where() const noexcept;
        };
};
