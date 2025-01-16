/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** NCursesDisplayModule.hpp
*/

#include "../../../src/IDisplayModule.hpp"
#include <iostream>
#include <ncurses.h>

class NCursesDisplayModule : public IDisplayModule {
    private:
        std::vector<keys> _events;
        std::string _userName;
        int _userScore;
    public:
        NCursesDisplayModule();
        ~NCursesDisplayModule() override;
        void render(std::vector<Elements>& map) override;
        std::vector<keys>& getEvents() override;
        void displayPlayerName(const std::string& name) override;
        void displayPlayerScore(int score) override;
};
