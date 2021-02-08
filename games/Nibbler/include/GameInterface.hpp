/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** description
*/

#ifndef OOP_ARCADE_2019_GAMEINTERFACE_HPP
#define OOP_ARCADE_2019_GAMEINTERFACE_HPP

#include <chrono>

#include "../../IGameInterface.hpp"
#include "../include/Snake.hpp"
#include "../include/Fruit.hpp"
#include "../include/Text.hpp"

namespace games {

class GameInterface : public IGameInterface
{
  private:
    enum State {
        NOTREADY,
        PREGAME,
        GAME,
        POSTGAME
    };
    std::vector<IObjectToDraw *> _assets;
    std::vector<IObjectToDraw *> _objects;
    std::vector<Snake *> _snake;
    std::vector<Fruit *> _fruits;
    std::string _username;
    unsigned int _score;
    std::vector<std::pair<std::string, unsigned int>> _scores;
    std::chrono::time_point<std::chrono::steady_clock> _lastFrame;
    std::chrono::time_point<std::chrono::steady_clock> _timer;
    std::chrono::time_point<std::chrono::steady_clock> _gameTime;

    unsigned int _countdown;
    unsigned int _walls;
    State _state;
    bool _end;
    unsigned int _time;
    unsigned int _level;
    unsigned int _lives;
    std::array<std::string, 32> _map;

    void createWalls();
    void createFruits();
    void createSnake();

    void prepareTexts();

    void loadScores();
    void updateScores();
    void saveScores();
    void move();
    void eatFruit();
    bool checkSnakeCollision();
    void updateTime(std::chrono::time_point<std::chrono::steady_clock> currentTime);

    void beginning(std::chrono::time_point<std::chrono::steady_clock> currentTime);
    void switchToGame();
    void game(std::chrono::time_point<std::chrono::steady_clock> currentTime);
    void switchToEnd();
    void reset();
    void ending(std::chrono::time_point<std::chrono::steady_clock> currentTime);
  public:
    GameInterface();
    ~GameInterface();
    bool start() override;
    virtual void setUsername(std::string username) {_username = username;}
    std::vector<IObjectToDraw *> getAssets() const override {return _assets;}
    bool end() override {return true;}

    COMMAND applyInput(COMMAND userInput) override;
    std::vector<IObjectToDraw *> compute() override;
};

} // namespace games

#endif //OOP_ARCADE_2019_GAMEINTERFACE_HPP
