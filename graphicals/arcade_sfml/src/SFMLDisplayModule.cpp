/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SFMLDisplayModule.cpp
*/

#include "SFMLDisplayModule.hpp"

SFMLDisplayModule::SFMLDisplayModule()
{
    window.create(sf::VideoMode(800, 600), "Arcade");
    std::cout << "SFMLDisplayModule initialized." << std::endl;
    if (!_font.loadFromFile("./assets/fonts/poppins.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
    } else {
        std::cout << "Font loaded successfully." << std::endl;
    }
}

SFMLDisplayModule::~SFMLDisplayModule()
{
    if (window.isOpen()) {
        window.close();
    }
}

void SFMLDisplayModule::render(std::vector<Elements>& map)
{
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Text textElement;
    textElement.setFont(_font);
    textElement.setCharacterSize(24);
    textElement.setFillColor(sf::Color::Black);

    window.clear(sf::Color::White);
    window.draw(_playerNameText);
    window.draw(_playerScoreText);

    for (auto& element : map) {
        if (!element.spritePath.empty()) {
            if (!texture.loadFromFile(element.spritePath)) {
                std::cerr << "Cannot load texture from file: " << element.spritePath << std::endl;
                continue;
            }
            sprite.setTexture(texture);
            sprite.setPosition(static_cast<float>(element.x), static_cast<float>(element.y));
            window.draw(sprite);
        } else if (!element.text.empty()) {
            textElement.setString(element.text);
            textElement.setPosition(static_cast<float>(element.x), static_cast<float>(element.y));
            window.draw(textElement);
        }
    }
    displayPlayerName(_userName);
    displayPlayerScore(_userScore);
    window.display();
}

std::vector<keys>& SFMLDisplayModule::getEvents()
{
    this->_events.clear();
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            exit(0);
        } else if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case (sf::Keyboard::Z) : this->_events.push_back(KEY_Z); break;
                case (sf::Keyboard::Q) : this->_events.push_back(KEY_Q); break;
                case (sf::Keyboard::S) : this->_events.push_back(KEY_S); break;
                case (sf::Keyboard::D) : this->_events.push_back(KEY_D); break;
                case (sf::Keyboard::Left) : this->_events.push_back(LEFT_ARROW); break;
                case (sf::Keyboard::Down) : this->_events.push_back(DOWN_ARROW); break;
                case (sf::Keyboard::Right) : this->_events.push_back(RIGHT_ARROW); break;
                case (sf::Keyboard::Up) : this->_events.push_back(UP_ARROW); break;
                case (sf::Keyboard::Escape) : this->_events.push_back(KEY_ESCAPE); break;
                case (sf::Keyboard::P) : this->_events.push_back(KEY_P); break;
                case (sf::Keyboard::Enter) : this->_events.push_back(KEY_ENTER); break;
                case (sf::Keyboard::Space) : this->_events.push_back(KEY_SPACE); break;
                case (sf::Keyboard::O) : this->_events.push_back(KEY_O); break;
                case (sf::Keyboard::A) : this->_events.push_back(KEY_A); break;
                default: break;
            }
        }
    }
    return this->_events;
}

void SFMLDisplayModule::displayPlayerName(const std::string& name)
{
    _userName = name;
    if (!_userName.empty()) {
        _playerNameText.setFont(_font);
        _playerNameText.setString(name);
        _playerNameText.setCharacterSize(24);
        _playerNameText.setFillColor(sf::Color::Red);
        float textXPos = window.getSize().x - _playerNameText.getLocalBounds().width - 10;
        float textYPos = window.getSize().y - _playerNameText.getLocalBounds().height - 10;
        _playerNameText.setPosition(textXPos, textYPos);
    }
}

void SFMLDisplayModule::displayPlayerScore(int score)
{
    _userScore = score;
    if (_userScore >= 0) {
        _playerScoreText.setFont(_font);
        _playerScoreText.setString("Score: " + std::to_string(score));
        _playerScoreText.setCharacterSize(24);
        _playerScoreText.setFillColor(sf::Color::Red);
        float textXPos = (window.getSize().x / 2) - (_playerScoreText.getLocalBounds().width / 2);
        _playerScoreText.setPosition(textXPos, 10);
    }
}

extern "C" IDisplayModule* createDisplayModule()
{
    return new SFMLDisplayModule();
}
