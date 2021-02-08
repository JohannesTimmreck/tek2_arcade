/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** description
*/

#include <dirent.h>
#include <cstring>
#include <cstdio>

#include "../include/Core.hpp"
#include "../include/MainMenu.hpp"

namespace core {

std::vector<std::string> Core::getLibraries(std::string path)
{
    std::vector<std::string> files;
    DIR *dir;
    struct dirent *ent;
    size_t nameLength;

    if ((dir = opendir(path.c_str())) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            nameLength = strlen(ent->d_name);
            if (ent->d_name[nameLength-1] == 'o'
             && ent->d_name[nameLength-2] == 's'
             && ent->d_name[nameLength-3] == '.')
                files.push_back(std::string(path + "/" + ent->d_name));
        }
        closedir (dir);
    } else
        perror ("Core: ");
    return files;
}

Core::Core(char *graphicsLibrary) :
    _availableGraphics(Core::getLibraries("lib")),
    _curGraphics(256),
    _graphicLoader(nullptr),
    _graphics(nullptr),
    _availableGames(Core::getLibraries("games")),
    _curGame(0),
    _gameLoader(nullptr),
    _game(nullptr),
    _userInput(NO_INPUT)
{
    for (size_t i  = 0; i < _availableGraphics.size(); i++) {
        if (graphicsLibrary == _availableGraphics[i] || graphicsLibrary == "./" + _availableGraphics[i]) {
            _curGraphics = i;
            break;
        }
    }
    if (_curGraphics == 256) {
        std::cerr << "Core: Chosen library " << graphicsLibrary << " not found" << std::endl;
        return;
    }
    std::cout << "Please enter your username:" << std::endl;
    std::cin >> _username;

    _game = new MainMenu(_availableGames, _availableGraphics);
    _game->setUsername(_username);
    if (!loadGraphics())
        return;
}

Core::~Core () {
    if (_graphics) {
        _graphics->destroyAssets();
        _graphics->destroy();
    }
    delete _graphics;
    delete _graphicLoader;
    if (_game)
        _game->end();
    delete _game;
    delete _gameLoader;
    _availableGames.clear();
    _availableGraphics.clear();
}

bool Core::loadGame() {
    if (_game) {
        _game->end();
        _graphics->destroyAssets();
    }
    delete _game;
    _game = nullptr;
    delete _gameLoader;
    _gameLoader = new DLLoader<games::IGameInterface>(_availableGames[_curGame]);
    if (!_gameLoader || !gameLoaded())
        return false;
    _game = _gameLoader->_getInstance();
    if (!_game) {
        std::cerr << "Core: Cant get instance of chosen game: " << _availableGames[_curGame] << std::endl;
        return false;
    }
    _game->setUsername(_username);
    if (!_graphics->initAssets(_game->getAssets())) {
        std::cerr << "Core: Cant set assets for chosen game: " << _availableGames[_curGame] << " to library " << _availableGraphics[_curGraphics] << std::endl;
        delete _gameLoader;
        return false;
    }
    _game->start();
    return true;
}

bool Core::loadGraphics()
{
    if (_graphics) {
        _graphics->destroyAssets();
        _graphics->destroy();
    }
    delete _graphics;
    _graphics = nullptr;
    delete _graphicLoader;

    _graphicLoader = new DLLoader<graphical::IGraphicalInterface>(_availableGraphics[_curGraphics]);
    if (!_graphicLoader || !_graphicLoader->loaded())
        return false;
    _graphics = _graphicLoader->_getInstance();
    _graphics->init();
    _graphics->initAssets(_game->getAssets());
    return true;
}

int Core::loop () {
    _lastFrame = std::chrono::steady_clock::now();
    while (_userInput != EXIT) {
        _currentTime = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(_currentTime - _lastFrame).count() > 16.6) {
            _userInput = _graphics->getInput();
            applyUserInput();
            if (!_graphics->draw(_game->compute()))
                std::cerr << "Core: Couldn't draw frame" << std::endl;
            _lastFrame = std::chrono::steady_clock::now();
        }
    }
    return 0;
}

int Core::applyUserInput()
{
    _userInput = _game->applyInput(_userInput);
    switch (_userInput) {
        case NO_INPUT:
            break;
        case PREV_GRAPH:
            if (_curGraphics == 0)
                _curGraphics = static_cast<int>(_availableGraphics.size() - 1);
            else
                _curGraphics -= 1;
            if (!loadGraphics())
                _userInput = EXIT;
            break;
        case NEXT_GRAPH:
            if (_curGraphics == _availableGraphics.size() - 1)
                _curGraphics = 0;
            else
                _curGraphics += 1;
            if (!loadGraphics())
                _userInput = EXIT;
            break;
        case PREV_GAME:
            if (_curGame == 0)
                _curGame = static_cast<int>(_availableGames.size() - 1);
            else
                _curGame -= 1;
            if (!loadGame())
                _userInput = EXIT;
            break;
        case NEXT_GAME:
            if (_curGame == _availableGames.size() - 1)
                _curGame = 0;
            else
                _curGame += 1;
            if (!loadGame())
                _userInput = EXIT;
            break;
        case RESTART:
            if (!loadGame())
                _userInput = EXIT;
            break;
        case MAIN_MENU:
            _game->end();
            _graphics->destroyAssets();
            delete _game;
            delete _gameLoader;
            _gameLoader = nullptr;
            _game = new MainMenu(_availableGames, _availableGraphics);
            _curGame = 0;
            _game->setUsername(_username);
            _graphics->initAssets(_game->getAssets());
            break;
        case EXIT:
            break;
        case UP:
            if (_curGame > 0)
                _curGame -= 1;
            break;
        case DOWN:
            if (_curGame < _availableGames.size() - 1)
                _curGame += 1;
            break;
        case GAME:
            if (!loadGame())
                _userInput = EXIT;
            break;
        default:
            return -1;
    }
    return -1;
}

} // namespace core