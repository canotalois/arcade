/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SDLDisplayModule.cpp
*/

#include "SDLDisplayModule.hpp"
#include <iostream>

SDLDisplayModule::SDLDisplayModule()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() == -1) {
        std::cerr << "SDL cannot initialize: " << SDL_GetError() << std::endl;
        return;
    }
    this->_window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!this->_window) {
        std::cerr << "Window cannot create: " << SDL_GetError() << std::endl;
        return;
    }
    this->_renderer = SDL_CreateRenderer(this->_window, -1, 0);
    if (!this->_renderer) {
        std::cerr << "Renderer cannot create: " << SDL_GetError() << std::endl;
        return;
    }
    SDL_SetRenderDrawColor(this->_renderer, 255, 255, 255, 255);
    this->_font = TTF_OpenFont("./assets/fonts/poppins.ttf", 24);
    if (!this->_font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return;
    }
}

SDLDisplayModule::~SDLDisplayModule()
{
    if (this->_font) {
        TTF_CloseFont(this->_font);
        this->_font = nullptr;
    }
    if (this->_renderer) {
        SDL_DestroyRenderer(this->_renderer);
        this->_renderer = nullptr;
    }
    if (this->_window) {
        SDL_DestroyWindow(this->_window);
        this->_window = nullptr;
    }
    TTF_Quit();
    SDL_Quit();
}

void SDLDisplayModule::render(std::vector<Elements> &map)
{
    SDL_RenderClear(this->_renderer);
    for (const auto& element : map) {
        if (!element.spritePath.empty()) {
            SDL_Surface* tmpSurface = IMG_Load(element.spritePath.c_str());
            SDL_Texture* texture = SDL_CreateTextureFromSurface(this->_renderer, tmpSurface);
            if (!texture) {
                std::cerr << "Failed to load texture from file: " << element.spritePath << std::endl;
                continue;
            }
            SDL_FreeSurface(tmpSurface);
            SDL_Rect dstRect = {element.x, element.y, 0, 0};
            SDL_QueryTexture(texture, nullptr, nullptr, &dstRect.w, &dstRect.h);
            SDL_RenderCopy(this->_renderer, texture, nullptr, &dstRect);
            SDL_DestroyTexture(texture);
        } else if (!element.text.empty()) {
            SDL_Color color = {0, 0, 0, 255};
            SDL_Surface* surface = TTF_RenderText_Solid(this->_font, element.text.c_str(), color);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(this->_renderer, surface);
            SDL_Rect dstRect = {element.x, element.y, surface->w, surface->h};
            SDL_FreeSurface(surface);
            SDL_RenderCopy(this->_renderer, texture, nullptr, &dstRect);
            SDL_DestroyTexture(texture);
        }
    }
    displayPlayerName(_userName);
    displayPlayerScore(_userScore);
    SDL_RenderPresent(this->_renderer);
}

std::vector<keys>& SDLDisplayModule::getEvents()
{
    this->_events.clear();
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            if (this->_font) {
                TTF_CloseFont(this->_font);
                this->_font = nullptr;
            }
            if (this->_renderer) {
                SDL_DestroyRenderer(this->_renderer);
                this->_renderer = nullptr;
            }
            if (this->_window) {
                SDL_DestroyWindow(this->_window);
                this->_window = nullptr;
            }
            TTF_Quit();
            SDL_Quit();
            exit (0);
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_z: this->_events.push_back(KEY_Z); break;
                case SDLK_q: this->_events.push_back(KEY_Q); break;
                case SDLK_s: this->_events.push_back(KEY_S); break;
                case SDLK_d: this->_events.push_back(KEY_D); break;
                case SDLK_LEFT: this->_events.push_back(LEFT_ARROW); break;
                case SDLK_DOWN: this->_events.push_back(DOWN_ARROW); break;
                case SDLK_RIGHT: this->_events.push_back(RIGHT_ARROW); break;
                case SDLK_UP: this->_events.push_back(UP_ARROW); break;
                case SDLK_ESCAPE: this->_events.push_back(KEY_ESCAPE); break;
                case SDLK_p: this->_events.push_back(KEY_P); break;
                case SDLK_RETURN: this->_events.push_back(KEY_ENTER); break;
                case SDLK_SPACE: this->_events.push_back(KEY_SPACE); break;
                case SDLK_o: this->_events.push_back(KEY_O); break;
                case SDLK_a: this->_events.push_back(KEY_A); break;
                default: break;
            }
        }
    }
    return this->_events;
}

void SDLDisplayModule::displayPlayerName(const std::string &name)
{
    _userName = name;
    if (!_userName.empty()) {
        SDL_Color color = {255, 0, 0, 255};
        SDL_Surface* surface = TTF_RenderText_Solid(this->_font, _userName.c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(this->_renderer, surface);

        SDL_Rect dstRect = {10, 10, surface->w, surface->h};
        SDL_FreeSurface(surface);

        SDL_RenderCopy(this->_renderer, texture, nullptr, &dstRect);
        SDL_DestroyTexture(texture);
    }
}

void SDLDisplayModule::displayPlayerScore(int score)
{
    _userScore = score;
    if (_userScore >= 0) {
        std::string scoreText = "Score: " + std::to_string(_userScore);
        SDL_Color color = {255, 0, 0, 255};
        SDL_Surface* surface = TTF_RenderText_Solid(this->_font, scoreText.c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(this->_renderer, surface);

        SDL_Rect dstRect = {700 - surface->w, 10, surface->w, surface->h};
        SDL_FreeSurface(surface);

        SDL_RenderCopy(this->_renderer, texture, nullptr, &dstRect);
        SDL_DestroyTexture(texture);
    }
}

extern "C" IDisplayModule* createDisplayModule()
{
    return new SDLDisplayModule();
}
