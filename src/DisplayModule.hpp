/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** DisplayModule.hpp
*/

#pragma once
#include "IDisplayModule.hpp"
#include <iostream>

class DisplayModule : public IDisplayModule {
    public:
        DisplayModule();
        ~DisplayModule() override;
        void render(std::vector<Elements>& map) override;
        std::vector<keys>& getEvents() override;
        void displayPlayerName(const std::string& name) override;
        void displayPlayerScore(int score) override;
};
