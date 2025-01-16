/*
** EPITECH PROJECT, 2023
** arcadebootstrap
** File description:
** DLLoader.hpp
*/

#pragma once

#include <iostream>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include "ErrorHandling.hpp"

class DLLoader {
    private:
        void *_handle;
    public:
        DLLoader(const std::string &path);
        DLLoader() : _handle(nullptr) {};
        ~DLLoader();

        bool checkSymbol(const std::string& symbol);

        template<typename T>
        T *getInstance(const std::string &symbole) {
            auto getSymbole = reinterpret_cast<T* (*)()>(dlsym(_handle, symbole.c_str()));
            const char *error = dlerror();
            if (error) {
                throw ErrorHandling::Error("Failed to load symbol", "");
            }
            return getSymbole();
        }
};