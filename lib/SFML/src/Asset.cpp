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
    _type(type), _id(id), _texture(), _rect(), _sprite(), _font(), _text(), _loaded(false)
{
    if (path[path.size() - 1] != '/')
        path.append("/");
    switch (_type) {
        case IObjectToDraw::objects:
            if (!_texture.loadFromFile(path + "texture.png"))
                return;
            _loaded = true;
            break;
        case IObjectToDraw::text:
            if (!_font.loadFromFile(path + "font.ttf"))
                return;
            _text.setCharacterSize(20);
            _text.setFillColor(sf::Color::White);
            _text.setStyle(sf::Text::Regular);
            _loaded = true;
    }
}

void Asset::setAnimRect(std::tuple<unsigned int, unsigned int, unsigned int, unsigned int> rect) {
    _rect.left = static_cast<int>(std::get<0>(rect));
    _rect.top = static_cast<int>(std::get<1>(rect));
    _rect.height = static_cast<int>(std::get<2>(rect));
    _rect.width = static_cast<int>(std::get<3>(rect));
    _sprite.setTextureRect(_rect);
}

void Asset::handle(IObjectToDraw *instance, sf::RenderWindow &window) {
    if (!_loaded)
        return;
    switch (_type) {
        case IObjectToDraw::objects:
            _sprite.setPosition(std::get<0>(instance->getCoords()), std::get<1>(instance->getCoords()));
            setAnimRect(instance->getSpritePos());
            _sprite.setTexture(_texture);
            window.draw(_sprite);
            break;
        case IObjectToDraw::text:
            _text.setFillColor(sf::Color(std::get<0>(instance->getColor()), std::get<1>(instance->getColor()), std::get<2>(instance->getColor()), std::get<3>(instance->getColor())));
            _text.setPosition(std::get<0>(instance->getCoords()), std::get<1>(instance->getCoords()));
            _text.setString(instance->getValue());
            _text.setFont(_font);
            window.draw(_text);
    }
}

} // namespace graphical