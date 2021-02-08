/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** description
*/

#include <iostream>
#include "../include/Asset.hpp"
#include <fstream>
#include <sstream>
#include <curses.h>
#include <unistd.h>
#include <vector>

namespace graphical {

Asset::Asset(std::string path, IObjectToDraw::Type type, std::string id) :
    _type(type), _id(id)
{
    if (path[path.size() - 1] != '/')
        path.append("/");
    switch(_type) {
        case IObjectToDraw::objects:
            if (!loadSymbolFromFile(path + "terminal.txt")) {
                refresh();
                return;
            }
    }
}

bool Asset::loadSymbolFromFile(std::string path) {
    std::ifstream t(path);
    std::stringstream buffer;
    buffer << t.rdbuf();

    this->_symbol = buffer.str().c_str();
    return (true);
}

void Asset::handle(IObjectToDraw *instance) {
    switch (_type) {
        case IObjectToDraw::objects:
            this->_coords = instance->getCoords();
            if (this->_symbol.c_str() != "0") {
                if (_symbol.find('\n') != std::string::npos) {
                    std::stringstream ss(_symbol.c_str());
                    std::string item;
                    std::vector<std::string> splittedString;
                    while (std::getline(ss, item, '\n'))
                        splittedString.push_back(item);
                    mvprintw(std::get<1>(_coords)/32, std::get<0>(_coords)/32, "%s", splittedString[0].c_str());
                    mvprintw((std::get<1>(_coords)/32) + 1, std::get<0>(_coords)/32, "%s", splittedString[1].c_str());
                } else 
                    mvprintw(std::get<1>(_coords)/32, std::get<0>(_coords)/32, "%s", this->_symbol.c_str());
            }
        case IObjectToDraw::text:
            this->_coords = instance->getCoords();
            mvprintw(std::get<1>(_coords)/32, std::get<0>(_coords)/32, "%s", instance->getValue().c_str());
    }
}

}   