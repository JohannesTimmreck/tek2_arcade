/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** GraphicalInterface_sdl2
*/
#include <stdio.h>
#include "../include/Graphical_interface_sdl2.hpp"

extern "C" graphical::IGraphicalInterface *entryPoint(void)
{
    return new graphical::GraphicalInterface_sdl;
}

graphical::GraphicalInterface_sdl::GraphicalInterface_sdl()
{
    std::cout << "Graphics: created SDL2 lib Interface" << std::endl;
}

graphical::GraphicalInterface_sdl::~GraphicalInterface_sdl()
{
    std::cout << "Graphics: destroy SDL2 lib Interface" << std::endl;
}

bool graphical::GraphicalInterface_sdl::init()
{
    std::cout << "Graphics: opening SDL2 window" << std::endl;
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        _window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, 0);
        _renderer = SDL_CreateRenderer(_window, -1, 0);
    }
    TTF_Init();
    return true;
}


bool graphical::GraphicalInterface_sdl::initAssets(std::vector<IObjectToDraw *> assets)
{
    for (size_t i = 0; i < assets.size(); i++)
        _assets.push_back(Asset(assets[i]->getPath(), assets[i]->getType(), assets[i]->getId()));
    return true;
}

bool graphical::GraphicalInterface_sdl::destroyAssets()
{
    _assets.clear();
    return true;
}

bool graphical::GraphicalInterface_sdl::destroy()
{
    TTF_Quit();
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    return true;
}

COMMAND graphical::GraphicalInterface_sdl::getInput()
{
    SDL_PollEvent(&_event);

    switch (_event.type) {
        case SDL_QUIT:
            return EXIT;
        case SDL_KEYDOWN:
            if (_event.key.keysym.sym == SDLK_w || _event.key.keysym.sym == SDLK_UP) {
                return UP;
            } else if (_event.key.keysym.sym == SDLK_a || _event.key.keysym.sym == SDLK_LEFT) {
                return LEFT;
            } else if (_event.key.keysym.sym == SDLK_d || _event.key.keysym.sym == SDLK_RIGHT) {
                return RIGHT;
            } else if (_event.key.keysym.sym == SDLK_s || _event.key.keysym.sym == SDLK_DOWN) {
                return DOWN;
            } else if (_event.key.keysym.sym == SDLK_u) {
                return PREV_GRAPH;
            } else if (_event.key.keysym.sym == SDLK_i) {
                return NEXT_GRAPH;
            } else if (_event.key.keysym.sym == SDLK_j) {
                return PREV_GAME;
            } else if (_event.key.keysym.sym == SDLK_k) {
                return NEXT_GAME;
            } else if (_event.key.keysym.sym == SDLK_r) {
                return RESTART;
            } else if (_event.key.keysym.sym == SDLK_m) {
                return MAIN_MENU;
            } else if (_event.key.keysym.sym == SDLK_q) {
                return EXIT;
            }
    }
    return NO_INPUT;
}

bool graphical::GraphicalInterface_sdl::draw(std::vector<IObjectToDraw *> objects)
{

	SDL_RenderClear(_renderer);
    for (size_t i = 0; i < objects.size(); i++) {
        for (size_t j = 0; j < _assets.size(); j++) {
            if (objects[i]->getId() == _assets[j].getId()) {
                _assets.at(j).handle(objects.at(i), _renderer);
                break;
            }
        }
    }
    SDL_RenderPresent(_renderer);
    return true;
}