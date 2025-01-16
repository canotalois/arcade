/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SDLDisplayModule.hpp
*/

#pragma once
#include "../../../src/IDisplayModule.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>

class SDLDisplayModule : public IDisplayModule {
    private:
        SDL_Window* _window = nullptr;
        SDL_Renderer* _renderer = nullptr;
        TTF_Font* _font = nullptr;
        std::vector<keys> _events;
        std::string _userName;
        int _userScore;
    public:
        SDLDisplayModule();
        ~SDLDisplayModule() override;
        void render(std::vector<Elements>& map) override;
        std::vector<keys>& getEvents() override;
        void displayPlayerName(const std::string& name) override;
        void displayPlayerScore(int score) override;
};
