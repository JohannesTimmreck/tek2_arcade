/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Asset
*/

#ifndef ASSET_HPP_
#define ASSET_HPP_

#include <SFML/Graphics.hpp>
#include "SDL2/SDL.h"
#include "../../../GlobalHeaders.hpp"
#include <SDL2/SDL_image.h>
#include "SDL2/SDL_ttf.h"

namespace graphical {

class Asset
{
  private:
    IObjectToDraw::Type _type;
    std::string _id;

    SDL_Surface *_texture;
    SDL_Rect _rect;

  //TEXT
    TTF_Font* _font;
    SDL_Color _color;

    bool _loaded;
  public:
    explicit Asset(std::string path, IObjectToDraw::Type type, std::string id);
    ~Asset() = default;
    void setAnimRect(std::tuple<unsigned int, unsigned int, unsigned int, unsigned int> rect);
    void updateTexture() {}
    std::string getId() {return _id;}
    void handle(IObjectToDraw *instance, SDL_Renderer *renderer);
};

} // namespace graphical

#endif /* !ASSET_HPP_ */
