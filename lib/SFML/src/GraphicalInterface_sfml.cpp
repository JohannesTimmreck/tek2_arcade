/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** GraphicalInterface_sfml
*/

#include "../include/GraphicalInterface_sfml.hpp"


extern "C" graphical::IGraphicalInterface *entryPoint(void)
{
    return new graphical::GraphicalInterface_sfml;
}

graphical::GraphicalInterface_sfml::GraphicalInterface_sfml()
{
    std::cout << "Graphics: created SFML lib Interface" << std::endl;
}

graphical::GraphicalInterface_sfml::~GraphicalInterface_sfml()
{
    std::cout << "Graphics: destroy SFML lib Interface" << std::endl;
}

bool graphical::GraphicalInterface_sfml::init()
{
    std::cout << "Graphics: opening SFML window" << std::endl;
    _window.create(sf::VideoMode(1920, 1080), "Arcade");
    return true;
}

bool graphical::GraphicalInterface_sfml::initAssets(std::vector<IObjectToDraw *> assets)
{
    for (size_t i = 0; i < assets.size(); i++)
        _assets.push_back(Asset(assets[i]->getPath(), assets[i]->getType(), assets[i]->getId()));
    return true;
}

bool graphical::GraphicalInterface_sfml::destroyAssets()
{
    _assets.clear();
    return true;
}

bool graphical::GraphicalInterface_sfml::destroy()
{
    _window.close();
    std::cout << "Graphics: SFML window closed" << std::endl;
    return true;
}

COMMAND graphical::GraphicalInterface_sfml::getInput()
{
    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            return EXIT;
        else if (_event.type == sf::Event::KeyPressed) {
            if (_event.key.code == sf::Keyboard::W || _event.key.code == sf::Keyboard::Up)
                return UP;
            else if (_event.key.code == sf::Keyboard::A || _event.key.code == sf::Keyboard::Left)
                return LEFT;
            else if (_event.key.code == sf::Keyboard::D || _event.key.code == sf::Keyboard::Right)
                return RIGHT;
            else if (_event.key.code == sf::Keyboard::S || _event.key.code == sf::Keyboard::Down)
                return DOWN;
            else if (_event.key.code == sf::Keyboard::U)
                return PREV_GRAPH;
            else if (_event.key.code == sf::Keyboard::I)
                return NEXT_GRAPH;
            else if (_event.key.code == sf::Keyboard::J)
                return PREV_GAME;
            else if (_event.key.code == sf::Keyboard::K)
                return NEXT_GAME;
            else if (_event.key.code == sf::Keyboard::R)
                return RESTART;
            else if (_event.key.code == sf::Keyboard::M)
                return MAIN_MENU;
            else if (_event.key.code == sf::Keyboard::Q)
                return EXIT;
        }
    }
    return NO_INPUT;
}

bool graphical::GraphicalInterface_sfml::draw(std::vector<IObjectToDraw *> objects)
{
    _window.clear();
    for (size_t i = 0; i < objects.size(); i++) {
        for (size_t j = 0; j < _assets.size(); j++) {
            if (objects[i]->getId() == _assets[j].getId()) {
                _assets[j].handle(objects[i], _window);
                break;
            }
        }
    }
    _window.display();
    return true;
}