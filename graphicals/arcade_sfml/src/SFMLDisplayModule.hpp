/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SFMLDisplayModule.hpp
*/

#pragma once

#include "../../../src/IDisplayModule.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class SFMLDisplayModule : public IDisplayModule {
    private:
        sf::RenderWindow window;
        sf::Font _font;
        sf::Text _playerNameText;
        sf::Text _playerScoreText;
        std::vector<keys> _events;
        std::string _userName;
        int _userScore;
    public:
        SFMLDisplayModule();
        ~SFMLDisplayModule() override;
        void render(std::vector<Elements>& map) override;
        std::vector<keys>& getEvents() override;
        void displayPlayerName(const std::string& name) override;
        void displayPlayerScore(int score) override;
};
