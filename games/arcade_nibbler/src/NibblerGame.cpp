/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** NibblerGame.cpp
*/

#include "NibblerGame.hpp"

NibblerGame::NibblerGame() : _score(0), _snakeDirection(RIGHT), _gridSize(40), _gridWidth(20), _gridHeight(15), _endGame(false), _appleAte(0), _isSnakeMoving(true)
{
    srand(time(nullptr));
    int startX = _gridWidth / 2;
    int startY = _gridHeight / 2;
    _snake.push_back({"./assets/sprites/snake_graphics/head_right.png", '@', startX, startY, 1.0f, 1.0f, Head, RIGHT});
    _snake.push_back({"./assets/sprites/snake_graphics/body_horizontal.png", 'o', startX - 1, startY, 1.0f, 1.0f, Body, RIGHT});
    _snake.push_back({"./assets/sprites/snake_graphics/body_horizontal.png", 'o', startX - 2, startY, 1.0f, 1.0f, Body, RIGHT});
    _snake.push_back({"./assets/sprites/snake_graphics/tail_left.png", '0', startX - 3, startY, 1.0f, 1.0f, Tail, RIGHT});
    addWalls();
    addRandomWalls(15);
    addApples(15);
    _startTime = std::chrono::steady_clock::now();
    std::cout << "NibblerGame initialized." << std::endl;
}

NibblerGame::~NibblerGame()
{
    std::cout << "NibblerGame destroyed." << std::endl;
}

int NibblerGame::update(std::vector<keys>& events)
{
    if (_endGame)
        return 2;
    if (_appleAte >= 15) {
        endGame(true);
    }
    auto now = std::chrono::steady_clock::now();
    if (now - _startTime >= _gameDuration) {
        if (_appleAte != 15) {
            endGame(false);
            return 2;
        }
    }
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastUpdate) >= _updateInterval) {
        if (_isSnakeMoving) {
            updateSnakeSegmentSprites();
        }
        redirectSnakeBasedOnWallCollision();
        _lastUpdate = now;
    }
    for (auto event : events) {
        switch (event) {
            case KEY_Z:
                if (_snakeDirection != DOWN) this->_snakeDirection = UP;
                break;
            case KEY_Q:
                if (_snakeDirection != RIGHT) this->_snakeDirection = LEFT;
                break;
            case KEY_S:
                if (_snakeDirection != UP) this->_snakeDirection = DOWN;
                break;
            case KEY_D:
                if (_snakeDirection != LEFT) this->_snakeDirection = RIGHT;
                break;
            case KEY_P:
                return 1;
            case KEY_O:
                return 4;
            case KEY_SPACE:
                return 3;
            case KEY_ESCAPE:
                return 2;
            case KEY_A:
                return 15;
            default: break;
        }
    }
    this->rebuildMap();
    return (0);
}

void NibblerGame::updateSnakeSegmentSprites()
{
    for (size_t i = _snake.size() - 1; i > 0; --i) {
        _snake[i].gridX = _snake[i-1].gridX;
        _snake[i].gridY = _snake[i-1].gridY;
        _snake[i].direction = _snake[i-1].direction;
        updateSnakeSegment(_snake[i], i);
    }
    _snake[0].direction = _snakeDirection;
    switch (_snakeDirection) {
        case UP: _snake[0].gridY -= 1; break;
        case DOWN: _snake[0].gridY += 1; break;
        case LEFT: _snake[0].gridX -= 1; break;
        case RIGHT: _snake[0].gridX += 1; break;
    }
    checkCollisions();
    updateSnakeSegment(_snake[0], 0);
}

void NibblerGame::updateSnakeSegment(SnakeSegment& element, size_t index)
{
    if (index == 0) {
        element.spritePath = headSpriteForDirection(element.direction);
    } else if (index == _snake.size() - 1) {
        element.spritePath = tailSpriteForDirection(element.direction);
    } else {
        element.spritePath = bodySpriteForDirection(element.direction);
    }
}

std::string NibblerGame::headSpriteForDirection(Direction direction)
{
    switch (direction) {
        case UP: return "./assets/sprites/snake_graphics/head_up.png";
        case DOWN: return "./assets/sprites/snake_graphics/head_down.png";
        case LEFT: return "./assets/sprites/snake_graphics/head_left.png";
        case RIGHT: return "./assets/sprites/snake_graphics/head_right.png";
        default: return "";
    }
}

