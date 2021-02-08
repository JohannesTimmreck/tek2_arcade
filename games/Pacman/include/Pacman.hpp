/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** description
*/

#ifndef OOP_ARCADE_2019_PACMAN_HPP
#define OOP_ARCADE_2019_PACMAN_HPP

#include <array>
#include <string>

#include "../../IGameInterface.hpp"
#include <tuple>
#include <chrono>

namespace games {

class Pacman : public IGameInterface
{
  public:
    enum MOVEMENT {
      UP,
      DOWN,
      LEFT,
      RIGHT
    };
    Pacman();
    ~Pacman();
    bool start();       // initialize game
    bool end();         // end game
    void setUsername(std::string username) override { _username = username; };             // set username for display of score
    COMMAND applyInput (COMMAND userInput) override;  // apply user input
    std::vector<IObjectToDraw *>getAssets() const override { return _assets; };              // return the assets for display
    std::vector<IObjectToDraw *> compute() override;    // calculate next game frame and return 

    void moveGhost(IObjectToDraw *ghost, int x);
    void movePlayer(IObjectToDraw *player);
    bool checkPlayerCollision(IObjectToDraw *player);
    void createAssets();
    void createObjects();
    void resetGame();
  private:
    int _playerX;
    int _playerY;
    MOVEMENT _currentMove;
    MOVEMENT _nextMove;
    unsigned int _score;
    unsigned int _dotsLeft;
    unsigned int _lives;
    std::string _username;
    std::vector<std::pair<std::string, unsigned int>> _oldScores;
    std::array<std::string, 32> _map;
    std::vector<IObjectToDraw *> _assets;
    std::vector<IObjectToDraw *> _objects;
    std::vector<IObjectToDraw *> _countdown;
    std::vector<std::pair<MOVEMENT, std::string>> _ghostMovement;
    std::chrono::time_point<std::chrono::steady_clock> _startCountdown;
    std::chrono::time_point<std::chrono::steady_clock> _ghostSpawn;
    std::chrono::time_point<std::chrono::steady_clock> _ghostModeTime;
    std::chrono::time_point<std::chrono::steady_clock> _playerTime;
    std::chrono::time_point<std::chrono::steady_clock> _ghostTime;
    std::chrono::time_point<std::chrono::steady_clock> _DeadTime;
    std::chrono::time_point<std::chrono::steady_clock> _fleeTime;
    bool _chase;
    bool _flee;
    bool _ghostActive;
    unsigned int _killCounter;
    unsigned int _start;
    unsigned int _ghostComputeSpeed;
};

} // namespace games

class Ghost :  public IObjectToDraw {
  public:
    Ghost(std::string id, std::string Path, Type type ,std::string value, long int x, long int y,
    unsigned int spriteX, unsigned int spriteY, unsigned int spriteHeight, unsigned int spriteWidth,
    int red, int green, int blue, int alpha,
    unsigned int scatterX, unsigned int scatterY, unsigned int startX, unsigned int startY);
    ~Ghost() = default;
    std::string getId() const override {return _id;};                       // get id which instances of this type get referenced to
    std::string getPath() const override {return _path;};                   // get path to the 2d texture
    Type getType() const override {return _type;};                                 // get enum Type [objects|text]
    std::string getValue() const override {return _value;};                         // get string to display for texts
    std::pair<long int, long int> getCoords() const override {return _coords;};  // get the coordinates of the current instance (x, y)
    std::tuple<unsigned int, unsigned int, unsigned int, unsigned int> getSpritePos() const override {return _spritePos;};
    std::tuple<uint, uint, uint, uint> getColor() const override { return _color; };
    void setCoords(long int x, long int y) {_coords = std::pair<long int, long int>(x, y);};
    void setSpritePos(unsigned int x, unsigned int y, unsigned int height, unsigned int width) { _spritePos = std::tuple<unsigned int, unsigned int, unsigned int, unsigned int>(x,y,height,width); };
    void setValue(std::string newValue) {_value = newValue;};

    void setDead(bool dead) {_dead = dead;};
    bool getDead() {return _dead;};
    void setFlee(bool flee) {_flee = flee;};
    bool getFlee() {return _flee;};
    void setInside(bool inside) {_inside = inside;};
    bool getInside() {return _inside;};
    std::pair<unsigned int, unsigned int> getScatterField() {return _scatterField;};
    std::pair<unsigned int, unsigned int> getStartField() {return _startField;};
  private:
    std::string _id;
    std::string _path;
    Type _type;
    std::string _value;
    std::pair<long int, long int> _coords;
    std::tuple<unsigned int, unsigned int, unsigned int, unsigned int> _spritePos;
    std::tuple<uint, uint, uint, uint> _color;
    bool _dead;
    bool _flee;
    bool _inside;
    std::pair<unsigned int, unsigned int> _startField;
    std::pair<unsigned int, unsigned int> _scatterField;
};

class ObjectToDraw : public IObjectToDraw {
  public:
    ObjectToDraw(std::string id, std::string Path, Type type ,std::string value, long int x, long int y,
    unsigned int spriteX, unsigned int spriteY, unsigned int spriteHeight, unsigned int spriteWidth,
    int red, int green, int blue, int alpha);
    ~ObjectToDraw() = default;
    std::string getId() const override {return _id;};                       // get id which instances of this type get referenced to

    std::string getPath() const override {return _path;};                   // get path to the 2d texture
    Type getType() const override {return _type;};                                 // get enum Type [objects|text]

    std::string getValue() const override {return _value;};                         // get string to display for texts
    std::pair<long int, long int> getCoords() const override {return _coords;};  // get the coordinates of the current instance (x, y)
    std::tuple<unsigned int, unsigned int, unsigned int, unsigned int> getSpritePos() const override {return _spritePos;};
    std::tuple<uint, uint, uint, uint> getColor() const override { return _color; };

    void setCoords(long int x, long int y) {_coords = std::pair<long int, long int>(x, y);};
    void setSpritePos(unsigned int x, unsigned int y, unsigned int height, unsigned int width) { _spritePos = std::tuple<unsigned int, unsigned int, unsigned int, unsigned int>(x,y,height,width); };
    void setValue(std::string newValue) {_value = newValue;};
  private:
    std::string _id;
    std::string _path;
    Type _type;
    std::string _value;
    std::pair<long int, long int> _coords;
    std::tuple<unsigned int, unsigned int, unsigned int, unsigned int> _spritePos;
    std::tuple<uint, uint, uint, uint> _color;
};

#endif //OOP_ARCADE_2019_IGAMEINTERFACE_HPP
