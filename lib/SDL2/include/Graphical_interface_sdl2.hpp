/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** graphical_interface_sdl2
*/

#ifndef GRAPHICAL_INTERFACE_SDL2_HPP_
#define GRAPHICAL_INTERFACE_SDL2_HPP_


#include <iostream>
#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>
#include "Asset.hpp"

#include "../../IGraphicalInterface.hpp"

namespace graphical {

class GraphicalInterface_sdl : public IGraphicalInterface
{
    public:
        GraphicalInterface_sdl();
        ~GraphicalInterface_sdl();
        bool init() override;
        bool initAssets(std::vector<IObjectToDraw *> assets) override;
        bool destroyAssets() override;
        bool destroy() override;
        COMMAND getInput() override;
        bool draw(std::vector<IObjectToDraw *> objects) override;
    private:
        SDL_Window *_window;
        SDL_Renderer *_renderer;
        SDL_Event _event;
        std::vector<Asset> _assets;
};

}

#endif /* !GRAPHICAL_INTERFACE_SDL2_HPP_ */
