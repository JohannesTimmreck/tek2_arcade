/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** description
*/

#include <iostream>
#include "../include/Core.hpp"

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Usage: ./arcade ./[path to graphical shared library module]" << std::endl;
        return 84;
    }
    core::Core core(av[1]);
    if (!core.graphicsLoaded())
        return 84;
    core.loop();
}