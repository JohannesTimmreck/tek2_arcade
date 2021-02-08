/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** description
*/

#include <iostream>
#include <fstream>

#include "../include/GameInterface.hpp"
#include "../include/Wall.hpp"

extern "C" games::IGameInterface *entryPoint(void) {
    return new games::GameInterface;
}

namespace games {

GameInterface::GameInterface() : _score(0), _walls(0), _end(false), _state(NOTREADY), _level(1), _lives(3),
_map({
"############################",
"#                          #",
"#                          #",
"#  ####  #  ####  #  ####  #",
"#  #  #  #        #  #  #  #",
"#  #  #  #        #  #  #  #",
"#  ####  #  #  #  #  ####  #",
"#        #  #  #  #        #",
"#        #  #  #  #        #",
"#  #######  #  #  #######  #",
"#  #                    #  #",
"#  #                    #  #",
"#  #  #######  #######  #  #",
"#                          #",
"#                          #",
"#  #######  ####  #######  #",
"#           #  #           #",
"#           #  #           #",
"#  ####  #  ####  #  ####  #",
"#  #  #  #        #  #  #  #",
"#  #  #  #        #  #  #  #",
"#  ####  #  ####  #  ####  #",
"#        #  #  #  #        #",
"#        #  #  #  #        #",
"#  #######  ####  #######  #",
"#                          #",
"#                          #",
"############################"})
{
  //assets
    _assets.push_back(new Wall(0,0));
    _assets.push_back(new Fruit(0,0));
    _assets.push_back(new Head(0, 0));
    _assets.push_back(new Body(0, 0));
    _assets.push_back(new Text);
    _assets.push_back(new Text("score"));
    _assets.push_back(new Text("time"));
    _lastFrame = std::chrono::steady_clock::now();
};

GameInterface::~GameInterface() {
    saveScores();
    _objects.clear();
    _assets.clear();
    _snake.clear();
    _scores.clear();
    _fruits.clear();
}

COMMAND GameInterface::applyInput(COMMAND userInput) {
    if (_end)
        return MAIN_MENU;
    if (_state != GAME) {
        switch (userInput) {
            case UP:
            case DOWN:
            case RIGHT:
            case LEFT:
                return NO_INPUT;
            default:return userInput;
        }
    }
    switch (userInput) {
        case UP:static_cast<Head *>(_snake.at(0))->turn(Head::UP);break;
        case RIGHT:static_cast<Head *>(_snake.at(0))->turn(Head::RIGHT);break;
        case LEFT:static_cast<Head *>(_snake.at(0))->turn(Head::LEFT);break;
        case DOWN:static_cast<Head *>(_snake.at(0))->turn(Head::DOWN);break;
        default:return userInput;
    }
    return NO_INPUT;
}

void GameInterface::createWalls() {
    unsigned long tileSize = 32;
    _walls = 0;
    for (size_t line = 0; line < _map.size(); line++) {
        for (size_t character = 0; character < _map.at(line).length(); character++) {
            if (_map[line][character] == '#') {
                _objects.push_back(new Wall(line * tileSize, character * tileSize));
                _walls++;
            }
        }
    }
}

void GameInterface::createFruits() {
    unsigned long tileSize = 32;

    _fruits.push_back(new Fruit(  1 * tileSize,   4 * tileSize));
    _fruits.push_back(new Fruit(  1 * tileSize,  10 * tileSize));
    _fruits.push_back(new Fruit(  1 * tileSize,  16 * tileSize));
    _fruits.push_back(new Fruit(  1 * tileSize,  22 * tileSize));
    _fruits.push_back(new Fruit(  4 * tileSize,  1 * tileSize));
    _fruits.push_back(new Fruit(  4 * tileSize,  7 * tileSize));
    _fruits.push_back(new Fruit(  4 * tileSize,  19 * tileSize));
    _fruits.push_back(new Fruit(  4 * tileSize,  25 * tileSize));
    _fruits.push_back(new Fruit(  7 * tileSize,  10 * tileSize));
    _fruits.push_back(new Fruit(  7 * tileSize,  16 * tileSize));
    _fruits.push_back(new Fruit(  10 * tileSize,  1 * tileSize));
    _fruits.push_back(new Fruit(  10 * tileSize,  6 * tileSize));
    _fruits.push_back(new Fruit(  10 * tileSize,  20 * tileSize));
    _fruits.push_back(new Fruit(  10 * tileSize,  25 * tileSize));
    _fruits.push_back(new Fruit(  12 * tileSize,   13 * tileSize));
    _fruits.push_back(new Fruit(  13 * tileSize,   6 * tileSize));
    _fruits.push_back(new Fruit(  13 * tileSize,   20 * tileSize));
    _fruits.push_back(new Fruit(  16 * tileSize,  4 * tileSize));
    _fruits.push_back(new Fruit(  16 * tileSize,  22 * tileSize));
    _fruits.push_back(new Fruit(  21 * tileSize,  1 * tileSize));
    _fruits.push_back(new Fruit(  21 * tileSize,  7 * tileSize));
    _fruits.push_back(new Fruit(  21 * tileSize,  10 * tileSize));
    _fruits.push_back(new Fruit(  21 * tileSize,  25 * tileSize));
    _fruits.push_back(new Fruit(  23 * tileSize,  1 * tileSize));
    _fruits.push_back(new Fruit(  23 * tileSize,  25 * tileSize));
    for (size_t i = 0; i < _fruits.size(); i++)
        _objects.push_back(_fruits.at(i));
}

void GameInterface::createSnake() {
    unsigned long tileSize = 32;
    for (int i = 0; i < _objects.size(); ++i) {
        if (_objects[i]->getId() == "body" || _objects[i]->getId() == "head") {
            _objects.erase(_objects.begin() + i);
            i -= 1;
        }
    }
    _snake.push_back(new Head(  25 * tileSize,   16 * tileSize));
    _snake.push_back(new Body(  25 * tileSize,   14 * tileSize));
    _snake.push_back(new Body(  25 * tileSize,   12 * tileSize));
    _snake.push_back(new Body(  25 * tileSize,   10 * tileSize));
    _snake.push_back(new Body(  25 * tileSize,   8 * tileSize));
    for (size_t i = 0; i < _snake.size(); i++)
        _objects.push_back(_snake.at(i));
}

void GameInterface::move() {
    if (static_cast<Head *>(_snake.at(0))->checkBlocked(_map))
        return;
    for (int i = _snake.size() - 1; i > 0; --i)
        _snake.at(i)->move(_snake.at(i-1));
    _snake.at(0)->move(nullptr);
}

void GameInterface::eatFruit() {
    for (size_t it = 0; it < _fruits.size(); it++) {
        if (_objects.at(_walls + it)->getCoords() == _snake.at(0)->getCoords()) {
            _objects.erase(_objects.begin() + _walls + it);
            _fruits.erase(_fruits.begin() + it);
            _snake.push_back(new Body(std::get<1>(_snake.at(_snake.size() - 1)->getCoords()), std::get<0>(_snake.at(_snake.size() - 1)->getCoords())));
            _objects.push_back(_snake.at(_snake.size() - 1));
            std::get<1>(_scores.at(_score)) += 10 * _level;
            updateScores();
            return;
        }
    }
}

bool GameInterface::checkSnakeCollision() {
    for (size_t it = 1; it < _snake.size(); it++) {
        if (_snake.at(it)->getCoords() == _snake.at(0)->getCoords()) {
            _lives--;
            switchToEnd();
            return false;
        }
    }
    return true;
}

void GameInterface::updateTime(std::chrono::time_point<std::chrono::steady_clock> currentTime) {
    if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - _gameTime).count() < 750)
        return;
    _gameTime = std::chrono::steady_clock::now();
    _time -= 10;
    if (_time == 0) {
        _lives--;
        switchToEnd();
        return;
    }
    for (int i = 0; i < _objects.size(); ++i) {
        if (_objects[i]->getId() == "time") {
            static_cast<Text *>(_objects[i])->setString(std::string("Time: " + std::to_string(_time)));
            break;
        }
    }
}