std::string NibblerGame::bodySpriteForDirection(Direction direction)
{
    switch (direction) {
        case UP: return "./assets/sprites/snake_graphics/body_vertical.png";
        case DOWN: return "./assets/sprites/snake_graphics/body_vertical.png";
        case LEFT: return "./assets/sprites/snake_graphics/body_horizontal.png";
        case RIGHT: return "./assets/sprites/snake_graphics/body_horizontal.png";
        default: return "";
    }
}

std::string NibblerGame::tailSpriteForDirection(Direction direction)
{
    switch (direction) {
        case UP: return "./assets/sprites/snake_graphics/tail_down.png";
        case DOWN: return "./assets/sprites/snake_graphics/tail_up.png";
        case LEFT: return "./assets/sprites/snake_graphics/tail_right.png";
        case RIGHT: return "./assets/sprites/snake_graphics/tail_left.png";
        default: return "";
    }
}

void NibblerGame::redirectSnakeBasedOnWallCollision()
{
    int headX = _snake.front().gridX;
    int headY = _snake.front().gridY;

    bool wallInFront = isWallBasedOnDirection(headX, headY, _snakeDirection);
    bool wallToLeft = isWallBasedOnDirection(headX, headY, leftDirection(_snakeDirection));
    bool wallToRight = isWallBasedOnDirection(headX, headY, rightDirection(_snakeDirection));

    if (wallInFront && !wallToLeft && !wallToRight) {
        stopSnake();
        return;
    }

    if (wallInFront && wallToLeft && !wallToRight) {
        _snakeDirection = rightDirection(_snakeDirection);
    } else if (wallInFront && !wallToLeft && wallToRight) {
        _snakeDirection = leftDirection(_snakeDirection);
    }
    resumeSnake();
}

Direction NibblerGame::leftDirection(Direction currentDirection)
{
    switch (currentDirection) {
        case UP: return LEFT;
        case DOWN: return RIGHT;
        case LEFT: return DOWN;
        case RIGHT: return UP;
    }
    return currentDirection;
}

Direction NibblerGame::rightDirection(Direction currentDirection)
{
    switch (currentDirection) {
        case UP: return RIGHT;
        case DOWN: return LEFT;
        case LEFT: return UP;
        case RIGHT: return DOWN;
    }
    return currentDirection;
}

bool NibblerGame::isWallBasedOnDirection(int x, int y, Direction direction)
{
    int checkX = x, checkY = y;
    switch (direction) {
        case UP: checkY -= 1; break;
        case DOWN: checkY += 1; break;
        case LEFT: checkX -= 1; break;
        case RIGHT: checkX += 1; break;
    }
    return isWall(checkX, checkY);
}

void NibblerGame::stopSnake()
{
    _isSnakeMoving = false;
}

void NibblerGame::resumeSnake()
{
    _isSnakeMoving = true;
}

bool NibblerGame::isWall(int x, int y)
{
    for (const auto& wall : _walls) {
        if (wall.gridX == x && wall.gridY == y) {
            return true;
        }
    }
    return false;
}

void NibblerGame::checkCollisions()
{
    int headX = _snake.front().gridX;
    int headY = _snake.front().gridY;

    for (auto it = _fruits.begin(); it != _fruits.end();) {
        if (headX == it->gridX && headY == it->gridY) {
            it = _fruits.erase(it);
            addSegment();
            _appleAte++;
            _score++;
        } else {
            ++it;
        }
    }

    for (size_t i = 1; i < _snake.size(); ++i) {
        if (headX == _snake[i].gridX && headY == _snake[i].gridY) {
            endGame(false);
            return;
        }
    }
}

void NibblerGame::endGame(bool winOrLose)
{
    isNewHighScore();
    if (winOrLose) {
        std::cout << "Win! Score: " << _score << std::endl;
    } else {
        std::cout << "Game Over! Score: " << _score << std::endl;
    }
    _endGame = true;
}

void NibblerGame::addSegment()
{
    SnakeSegment& tail = _snake.back();
    SnakeSegment newSegment = {tail.spritePath, '0', tail.gridX, tail.gridY, 1.0f, 1.0f, Body, tail.direction};

    tail.part = Body;
    tail.asciiSprite = 'o';
    _snake.push_back(newSegment);
}

