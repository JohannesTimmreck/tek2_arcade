/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** description
*/

#ifndef OOP_ARCADE_2019_MAINMENUOBJECT_HPP
#define OOP_ARCADE_2019_MAINMENUOBJECT_HPP

#include "../../GlobalHeaders.hpp"

namespace core {

class MainMenuObject : public IObjectToDraw
{
  public:
    explicit MainMenuObject(std::string id,
        std::string path,
        Type type,
        std::string value,
        long int x,
        long int y,
        unsigned int textX = 0,
        unsigned int textY = 0,
        unsigned int textHeight = 0,
        unsigned int textWidth = 0);

    explicit MainMenuObject(std::string id, std::string path, std::string value, long int x, long int y);
    ~MainMenuObject() = default;
    std::string getId() const override {return _id;}

    std::string getPath() const override {return _path;}
    Type getType() const override {return _type;}

    std::string getValue() const override {return _value;}
    std::pair<long int, long int> getCoords() const override {return _coords;}
    std::tuple<unsigned int, unsigned int, unsigned int, unsigned int> getSpritePos() const override {return _texture;}
    std::tuple<uint, uint, uint, uint> getColor() const override {return std::make_tuple(255,255,255,255);}
    void setCoords(long int x, long int y) {std::get<0>(_coords) = x;std::get<1>(_coords) = y;}

  private:
    std::string _id;
    std::string _path;
    Type _type;
    std::string _value;

    std::pair<long int, long int> _coords; // (x, y)
    std::tuple<unsigned int, unsigned int, unsigned int, unsigned int> _texture; // (x, y, height, width)
};

}

#endif //OOP_ARCADE_2019_MAINMENUOBJECT_HPP