void GameInterface::prepareTexts() {
    _time = 990;
    _gameTime = std::chrono::steady_clock::now();
    _objects.push_back(new Text("time", "Time: " + std::to_string(_time),  30 * 32, 2 * 32));
    _objects.push_back(new Text("text", "Lives: " + std::to_string(_lives),  30 * 32, 3 * 32));
    _objects.push_back(new Text("text", "Level: " + std::to_string(_level),  30 * 32, 4 * 32));
    _objects.push_back(new Text("text", "Highscores",  30 * 32, 6 * 32));
    for (size_t i = 0; i < _scores.size(); i++)
        _objects.push_back(new Text("score", std::get<0>(_scores[i]) + " " + std::to_string(std::get<1>(_scores[i])),  30 * 32, (i + 7) * 32));
}

bool GameInterface::start() {
    _objects.clear();
    _countdown = 4;
    loadScores();
    if (_level % 4 == 0)
        _lives += 1;
    _objects.push_back(new Text("text", "Game loads", 820, 500));
    _objects.push_back(new Text("text", "Level: " + std::to_string(_level), 820, 532));
    _objects.push_back(new Text("text", "Lives: " + std::to_string(_lives), 820, 564));
    if (_level != 1)
        _objects.push_back(new Text("text", "Your score: " + std::to_string(_scores[_score].second), 820, 596));
    _timer = std::chrono::steady_clock::now();
    _state = PREGAME;
    return true;
}

