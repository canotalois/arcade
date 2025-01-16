/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** AGameModule.cpp
*/

#include "AGameModule.hpp"

AGameModule::AGameModule()
{
    std::cout << "AGameModule initialized." << std::endl;
}

int AGameModule::update(std::vector<keys>& events)
{
    (void) events;
    return (-1);
}

int AGameModule::getScore()
{
    return -1;
}

void AGameModule::setName(const std::string& name)
{
    (void) name;
}

const std::string AGameModule::getName()
{
    return "NULL";
}

std::vector<Elements>& AGameModule::getMap()
{
//    std::vector<Elements> map;
//    return map;
    return _map;
}

void AGameModule::setLibs(std::vector<std::string> gameLibs, std::vector<std::string> graphicLibs, int indexDisplayList)
{
    this->_gameLibs = gameLibs;
    this->_graphicLibs = graphicLibs;
    this->_indexDisplayList = indexDisplayList;
}

AGameModule::~AGameModule()
{
    std::cout << "AGameModule stopped." << std::endl;
}
