/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** AGameModule.hpp
*/

#pragma once
#include "IGameModule.hpp"
#include <iostream>

class AGameModule : public IGameModule {
    private:
        std::vector<Elements> _map;
        std::vector<std::string> _graphicLibs;
        std::vector<std::string> _gameLibs;
        int _indexDisplayList;
    public:
        AGameModule();
        ~AGameModule() override;
        int update(std::vector<keys>& events) override; // Met à jour le jeu // Appelé dans la game loop de Core
        int getScore() override;
        void setName(const std::string& name) override;
        const std::string getName() override;
        std::vector<Elements>& getMap() override;
        void setLibs(std::vector<std::string> gameLibs, std::vector<std::string> graphicLibs, int indexDisplayList) override;
};
