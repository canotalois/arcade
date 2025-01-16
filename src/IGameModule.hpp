/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** IGameModule.hpp
*/

#pragma once
#include "IDisplayModule.hpp"
#include <vector>

class IGameModule {
    public:
        virtual ~IGameModule() = default;

        // Mise à jour et rendu du jeu
        virtual int update(std::vector<keys>& events) = 0; // Met à jour le jeu // Appelé dans la game loop de Core
        virtual int getScore() = 0;
        virtual void setName(const std::string& name) = 0;
        virtual const std::string getName() = 0;
        virtual std::vector<Elements>& getMap() = 0;
        virtual void setLibs(std::vector<std::string> gameLibs, std::vector<std::string> graphicLibs, int indexDisplayList) = 0;
};
