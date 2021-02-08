/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** description
*/

#ifndef OOP_ARCADE_2019_SNAKE_HPP
#define OOP_ARCADE_2019_SNAKE_HPP

#include "../../../GlobalHeaders.hpp"

namespace games {

class Snake : public IObjectToDraw
{
  public:
    enum Direction
    {
        RIGHT = 0,
        UP,
        LEFT,
        DOWN
    };
  protected:
    std::pair<long int, long int> _coords;
    std::pair<long int, long int> _lastCoords;
    Direction _direction;
  public:
    Snake(long int y, long int x) : _coords(std::make_pair(x, y)), _lastCoords(std::make_pair(x, y)), _direction(RIGHT) {};
    ~Snake() = default;

    Type getType() const override {return objects;}
    std::string getValue() const override {return "";}
    std::pair<long int, long int> getCoords()  const override {return _coords;}
    std::pair<long int, long int> getLastCoords()  const {return _lastCoords;}
    Direction getDirection() const {return _direction;}
    virtual void move(Snake *part) = 0;
};

class Body : public Snake {
  public:
    Body(long int y, long int x) : Snake(y, x) {}
    ~Body() = default;
    std::string getId() const override {return std::string("body");}
    std::string getPath() const override {return std::string("games/Nibbler/assets/body/");}
    std::tuple<unsigned int, unsigned int, unsigned int, unsigned int> getSpritePos() const override {return std::make_tuple(0, 0, 64, 64);}
    std::tuple<uint, uint, uint, uint> getColor() const override {return std::make_tuple(0,0,0,0);};
    void move(Snake *part) override;
};

class Head : public Snake {
  private:
    Direction _nextDirection;
  public:
    Head(long int y, long int x) : Snake(y, x), _nextDirection(RIGHT) {}
    ~Head() = default;
    std::string getId() const override {return std::string("head");}
    std::string getPath() const override {return std::string("games/Nibbler/assets/head");}
    std::tuple<unsigned int, unsigned int, unsigned int, unsigned int> getSpritePos() const override {return std::make_tuple(64 * _direction, 0, 64, 64);}
    std::tuple<uint, uint, uint, uint> getColor() const override {return std::make_tuple(0,0,0,0);};
    void turn(Direction direction);
    void move(Snake *part) override;
    bool checkBlocked(std::array<std::string, 32> &map);
};

} // namespace games

#endif //OOP_ARCADE_2019_SNAKE_HPP
