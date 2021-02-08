/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** description
*/

#ifndef OOP_ARCADE_2019_CORE_HPP
#define OOP_ARCADE_2019_CORE_HPP

#include <string>
#include <vector>
#include <chrono>

#include "../../GlobalHeaders.hpp"
#include "../../lib/IGraphicalInterface.hpp"
#include "../../games/IGameInterface.hpp"

#include "DLLoader.hpp"

namespace core {

class Core
{
  public:
  private:
  // libraries
    std::vector<std::string> _availableGraphics;
    int _curGraphics;
    DLLoader<graphical::IGraphicalInterface> *_graphicLoader;
    graphical::IGraphicalInterface *_graphics;
    std::vector<std::string> _availableGames;
    int _curGame;
    DLLoader<games::IGameInterface> *_gameLoader;
    games::IGameInterface *_game;


    std::string _username;
    std::chrono::time_point<std::chrono::steady_clock> _lastFrame;
    std::chrono::time_point<std::chrono::steady_clock> _currentTime;
    COMMAND _userInput;

    bool loadGraphics();
    bool loadGame();
    static std::vector<std::string> getLibraries(std::string path);
  public:
    explicit Core(char *graphicsLibrary);
    ~Core();
    bool graphicsLoaded()
        {if (_graphicLoader) return _graphicLoader->loaded();else return false;}
    bool gameLoaded() {
        if (_gameLoader) return _gameLoader->loaded();else return false;}
    int loop(); // main program loop
    int applyUserInput();
};

} // namespace core

#endif //OOP_ARCADE_2019_CORE_HPP
