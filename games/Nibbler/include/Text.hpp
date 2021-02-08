/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** description
*/

#ifndef OOP_ARCADE_2019_GAMEOBJECT_HPP
#define OOP_ARCADE_2019_GAMEOBJECT_HPP

#include "../../../GlobalHeaders.hpp"

namespace games {

class Text : public IObjectToDraw
{
  public:
    explicit Text(std::string id = "text", std::string value = "", long int x = 0, long int y = 0, std::string path = "games/Nibbler/assets/text/");

    ~Text() = default;
    std::string getId() const override {return _id;}

    std::string getPath() const override {return _path;}
    Type getType() const override {return text;}

    std::string getValue() const override {return _value;}
    std::pair<long int, long int> getCoords() const override {return _coords;}
    std::tuple<unsigned int, unsigned int, unsigned int, unsigned int> getSpritePos() const override {return std::make_tuple(0,0,0,0);}
    void setCoords(long int x, long int y) {std::get<0>(_coords) = x;std::get<1>(_coords) = y;}
    void setString(std::string string) {_value = string;}
    std::tuple<uint, uint, uint, uint> getColor() const override {return std::make_tuple(255,255,255,255);}

  private:
    std::string _id;
    std::string _path;
    std::string _value;
    std::pair<long int, long int> _coords; // (x, y)
};

} // namespace games

#endif //OOP_ARCADE_2019_GAMEOBJECT_HPP
