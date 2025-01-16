/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** DisplayModule.cpp
*/

#include "DisplayModule.hpp"

DisplayModule::DisplayModule()
{
    std::cout << "DisplayModule initialized." << std::endl;
}

void DisplayModule::render(std::vector<Elements>& map)
{
    (void) map;
    std::cout << "DisplayModule rendered." << std::endl;
}

std::vector<keys>& DisplayModule::getEvents()
{
    std::vector<keys> events;
    return events;
}

void DisplayModule::displayPlayerName(const std::string& name)
{
    std::cout << "Username: " << name << std::endl;
}

void DisplayModule::displayPlayerScore(int score)
{
    std::cout << "Score: " << score << std::endl;
}

DisplayModule::~DisplayModule()
{
    std::cout << "DisplayModule stopped." << std::endl;
}
