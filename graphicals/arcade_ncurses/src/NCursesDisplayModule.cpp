/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** NCursesDisplayModule.cpp
*/

#include "NCursesDisplayModule.hpp"


NCursesDisplayModule::NCursesDisplayModule() : _userScore(0)
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    nodelay(stdscr, TRUE);
    clear();
    std::cout << "NCursesDisplayModule initialized." << std::endl;
}

NCursesDisplayModule::~NCursesDisplayModule()
{
    endwin();
}

void NCursesDisplayModule::render(std::vector<Elements>& map)
{
    erase();
    for (const auto& element : map) {
        if (element.spritePath.empty() && !element.text.empty()) {
            mvprintw(element.y, element.x, "%s", element.text.c_str());
        }
        mvaddch(element.y / 40, element.x / 20, element.asciiSprite);
    }
    displayPlayerName(_userName);
    displayPlayerScore(_userScore);
    refresh();
}

std::vector<keys>& NCursesDisplayModule::getEvents()
{
    this->_events.clear();
    switch(getch()) {
        case 'z':
            _events.push_back(KEY_Z);
            break;
        case 'q':
            _events.push_back(KEY_Q);
            break;
        case 's':
            _events.push_back(KEY_S);
            break;
        case 'd':
            _events.push_back(KEY_D);
            break;
        case KEY_LEFT:
            _events.push_back(LEFT_ARROW);
            break;
        case KEY_DOWN:
            _events.push_back(DOWN_ARROW);
            break;
        case KEY_RIGHT:
            _events.push_back(RIGHT_ARROW);
            break;
        case KEY_UP:
            _events.push_back(UP_ARROW);
            break;
        case 27:
            _events.push_back(KEY_ESCAPE);
            break;
        case 'p':
            _events.push_back(KEY_P);
            break;
        case '\n':
            _events.push_back(static_cast<keys>(KEY_ENTER));
            break;
        case ' ':
            _events.push_back(KEY_SPACE);
            break;
        case 'o':
        case 'O':
            _events.push_back(KEY_O);
            break;
        case 'a':
            _events.push_back(KEY_A);
        default:
            break;
    }
    return _events;
}

void NCursesDisplayModule::displayPlayerName(const std::string& name)
{
    _userName = name;
    mvprintw(0, 20, "%s", name.c_str());
}

void NCursesDisplayModule::displayPlayerScore(int score)
{
    _userScore = score;
    if (_userScore >= 0) {
        mvprintw(0, COLS - 20, "Score: %d", score);
    }
}

extern "C" IDisplayModule* createDisplayModule()
{
    return new NCursesDisplayModule();
}
