/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** description
*/

#include "../include/Text.hpp"

namespace games {

Text::Text(std::string id, std::string value, long int x, long int y, std::string path) :
    _id(id), _path(std::move(path)), _value(std::move(value)), _coords(x, y)
{
}

} // namespace games