void GameInterface::beginning(std::chrono::time_point<std::chrono::steady_clock> currentTime) {
    if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - _timer).count() > 4 - _countdown) {
        _countdown--;
        static_cast<Text *>(_objects[0])->setString("Game starts in " + std::to_string(_countdown));
        if (_countdown == 0)
            switchToGame();
    }
}

void GameInterface::switchToGame() {
    _objects.clear();
    createWalls();
    createFruits();
    createSnake();
    prepareTexts();
    _state = GAME;
}

void GameInterface::game(std::chrono::time_point<std::chrono::steady_clock> currentTime) {
    move();
    if (!checkSnakeCollision())
        return;
    eatFruit();
    if (_fruits.empty()) {
        _scores[_score].second += _time * _level;
        _scores[_score].second += _snake.size() * 20 * _level;
        updateScores();
        _level += 1;
        switchToEnd();
    }
    updateTime(currentTime);
}

void GameInterface::switchToEnd() {
    _objects.clear();
    _snake.clear();
    if (_fruits.empty()) {
        start();
        return;
    }
    _countdown = 4;
    _objects.push_back(new Text("text", "Your score: " + std::to_string(_scores[_score].second), 820, 532));
    if (_lives == 0) {
        _objects.push_back(new Text("text", "Go back to main menu in " + std::to_string(_countdown), 820, 500));
    } else {
        _objects.push_back(new Text("text", "Restart in " + std::to_string(_countdown), 820, 500));
        _objects.push_back(new Text("text", "Level: " + std::to_string(_level), 820, 564));
        _objects.push_back(new Text("text", "Your Lives: " + std::to_string(_lives), 820, 596));
    }
    _timer = std::chrono::steady_clock::now();
    _state = POSTGAME;
}

void GameInterface::ending(std::chrono::time_point<std::chrono::steady_clock> currentTime) {
    if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - _timer).count() > 4 - _countdown) {
        _countdown--;
        if (_lives == 0)
            static_cast<Text *>(_objects[1])->setString(
                "Go back to main menu in " + std::to_string(_countdown));
        else
            static_cast<Text *>(_objects[1])->setString(
                "Restart in " + std::to_string(_countdown));
        if (_countdown != 0)
            return;
        if (_lives == 0) {
            saveScores();
            _end = true;
        } else {
            reset();
        }
    }
}

void GameInterface::reset() {
    _objects.clear();
    createWalls();
    for (size_t i = 0; i < _fruits.size(); i++)
        _objects.push_back(_fruits.at(i));
    createSnake();
    prepareTexts();
    _time = 990;
    _state = GAME;
}

std::vector<IObjectToDraw *> GameInterface::compute() {
    std::chrono::time_point<std::chrono::steady_clock> currentTime = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - _lastFrame).count() < 166)
        return _objects;
    switch (_state) {
        case PREGAME:beginning(currentTime);break;
        case GAME:game(currentTime);break;
        case POSTGAME:ending(currentTime);break;
        default:std::cerr << "Nibbler: Parts of the game are not initialized" << std::endl;break;
    }
    _lastFrame = std::chrono::steady_clock::now();
    return _objects;
}

void GameInterface::loadScores() {
    if (!_scores.empty())
        return;
    std::fstream fs;
    fs.open("./games/Nibbler/.highscore.txt", std::ios::out | std::ios::app);
    fs.close();
    std::ifstream scoreFile("./games/Nibbler/.highscore.txt");
    for(std::string line; std::getline(scoreFile, line);)
        _scores.push_back(std::pair<std::string, unsigned int>(line.substr(0, line.find_last_of(" ")), std::stoi(line.substr(line.find_last_of(" "), line.size()))));
    _scores.push_back(std::pair<std::string, unsigned int>(_username, 0));
    _score = _scores.size() - 1;
}

void GameInterface::updateScores() {
    while (_score != 0 && std::get<1>(_scores.at(_score)) > std::get<1>(_scores.at(_score - 1))) {
        _score -= 1;
        _scores.emplace( _scores.begin() + _score, _scores.at(_score + 1));
        _scores.erase( _scores.begin() + _score + 2);
    }
    for (int i = 0; i < _objects.size(); ++i) {
        if (_objects[i]->getId() == "score") {
            _objects.erase(_objects.begin() + i);
            i -= 1;
        }
    }
    for (size_t i = 0; i < _scores.size(); i++) {
        _objects.push_back(new Text("score",
            std::get<0>(_scores[i]) + " " + std::to_string(std::get<1>(_scores[i])),
                                    30 * 32, (i + 7) * 32));
    }
}

void GameInterface::saveScores() {
    std::ofstream saveFile("./games/Nibbler/.highscore.txt");
    for (int x = 0; x != _scores.size() && x != 10; x++) {
        saveFile << std::string(_scores.at(x).first + " " + std::to_string(_scores.at(x).second));
        if (x + 1 != _scores.size() && x + 1 != 10)
            saveFile << std::endl;
    }
}

} // namespace games