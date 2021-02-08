/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** description
*/

#ifndef OOP_ARCADE_2019_GLOBALHEADERS_HPP
#define OOP_ARCADE_2019_GLOBALHEADERS_HPP

#include <utility>
#include <string>
#include <tuple>

enum COMMAND {
    NO_INPUT,
  // change libraries
    PREV_GRAPH,
    NEXT_GRAPH,
    PREV_GAME,
    NEXT_GAME,
  // change game state
    RESTART,
    PAUSE,
    MAIN_MENU,
    GAME,
    EXIT,
  // game relevant user input
    UP,
    RIGHT,
    DOWN,
    LEFT,
  // TYPE BACK_SPACE KEY
    ACTION
};

class IObjectToDraw {
  public:
    enum Type {
        objects,
        text
    };
    virtual ~IObjectToDraw() = default;
    // get id which instances of this type get referenced to
    virtual std::string getId() const = 0;
    // path to directory of assets [terminal.txt, texture.png, mesh.*]
    virtual std::string getPath() const = 0;
    // get enum Type [objects|text]
    virtual Type getType() const = 0;
    // get string to display for texts
    virtual std::string getValue() const = 0;
    // get the coordinates of the current instance (x, y)
    virtual std::pair<long int, long int> getCoords() const = 0;
    // get position of sprite in texture for animation(x, y, width, height)
    virtual std::tuple <uint, uint, uint, uint> getSpritePos() const = 0;
    // get color of the asset(0-255, 0-255, 0-255, 0-255)
    virtual std::tuple<uint, uint, uint, uint> getColor() const = 0;

};

#endif //OOP_ARCADE_2019_GLOBALHEADERS_HPP
