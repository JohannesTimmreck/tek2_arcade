/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** description
*/

#include "../include/MainMenuObject.hpp"

namespace core {

MainMenuObject::MainMenuObject(std::string id, std::string path, std::string value, long int x, long int y) :
    _id(std::move(id)), _path(std::move(path)), _type(text), _value(std::move(value)),
    _coords(x, y), _texture(0, 0, 0, 0)
{
}

MainMenuObject::MainMenuObject(std::string id, std::string path, Type type, std::string value, long int x, long int y, unsigned int textX, unsigned int textY, unsigned int textHeight, unsigned int textWidth) :
    _id(std::move(id)), _path(std::move(path)), _type(type), _value(std::move(value)),
    _coords(x, y), _texture(textX, textY, textHeight, textWidth)
{
}

}  // namespace core