/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** MenuGame.hpp
*/

#pragma once

#include "../../../src/IGameModule.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
class MenuGame : public IGameModule {
    private:
        std::string _name;
        int _score;
        std::vector<Elements> _map;
        std::vector<std::string> _graphicLibs;
        std::vector<std::string> _gameLibs;
        size_t _indexDisplayList;
        size_t _acutalDisplayIndex;
        size_t _actualGameIndex;
        bool _isSelectingGame;
        bool _isSelectingDisplay;
        bool _isWritingUserName;
        bool _isMenuRemoved;
        void reBuildMap();
        void getHighScore(const std::string& path);
    public:
        MenuGame();
        ~MenuGame() override;

        int update(std::vector<keys>& events) override;
        int getScore() override;
        void setName(const std::string& name) override;
        const std::string getName() override;
        std::vector<Elements>& getMap() override;
        void setLibs(std::vector<std::string> gameLibs, std::vector<std::string> graphicLibs, int indexDisplayList) override;
};
