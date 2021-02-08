/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** description
*/

#ifndef OOP_ARCADE_2019_FRUIT_HPP
#define OOP_ARCADE_2019_FRUIT_HPP

#include "../../../GlobalHeaders.hpp"

namespace games {

class Fruit : public IObjectToDraw
{
  private:
    std::pair<long int, long int> _coords;
  public:
    Fruit(long int y, long int x) : _coords(std::make_pair(x, y)) {};
    ~Fruit() = default;
    std::string getId() const override {return std::string("fruit");}
    std::string getPath() const override {return std::string("games/Nibbler/assets/fruit");}
    Type getType() const override {return objects;}
    std::string getValue() const override {return "";}
    std::pair<long int, long int> getCoords() const override {return _coords;}
    std::tuple<unsigned int, unsigned int, unsigned int, unsigned int> getSpritePos() const override {return std::make_tuple(0, 0, 64, 64);}
    std::tuple<uint, uint, uint, uint> getColor() const override {return std::make_tuple(0,0,0,0);};
};

} // namespace games

#endif //OOP_ARCADE_2019_FRUIT_HPP
