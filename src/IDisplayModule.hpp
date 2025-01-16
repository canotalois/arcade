/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** IDisplayModule
*/

#pragma once
#include <string>
#include <vector>

struct Elements {
    std::string spritePath;
    char asciiSprite;
    int x;
    int y;
    float width;
    float height;
    std::string text;
};

enum keys {
    ERROR = -1,
    UP_ARROW,
    DOWN_ARROW,
    LEFT_ARROW,
    RIGHT_ARROW,
    KEY_Z,
    KEY_S,
    KEY_Q,
    KEY_D,
    KEY_ESCAPE, // touche pour retourner au menu principale
    KEY_P, // Touche pour changer dynamiquement la librairie graphique
    KEY_ENTER, // touche pour valider sur le menu
    KEY_SPACE, // touche pour reset le jeu
    KEY_O, // touche pour changer la lib de jeu
    KEY_A // touche pour fermer le programme
};

class IDisplayModule {
    public:
        virtual ~IDisplayModule() = default;

        // Mise à jour et rendu des éléments graphiques
        virtual void render(std::vector<Elements>& map) = 0; // Draw l'état actuel du jeu // Appeler à chaque tour de la boucle principale dans Core

        virtual std::vector<keys>& getEvents() = 0; // Liste qui contient les events sous forme de int pour enum

        // Affichage des éléments utilisateur
        virtual void displayPlayerName(const std::string& name) = 0; // Appelé par le Core our par le jeu
        virtual void displayPlayerScore(int score) = 0; // Appelé par le Core oou par le jeu
};
