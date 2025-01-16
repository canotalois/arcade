/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Core.hpp
*/

#pragma once
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"
#include "DLLloader.hpp"
#include <vector>
#include <memory>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include "ErrorHandling.hpp"

class Core {
    private:
        std::unique_ptr<IDisplayModule> _displayModule; // Création du module display
        std::unique_ptr<IGameModule> _gameModule; // Création du module game
        std::unique_ptr<DLLoader> _gameLoader;
        std::unique_ptr<DLLoader> _displayLoader;

        bool _isRunning; // Booléan indiquant si l'arcade est en train de tourner
        std::vector<std::string> _gameList;
        std::vector<std::string> _graphicLibList;
        std::string _userName;
        std::string _currentScore;
        size_t _indexLibGraphic;
        size_t _indexLibGame;


    public:
        Core(const std::string &graphicPath, const std::string &menuPath); // Constructor
        ~Core(); // Destructor
        void run(); // Launcher de la boucle de l'arcade
        void switchGame(); // Changeur de lib de jeu
        void switchDisplay(); // Changeur de lib graphique
        void switchToMenu();
        void setGameList(const std::string &newgame);
        void setGraphicList(const std::string &newlib);
        std::vector<std::string> getGameList();
        std::vector<std::string> getGraphicList();
        std::string getDisplayPath() {
            return _graphicLibList[_indexLibGraphic];
        }
        std::string getGamePath() {
            return _gameList[_indexLibGame];
        }
};
