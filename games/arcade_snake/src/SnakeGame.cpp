/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SnakeGame.cpp
*/

#include "SnakeGame.hpp"

SnakeGame::SnakeGame() : _score(0), _snakeDirection(RIGHT), _gridSize(40), _gridWidth(20), _gridHeight(15), _endGame(false)
{
    srand(time(nullptr));
    int startX = _gridWidth / 2;
    int startY = _gridHeight / 2;
    _snake.push_back({"./assets/sprites/snake_graphics/head_right.png", '@', startX, startY, 1.0f, 1.0f, Head, RIGHT});
    _snake.push_back({"./assets/sprites/snake_graphics/body_horizontal.png", 'o', startX - 1, startY, 1.0f, 1.0f, Body, RIGHT});
    _snake.push_back({"./assets/sprites/snake_graphics/body_horizontal.png", 'o', startX - 2, startY, 1.0f, 1.0f, Body, RIGHT});
    _snake.push_back({"./assets/sprites/snake_graphics/tail_left.png", '0', startX - 3, startY, 1.0f, 1.0f, Tail, RIGHT});
    addApple();
    std::cout << "SnakeGame initialized." << std::endl;
}

SnakeGame::~SnakeGame()
{
    std::cout << "SnakeGame destroyed." << std::endl;
}

int SnakeGame::update(std::vector<keys>& events)
{
    if (_endGame)
        return 2;
    auto now = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastUpdate) >= _updateInterval) {
        updateSnakeSegmentSprites();
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

void SnakeGame::updateSnakeSegmentSprites()
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

void SnakeGame::updateSnakeSegment(SnakeSegment& element, size_t index)
{
    if (index == 0) {
        element.spritePath = headSpriteForDirection(element.direction);
    } else if (index == _snake.size() - 1) {
        element.spritePath = tailSpriteForDirection(element.direction);
    } else {
        element.spritePath = bodySpriteForDirection(element.direction);
    }
}

std::string SnakeGame::headSpriteForDirection(Direction direction)
{
    switch (direction) {
        case UP: return "./assets/sprites/snake_graphics/head_up.png";
        case DOWN: return "./assets/sprites/snake_graphics/head_down.png";
        case LEFT: return "./assets/sprites/snake_graphics/head_left.png";
        case RIGHT: return "./assets/sprites/snake_graphics/head_right.png";
        default: return "";
    }
}

std::string SnakeGame::bodySpriteForDirection(Direction direction)
{
    switch (direction) {
        case UP: return "./assets/sprites/snake_graphics/body_vertical.png";
        case DOWN: return "./assets/sprites/snake_graphics/body_vertical.png";
        case LEFT: return "./assets/sprites/snake_graphics/body_horizontal.png";
        case RIGHT: return "./assets/sprites/snake_graphics/body_horizontal.png";
        default: return "";
    }
}

std::string SnakeGame::tailSpriteForDirection(Direction direction)
{
    switch (direction) {
        case UP: return "./assets/sprites/snake_graphics/tail_down.png";
        case DOWN: return "./assets/sprites/snake_graphics/tail_up.png";
        case LEFT: return "./assets/sprites/snake_graphics/tail_right.png";
        case RIGHT: return "./assets/sprites/snake_graphics/tail_left.png";
        default: return "";
    }
}

void SnakeGame::checkCollisions()
{
    for (auto it = _fruits.begin(); it != _fruits.end();) {
        if (_snake[0].gridX == it->gridX && _snake[0].gridY == it->gridY) {
            it = _fruits.erase(it);
            addSegment();
            _score++;
            addApple();
        } else {
            ++it;
        }
    }
    for (size_t i = 1; i < _snake.size(); ++i) {
        if (_snake[0].gridX == _snake[i].gridX && _snake[0].gridY == _snake[i].gridY) {
            endGame();
            return;
        }
    }
    if (_snake[0].gridX < 0 || _snake[0].gridX > _gridWidth - 1 || _snake[0].gridY < 0 || _snake[0].gridY > _gridHeight - 1) {
        endGame();
        return;
    }
}
bool SnakeGame::isNewHighScore()
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
            return true;
        }
    }

    return false;
}

void SnakeGame::endGame()
{
    if (isNewHighScore()) {
        std::cout << "Congratulations ! New highScore: " << _score << std::endl;
    } else {
        std::cout << "Game Over! Score: " << _score << std::endl;
    }
    _endGame = true;
}

void SnakeGame::addSegment()
{
    SnakeSegment& tail = _snake.back();
    SnakeSegment newSegment = {tail.spritePath, '0', tail.gridX, tail.gridY, 1.0f, 1.0f, Body, tail.direction};

    tail.part = Body;
    tail.asciiSprite = 'o';
    _snake.push_back(newSegment);
}

void SnakeGame::addApple()
{
    int appleX, appleY;
    do {
        appleX = rand() % _gridWidth;
        appleY = rand() % _gridHeight;
    } while (checkAppleCollision(appleX, appleY));

    Fruit apple = {appleX, appleY, "./assets/sprites/snake_graphics/apple.png"};
    _fruits.push_back(apple);
}

bool SnakeGame::checkAppleCollision(int x, int y)
{
    for (const auto& segment : _snake) {
        if (segment.gridX == x && segment.gridY == y) {
            return true;
        }
    }
    return false;
}

void SnakeGame::rebuildMap()
{
    _map.clear();
    char asciiSprite;
    int pixelX;
    int pixelY;
    Elements elemConverted;

    for (int y = 0; y <= _gridHeight + 1; y++) {
        for (int x = 0; x <= _gridWidth + 1; x++) {
            asciiSprite = ' ';
            if (x == 0 || x == _gridWidth + 1 || y == 0 || y == _gridHeight + 1) {
                asciiSprite = '*';
            }
            _map.push_back({ "", asciiSprite, x * _gridSize, y * _gridSize, 1.0f, 1.0f, "" });
        }
    }
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
}

int SnakeGame::getScore()
{
    return _score;
}

void SnakeGame::setName(const std::string& name)
{
    _name = name;
}

const std::string SnakeGame::getName()
{
    return _name;
}

std::vector<Elements>& SnakeGame::getMap()
{
    return _map;
}

void SnakeGame::setLibs(std::vector<std::string> gameLibs, std::vector<std::string> graphicLibs, int indexDisplayList)
{
    this->_gameLibs = gameLibs;
    this->_graphicLibs = graphicLibs;
    this->_indexDisplayList = indexDisplayList;
}

extern "C" IGameModule* createGameModule()
{
    return new SnakeGame();
}
