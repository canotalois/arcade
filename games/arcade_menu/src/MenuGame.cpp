/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** MenuGame.cpp
*/

#include "./MenuGame.hpp"

MenuGame::MenuGame()
{
    _isSelectingGame = true;
    _isSelectingDisplay = false;
    _isWritingUserName = false;
    _actualGameIndex = 0;
    getHighScore("highScore.txt");
}

std::vector<Elements>& MenuGame::getMap()
{
    return _map;
}

int MenuGame::getScore()
{
    return _score;
}

void MenuGame::getHighScore(const std::string& path)
{
    std::ifstream file(path);
    int highScore = 0;

    if (file.is_open()) {
        std::string line;
        if (std::getline(file, line)) {
            std::istringstream iss(line);
            iss >> highScore;
        }
        file.close();
    } else {
        std::cerr << "Impossible d'ouvrir le fichier : " << path << std::endl;
    }

    _score = highScore;
}
void MenuGame::setName(const std::string& name)
{
    _name = name;
}

const std::string MenuGame::getName()
{
    return _name;
}

int MenuGame::update(std::vector<keys>& events)
{
    for (auto event : events) {
        switch (event) {
            case DOWN_ARROW:
                if (_isSelectingDisplay == true) {
                    if (_acutalDisplayIndex < _graphicLibs.size() - 1)
                        _acutalDisplayIndex++;
                    return 10;
                }
                if (_isSelectingGame == true) {
                    if (_actualGameIndex < (_gameLibs.size() - 1))
                        _actualGameIndex++;
                    return 11;
                }
                break;
            case UP_ARROW:
                if (_isSelectingDisplay == true) {
                    if (_acutalDisplayIndex > 0)
                        _acutalDisplayIndex--;
                    return 12;
                }
                if (_isSelectingGame == true) {
                    if (_actualGameIndex > 0)
                        _actualGameIndex--;
                    return 13;
                }
                break;
            case RIGHT_ARROW:
                if (_isSelectingGame == true) {
                    _isSelectingGame = false;
                    _isSelectingDisplay = true;
                    break;
                } else if (_isSelectingDisplay == true) {
                    _isSelectingDisplay = false;
                    _isWritingUserName = true;
                    break;
                }
                break;
            case LEFT_ARROW:
                if (_isWritingUserName == true) {
                    _isWritingUserName = false;
                    _isSelectingDisplay = true;
                    break;
                } else if (_isSelectingDisplay == true) {
                    _isSelectingDisplay = false;
                    _isSelectingGame = true;
                    break;
                }
                break;
            case KEY_ENTER:
                if (_isSelectingDisplay == true)
                    return 7;
                if (_isSelectingGame == true)
                    return 3;
                break;
            case KEY_P:
                return 1;
            case KEY_A:
                return 15;
            default: break;
        }
    }
    this->reBuildMap();
    return 0;
}

void MenuGame::reBuildMap()
{

    _map.clear();
    int xPosGame = 30;
    int xPosDisplay = 400;
    int y = 60;
    int space = 50;

    _map.push_back({"", ' ', xPosGame, y, 1.0f, 1.0f, "Available games :"});
    _map.push_back({"", ' ', xPosDisplay, y, 1.0f, 1.0f, "Available graphic libs :"});
    for (size_t i = 0; i < _gameLibs.size(); ++i) {
        int newY = y + (i + 1) * space;
        if (i == _actualGameIndex && _isSelectingGame == true)
            _map.push_back({"", ' ', xPosGame, newY, 1.0f, 1.0f, _gameLibs[i] + "  X"});
        else 
            _map.push_back({"", ' ', xPosGame, newY, 1.0f, 1.0f, _gameLibs[i]});

    }
    for (size_t i = 0; i < _graphicLibs.size(); ++i) {
        int newY = y + (i + 1) * space;
        if (i == _acutalDisplayIndex && _isSelectingDisplay == true) 
            _map.push_back({"", ' ', xPosDisplay, newY, 1.0f, 1.0f, _graphicLibs[i] + "  X"});
        else 
            _map.push_back({"", ' ', xPosDisplay, newY, 1.0f, 1.0f, _graphicLibs[i]});
    }
}

void MenuGame::setLibs(std::vector<std::string> gameLibs, std::vector<std::string> graphicLibs, int indexDisplayList)
{
    this->_gameLibs = gameLibs;
    this->_graphicLibs = graphicLibs;
    this->_indexDisplayList = indexDisplayList;
    _acutalDisplayIndex = indexDisplayList;
}

MenuGame::~MenuGame()
{
    _map.clear();
    std::cout << "Menu détruit" << std::endl;
}

extern "C" IGameModule* createGameModule()
{
    return new MenuGame();
}