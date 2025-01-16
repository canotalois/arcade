/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** main.cpp
*/

#include "Core.hpp"
#include "DisplayModule.hpp"
#include "AGameModule.hpp"
#include <dlfcn.h>
#include <filesystem>
#include "ErrorHandling.hpp"

int main(int ac, char **av)
{
    try {
        if (ac != 2) {
            throw ErrorHandling::Error("Usage: ./arcade path_to_graphic_lib.so", "");
        }
        Core core(av[1],"./lib/arcade_menu.so");
        core.run();
    } catch (ErrorHandling::Error &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    return 0;
}
