/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** description
*/

#include <iostream>
#include <dirent.h>
#include <cstring>

#include "../include/MainMenu.hpp"
#include "../include/MainMenuObject.hpp"

namespace core {

MainMenu::MainMenu(std::vector<std::string> &games, std::vector<std::string> &graphics) :
    _curGame(0),
    _availableGames(games),
    _availableGraphics(graphics) {
    // create assets
    _assets.push_back(new MainMenuObject("background", "core/assets/background/",
        MainMenuObject::objects, "", 0, 0));
    _assets.push_back(new MainMenuObject("title","core/assets/title/", "", 0, 0));
    _assets.push_back(new MainMenuObject("menuPoint", "core/assets/menupoint/", "", 0, 0));
    _assets.push_back(new MainMenuObject("selected", "core/assets/selected/",
        MainMenuObject::objects, "", 0, 0));
    // create objects
    _objects.push_back(new MainMenuObject("background", "core/assets/background/",
        MainMenuObject::objects, "", 0, 0, 0, 0, 1080, 1920));
    _objects.push_back(new MainMenuObject("title", "", "ARCADE MACHINE", (1920 - (strlen("ARCADE MACHINE") * 20))/2, 100));
    int base_y = 300;
    int base_x = 1920/3;
    _objects.push_back(new MainMenuObject("title", "", "MENU", base_x, base_y));
    for (size_t i = 0; i < _availableGames.size(); i++)
        _objects.push_back(
            new MainMenuObject("menuPoint", "", _availableGames[i].substr(17, _availableGames[i].size() - 20), base_x,
                               base_y + (int)((i + 1) * 64)));
    _objects.push_back(new MainMenuObject("menuPoint", "", "Exit", base_x, base_y + (int)(_availableGames.size() + 1) * 64));
    _objects.push_back(new MainMenuObject("selected", "core/assets/selected/",
                                          MainMenuObject::objects, "", base_x - 32, base_y + 64,
                                          0, 0, 20, 20));
    base_x = 1920/3 * 2 - 150;
    _objects.push_back(new MainMenuObject("title", "", "GRAPHICS OVERVIEW", base_x, base_y));
    for (size_t i = 0; i < _availableGraphics.size(); i++) {
        _objects.push_back(
            new MainMenuObject("menuPoint", "", _availableGraphics[i].substr(15, _availableGraphics[i].size() - 18), base_x,
                               base_y + (int) (i + 1) * 64));
    }
    _objects.push_back(new MainMenuObject("title", "", "username: ", (1920 - (strlen("username: ") * 20))/2, 150));
}

MainMenu::~MainMenu() {
    _assets.clear();
    _objects.clear();
    _availableGames.clear();
}

COMMAND MainMenu::applyInput (COMMAND userInput) {
    switch (userInput) {
        case UP:
            if (_curGame == 0)
                break;
            _curGame--;
            for (size_t i = 0; i < _objects.size(); i++) {
                if (_objects[i]->getId() == "selected")
                    dynamic_cast<MainMenuObject *>(_objects[i])->setCoords(std::get<0>(_objects[_curGame + 2]->getCoords()) - 32, std::get<1>(_objects[i]->getCoords()) - 64);
            }
            break;
        case RIGHT:
            if (_curGame < _availableGames.size()) {
                std::cout << "Game: Chosen Game: " << _availableGames[_curGame] << std::endl;
                return GAME;
            }
            else {
                std::cout << "Game: Chosen Exit " << _curGame << std::endl;
                return EXIT;
            }
        case DOWN:
            if (_curGame == _availableGames.size())
                break;
            _curGame++;
            for (size_t i = 0; i < _objects.size(); i++) {
                if (_objects[i]->getId() == "selected")
                    dynamic_cast<MainMenuObject *>(_objects[i])->setCoords(std::get<0>(_objects[_curGame + 2]->getCoords()) - 32, std::get<1>(_objects[i]->getCoords()) + 64);
            }
            break;
        case LEFT:break;
        case NEXT_GAME:return NO_INPUT;
        case PREV_GAME:return NO_INPUT;
        case MAIN_MENU:return NO_INPUT;
        case RESTART:return NO_INPUT;
        default:break;
    }
    return userInput;
}

void MainMenu::setUsername(std::string username) {
    username.insert(0, "username: ");
    _objects.pop_back();
    _objects.push_back(new MainMenuObject("title", "", username, (1920 - (username.size() * 20))/2, 150));
}

std::vector<IObjectToDraw *> MainMenu::compute() {
    return _objects;
}

}