/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** description
*/

#include "../include/GraphicalInterface_ncurses.hpp"
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <tuple>

#include <ncurses.h>

#include <iomanip>
#include <fstream>
#include <sstream>


extern "C" graphical::IGraphicalInterface *entryPoint(void)
{
    return new graphical::GraphicalInterface_ncurses;
}

namespace graphical {

GraphicalInterface_ncurses::GraphicalInterface_ncurses () {
    // std::cout << "created nCurses Graphical Interface" << std::endl;
}

bool GraphicalInterface_ncurses::init() {
    struct winsize width;
    struct winsize length;

    initscr();
    getmaxyx(stdscr, this->m_maxLength, this->m_maxWidth);

    ioctl(0, TIOCGWINSZ, &width);
    this->m_terminalLength = width.ws_row;
    ioctl(0, TIOCGWINSZ, &length);
    this->m_terminalWidth = length.ws_col;

    nodelay(stdscr, true);
    curs_set(0);

    return 0;
}

COMMAND GraphicalInterface_ncurses::getInput() {
    refresh();

    int keys;

    keypad(stdscr, TRUE);
    keys = getch();
    if (keys == KEY_RIGHT || keys == 100)
        return RIGHT;
    else if (keys == KEY_DOWN || keys == 115)
        return DOWN;
    else if (keys == KEY_UP || keys == 119)
        return UP;
    else if (keys == KEY_LEFT || keys == 97)
        return LEFT;
    else if (keys == 117)
        return (PREV_GRAPH);
    else if (keys == 105)
        return (NEXT_GRAPH);
    else if (keys == 106)
        return (PREV_GAME);
    else if (keys == 107)
        return (NEXT_GAME);
    else if (keys == 114)
        return (RESTART);
    else if (keys == 109)
        return (MAIN_MENU);
    else if (keys == 113)
        return (EXIT);
    return NO_INPUT;
}

bool GraphicalInterface_ncurses::initAssets(std::vector<IObjectToDraw *> assets) {
    for (size_t i = 0; i < assets.size(); i++)
        _assets.push_back(Asset(assets[i]->getPath(), assets[i]->getType(), assets[i]->getId()));
    return (true);
}

bool GraphicalInterface_ncurses::draw(std::vector<IObjectToDraw *> objects) {
    clear();
    // refresh();
    for (size_t i = 0; i < objects.size(); i++) {
        for (size_t j = 0; j < _assets.size(); j++) {
            if (objects[i]->getId() == _assets[j].getId()) {
                _assets[j].handle(objects[i]);
                break;
            }
        }
    }
    return (true);
}

GraphicalInterface_ncurses::~GraphicalInterface_ncurses () {
    endwin();
}

}