void NibblerGame::addWalls()
{
    for (int x = 0; x < _gridWidth; ++x) {
        _walls.push_back({x, 0, "./assets/sprites/snake_graphics/wall.png"}); // Mur du haut
        _walls.push_back({x, _gridHeight - 1, "./assets/sprites/snake_graphics/wall.png"}); // Mur du bas
    }

    for (int y = 1; y < _gridHeight - 1; ++y) { // Commence à 1 et finit à _gridHeight - 1 pour éviter les doubles coins
        _walls.push_back({0, y, "./assets/sprites/snake_graphics/wall.png"}); // Mur de gauche
        _walls.push_back({_gridWidth - 1, y, "./assets/sprites/snake_graphics/wall.png"}); // Mur de droite
    }
}

void NibblerGame::addRandomWalls(int numberOfWalls)
{
    for (int i = 0; i < numberOfWalls; ++i) {
        int wallX = rand() % _gridWidth;
        int wallY = rand() % _gridHeight;
        if (!checkSnakeCollision(wallX, wallY) && !checkAppleCollision(wallX, wallY)) {
            _walls.push_back({wallX, wallY, "./assets/sprites/snake_graphics/wall.png"});
        }
    }
}

void NibblerGame::addApples(int numberOfApples)
{
    int applesAdded = 0;
    while (applesAdded < numberOfApples) {
        int appleX = rand() % _gridWidth;
        int appleY = rand() % _gridHeight;
        if (!checkWallCollision(appleX, appleY) && !checkSnakeCollision(appleX, appleY)) {
            _fruits.push_back({appleX, appleY, "./assets/sprites/snake_graphics/apple.png"});
            applesAdded++;
        }
    }
}

bool NibblerGame::checkWallCollision(int x, int y)
{
    for (const auto& wall : _walls) {
        if (wall.gridX == x && wall.gridY == y) {
            return true;
        }
    }
    return false;
}

bool NibblerGame::checkSnakeCollision(int x, int y)
{
    for (const auto& segment : _snake) {
        if (segment.gridX == x && segment.gridY == y) {
            return true;
        }
    }
    return false;
}

bool NibblerGame::checkAppleCollision(int x, int y)
{
    for (const auto& segment : _snake) {
        if (segment.gridX == x && segment.gridY == y) {
            return true;
        }
    }
    return false;
}

void NibblerGame::rebuildMap()
{
    _map.clear();
    char asciiSprite;
    int pixelX;
    int pixelY;
    Elements elemConverted;

    for (const auto& fruit : _fruits) {
        pixelX = fruit.gridX * _gridSize;
        pixelY = fruit.gridY * _gridSize;
        elemConverted = {fruit.spritePath, 'A', pixelX, pixelY, 1.0f, 1.0f, ""};
        _map.push_back(elemConverted);
    }
    for (const auto& segment : _snake) {
        pixelX = segment.gridX * _gridSize;
        pixelY = segment.gridY * _gridSize;
        elemConverted = {segment.spritePath, segment.asciiSprite, pixelX, pixelY, segment.width, segment.height, ""};
        _map.push_back(elemConverted);
    }
    for (const auto& wall : _walls) {
        pixelX = wall.gridX * _gridSize;
        pixelY = wall.gridY * _gridSize;
        elemConverted = {wall.spritePath, '#', pixelX, pixelY, 1.0f, 1.0f, ""};
        _map.push_back(elemConverted);
    }
}

int NibblerGame::getScore()
{
    return _score;
}

void NibblerGame::setName(const std::string& name)
{
    _name = name;
}

const std::string NibblerGame::getName()
{
    return _name;
}

std::vector<Elements>& NibblerGame::getMap()
{
    return _map;
}

void NibblerGame::setLibs(std::vector<std::string> gameLibs, std::vector<std::string> graphicLibs, int indexDisplayList)
{
    this->_gameLibs = gameLibs;
    this->_graphicLibs = graphicLibs;
    this->_indexDisplayList = indexDisplayList;
}

void NibblerGame::isNewHighScore()
{
    std::ifstream file("highScore.txt");
    int highScore = -1;

    if (file.is_open()) {
        std::string line;
        if (std::getline(file, line)) {
            std::istringstream iss(line);
            iss >> highScore;
        }
        file.close();
    }
    if (_score > highScore) {
        std::ofstream outFile("highScore.txt");
        if (outFile.is_open()) {
            outFile << _score;
            outFile.close();
        }
    }
}

extern "C" IGameModule* createGameModule()
{
    return new NibblerGame();
}

