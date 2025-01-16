/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Core.cpp
*/

#include "Core.hpp"

Core::Core(const std::string &graphicPath, const std::string &menuPath)
{
    // loads libraries and verify graphicLib
    this->_isRunning = false;
    this->_displayLoader = std::make_unique<DLLoader>(graphicPath);

    if (!_displayLoader->checkSymbol("createDisplayModule"))
        throw ErrorHandling::Error("Invalid file." ,"");

    this->_gameLoader = std::make_unique<DLLoader>(menuPath);
    _gameModule.reset(_gameLoader->getInstance<IGameModule>("createGameModule"));
    _displayModule.reset(_displayLoader->getInstance<IDisplayModule>("createDisplayModule"));


    // fill and update vectors and index
    for (const auto & entry : std::filesystem::directory_iterator("./lib")) {
        try {
            DLLoader loader(entry.path().string());
            if (loader.checkSymbol("createGameModule"))
                setGameList(entry.path().string());
            else if (loader.checkSymbol("createDisplayModule"))
                setGraphicList(entry.path().string());
            else
                std::cerr << "Invalid file :" << entry.path().string() << std::endl;
        } catch (const std::runtime_error &e) {
            try {
                DLLoader loader(entry.path().string());
                std::unique_ptr<IDisplayModule> libModule(loader.getInstance<IDisplayModule>("createDisplayModule"));
            } catch (const std::runtime_error &e) {
                std::cerr << "Invalid file. : " << entry.path().string() << std::endl;
                }
            }
    }
    for (unsigned int i = 0; i < _graphicLibList.size(); i++) {
        if (_graphicLibList[i] == graphicPath || _graphicLibList[i] == "./" + graphicPath) {
            _indexLibGraphic = i;
            break;
        }
    }
    for (unsigned int i = 0; i < _gameList.size(); i++) {
        if (_gameList[i] == menuPath || _gameList[i] == "./" + menuPath) {
            _gameList.erase(_gameList.begin() + i);
            break;
        }
    }
    _indexLibGame = 0;

}

Core::~Core()
{
    _isRunning = false;
    _displayModule.reset();
    _displayLoader.reset();
    _gameModule.reset();
    _gameLoader.reset();
}

std::vector<std::string> Core::getGameList()
{
    return this->_gameList;
}
std::vector<std::string> Core::getGraphicList()
{
    return this->_graphicLibList;
}

void Core::setGameList(const std::string &newgame)
{
    this->_gameList.push_back(newgame);
}

void Core::setGraphicList(const std::string &newlib)
{
    this->_graphicLibList.push_back(newlib);
}

void Core::switchToMenu()
{
    _gameModule.reset();
    _gameLoader.reset();

    _gameLoader.reset(new DLLoader("./lib/arcade_menu.so"));
    _gameModule.reset(_gameLoader->getInstance<IGameModule>("createGameModule")); // load la nouvelle instance dans le pointeur
    
}

void Core::run()
{
    _isRunning = true;
    while (_isRunning) {
        if (_displayModule && _gameModule) {
            _gameModule->setLibs(this->_gameList, this->_graphicLibList, this->_indexLibGraphic);
//            _displayModule->displayPlayerName(_gameModule->getName());
            _displayModule->displayPlayerName("Golbut");
            _displayModule->displayPlayerScore(_gameModule->getScore());
            int updateRet = _gameModule->update(_displayModule->getEvents());
            if (updateRet == 1) {
                _indexLibGraphic++;
                if (_indexLibGraphic > (_graphicLibList.size() -1))
                    _indexLibGraphic = 0;
                switchDisplay();
            };
            if (updateRet == 2)
                switchToMenu();
            if (updateRet == 3)
                switchGame();
            if (updateRet == 4) {
                _indexLibGame++;
                if (_indexLibGame > (_gameList.size() - 1))
                    _indexLibGame = 0;
                switchGame();
            }
            if (updateRet == 7)
                switchDisplay();
            if (updateRet == 10) {
                if (_indexLibGraphic < (_graphicLibList.size() -1))
                    _indexLibGraphic++;
            }
            if (updateRet == 11) {
                if (_indexLibGame < (_gameList.size() -1))
                    _indexLibGame++;
            }
            if (updateRet == 12) {
                if (_indexLibGraphic > 0)
                    _indexLibGraphic--;
            }
            if (updateRet == 13) {
                if (_indexLibGame > 0)
                    _indexLibGame--;
            }
            if (updateRet == 15) {
                _isRunning = false;
            }


            _displayModule->render(_gameModule->getMap());
        }
    }
}

void Core::switchGame()
{
    _gameModule.reset();
    _gameLoader.reset();

    _gameLoader.reset(new DLLoader(getGamePath()));
    _gameModule.reset(_gameLoader->getInstance<IGameModule>("createGameModule")); // load la nouvelle instance dans le pointeur
    
}


void Core::switchDisplay()
{
    //free le loader et la lib utilisé
    _displayModule.reset();
    _displayLoader.reset();


    //update la lib graphique
    _displayLoader.reset(new DLLoader(getDisplayPath()));
    _displayModule.reset(_displayLoader->getInstance<IDisplayModule>("createDisplayModule"));
    
}
