/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SnakeGame.hpp
*/

#pragma once

#include "../../../src/IGameModule.hpp"
#include <iostream>
#include <chrono>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>

enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

enum SnakePart {
    Head,
    Body,
    Tail,
    BodyTurn
};

struct SnakeSegment {
    std::string spritePath;
    char asciiSprite;
    int gridX;
    int gridY;
    float width;
    float height;
    SnakePart part;
    Direction direction;
};

struct Fruit {
    int gridX;
    int gridY;
    std::string spritePath;
};

class SnakeGame : public IGameModule {
    private:
        std::string _name;
        int _score;
        std::vector<Elements> _map;
        std::vector<std::string> _graphicLibs;
        std::vector<std::string> _gameLibs;
        int _indexDisplayList;
        std::vector<SnakeSegment> _snake;
        std::vector<Fruit> _fruits;
        Direction _snakeDirection;
        int _gridSize;
        int _gridWidth;
        int _gridHeight;
        std::chrono::steady_clock::time_point _lastUpdate;
        std::chrono::milliseconds _updateInterval{100};
        std::string headSpriteForDirection(Direction direction);
        std::string bodySpriteForDirection(Direction direction);
        std::string tailSpriteForDirection(Direction direction);
        bool _endGame;

        void rebuildMap();
        bool checkAppleCollision(int x, int y);
        void addApple();
        void addSegment();
        void checkCollisions();
        void updateSnakeSegmentSprites();
        void updateSnakeSegment(SnakeSegment& segment, size_t index);
        void endGame();
        bool isNewHighScore();

    public:
        SnakeGame();
        ~SnakeGame() override;

        int update(std::vector<keys>& events) override;
        int getScore() override;
        void setName(const std::string& name) override;
        const std::string getName() override;
        std::vector<Elements>& getMap() override;
        void setLibs(std::vector<std::string> gameLibs, std::vector<std::string> graphicLibs, int indexDisplayList) override;
};
