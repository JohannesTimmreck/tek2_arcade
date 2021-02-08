/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** description
*/

#include <iostream>

#include "../include/Asset.hpp"

namespace graphical {

Asset::Asset(std::string path, IObjectToDraw::Type type, std::string id) :
_type(type), _id(id)
{
    if (path[path.size() - 1] != '/')
        path.append("/");
    switch (_type) {
        case IObjectToDraw::objects:
            path.append("texture.png");
            _texture = IMG_Load(path.c_str());
            _loaded = true;
            break;
        case IObjectToDraw::text:
            path.append("font.ttf");
            _font = TTF_OpenFont(path.c_str(), 24);
            _color = {255, 255, 255, 255};
            _loaded = true;
            break;
    }
}

void Asset::setAnimRect(std::tuple<unsigned int, unsigned int, unsigned int, unsigned int> rect) {
    _rect.x = static_cast<int>(std::get<0>(rect));
    _rect.y = static_cast<int>(std::get<1>(rect));
    _rect.h = static_cast<int>(std::get<2>(rect));
    _rect.w = static_cast<int>(std::get<3>(rect));
}

void Asset::handle(IObjectToDraw *instance, SDL_Renderer *renderer)
{
    SDL_Rect dstrect;
    SDL_Texture *sprite;
    if (!_loaded)
        return;
    switch (_type) {
        case IObjectToDraw::objects:
            setAnimRect(instance->getSpritePos());
            dstrect = { static_cast<int>(std::get<0>(instance->getCoords())), static_cast<int>(std::get<1>(instance->getCoords())), _rect.w, _rect.h };
            if (_texture == NULL) {
                break;
            }
            sprite = SDL_CreateTextureFromSurface(renderer, _texture);
	        SDL_RenderCopy(renderer, sprite, &_rect, &dstrect);
            SDL_DestroyTexture(sprite);
            break;
        case IObjectToDraw::text:
            if (_font == NULL) {
                break;
            }
            _color.r = std::get<0>(instance->getColor());
            _color.g = std::get<1>(instance->getColor());
            _color.b = std::get<2>(instance->getColor());
            _color.a = std::get<3>(instance->getColor());
            _texture = TTF_RenderText_Solid(_font, instance->getValue().c_str(), _color);
            if (_texture == NULL) {
                break;
            }
            dstrect = { static_cast<int>(std::get<0>(instance->getCoords())), static_cast<int>(std::get<1>(instance->getCoords())), _texture->w, _texture->h };
		    sprite = SDL_CreateTextureFromSurface(renderer, _texture);
            SDL_RenderCopy(renderer, sprite, NULL, &dstrect);
            SDL_DestroyTexture(sprite);
            SDL_FreeSurface(_texture);
            break;
    }
}

} // namespace graphical