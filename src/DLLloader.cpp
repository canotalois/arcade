/*
** EPITECH PROJECT, 2023
** arcadebootstrap
** File description:
** DLLoader.cpp
*/

#include "./DLLloader.hpp"

bool DLLoader::checkSymbol(const std::string &symbol)
{
    void *sym = dlsym(_handle, symbol.c_str());

    if (sym != nullptr)
        return true;
    
    return false;
}

DLLoader::DLLoader(const std::string &path)
{
    void *handle = dlopen(path.c_str(), RTLD_LAZY);

    if (!handle) {
        throw ErrorHandling::Error("Invalid file while loading libraries : " + path, "");
    }

    this->_handle = handle;
}

DLLoader::~DLLoader()
{
    if (this->_handle) {
        dlclose(_handle);
    }
}