/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** description
*/

#ifndef OOP_ARCADE_2019_WALL_HPP
#define OOP_ARCADE_2019_WALL_HPP

#include "../../../GlobalHeaders.hpp"

namespace games {

class Wall : public IObjectToDraw
{
  private:
    std::pair<long int, long int> _coords;
  public:
    Wall(long int y, long int x) : _coords(std::make_pair(x, y)) {};
    ~Wall() = default;
    std::string getId() const override {return std::string("wall");}
    std::string getPath() const override {return std::string("games/Nibbler/assets/wall");}
    Type getType() const override {return objects;}
    std::string getValue() const override {return "";}
    std::pair<long int, long int> getCoords() const override {return _coords;}
    std::tuple<unsigned int, unsigned int, unsigned int, unsigned int> getSpritePos() const override {return std::make_tuple(0, 0, 32, 32);}
    std::tuple<uint, uint, uint, uint> getColor() const override {return std::make_tuple(0,0,0,0);};
};

} // namespace games

#endif //OOP_ARCADE_2019_WALL_HPP
