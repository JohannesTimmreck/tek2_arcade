/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** GhostAI
*/

#include "../include/Pacman.hpp"
#include <math.h>
#include <iostream>

float getDistance(int ghostX, int ghostY, int playerX, int playerY)
{
    float res = 0;

    res = pow(ghostX - playerX, 2) + pow(ghostY - playerY, 2);
    res = pow(res, 0.5f);
    return res;
}

std::pair<long int, long int> calculatePinkTarget(
games::Pacman::MOVEMENT playerMove, int playerX, int playerY)
{
    switch (playerMove)
    {
    case games::Pacman::UP:
        playerX = playerX - 4;
        playerY = playerY - 4;
        break;
    case games::Pacman::LEFT:
        playerX = playerX - 4;
        break;
    case games::Pacman::DOWN:
        playerY = playerY + 4;
        break;
    case games::Pacman::RIGHT:
        playerX = playerX + 4;
        break;
    }
    return std::pair<long int, long int>(playerX, playerY);
}

std::pair<long int, long int> calculateBlueTarget(std::vector<IObjectToDraw *> objects,
games::Pacman::MOVEMENT playerMove, int playerX, int playerY)
{
    long int ghostX = 0;
    long int ghostY = 0;
    switch (playerMove) {
        case games::Pacman::UP:
            playerY = playerY -2;
            break;
        case games::Pacman::LEFT:
            playerX = playerX -2;
            break;
        case games::Pacman::DOWN:
            playerY = playerY +2;
            break;
        case games::Pacman::RIGHT:
            playerX = playerX +2;
            break;
    }
    for (int x = 0; x != objects.size(); x++) {
        if (objects.at(x)->getId() == "Ghost1") {
            ghostX = playerX - objects.at(x)->getCoords().first/32;
            ghostX = ghostX + playerX;
            ghostY = playerY - objects.at(x)->getCoords().second/32;
            ghostY = ghostY + playerY;
        }
    }
    return std::pair<long int, long int>(ghostX, ghostY);
}

std::vector<std::pair<games::Pacman::MOVEMENT, float>> checkSurrounding(std::array<std::string, 32> map, IObjectToDraw *ghost,
games::Pacman::MOVEMENT movement, int playerX, int playerY)
{
    float res = 0;
    int ghostX = ghost->getCoords().first/32;
    int ghostY = ghost->getCoords().second/32;
    std::vector<std::pair<games::Pacman::MOVEMENT, float>> options;
    if (ghost->getCoords().first%32 != 0 || ghost->getCoords().second%32 != 0) {
        options.push_back(std::pair<games::Pacman::MOVEMENT, float>(movement, 1));
        return options;
    }

    if (movement != games::Pacman::LEFT && ghostX != 30 && map[ghostY][ghostX+1] != '#') {
        res = getDistance(ghostX+1, ghostY, playerX, playerY);
        options.push_back(std::pair<games::Pacman::MOVEMENT, float>(games::Pacman::RIGHT, res));
    }
    if (movement != games::Pacman::UP && ghostY != 31 && map[ghostY+1][ghostX] != '#') {
        if (static_cast<Ghost *>(ghost)->getDead() == true || ((ghostY == 11 && ghostX == 15) == false && (ghostY == 11 && ghostX == 14) == false)) {
            res = getDistance(ghostX, ghostY+1, playerX, playerY);
            options.push_back(std::pair<games::Pacman::MOVEMENT, float>(games::Pacman::DOWN, res));
        }
    }
    if (movement != games::Pacman::RIGHT && ghostX != 0 && map[ghostY][ghostX-1] != '#') {
        res = getDistance(ghostX-1, ghostY, playerX, playerY);
        options.push_back(std::pair<games::Pacman::MOVEMENT, float>(games::Pacman::LEFT, res));
    }
    if (movement != games::Pacman::DOWN && ghostY != 0 && map[ghostY-1][ghostX] != '#') {
        if ((ghostY == 23 && ghostX == 16) == false && (ghostY == 23 && ghostX == 13) == false
            && (ghostY == 11 && ghostX == 16) == false && (ghostY == 11 && ghostX == 13) == false) {
            res = getDistance(ghostX, ghostY-1, playerX, playerY);
            options.push_back(std::pair<games::Pacman::MOVEMENT, float>(games::Pacman::UP, res));
        }
    }
    return options;
}

games::Pacman::MOVEMENT getRandomDirection(std::vector<std::pair<games::Pacman::MOVEMENT, float>> options)
{
    int num = std::rand() % options.size();

    return (options.at(num).first);
}

games::Pacman::MOVEMENT searchShortestPath(std::vector<std::pair<games::Pacman::MOVEMENT, float>> options)
{
    std::pair<games::Pacman::MOVEMENT, float> newMovement;

    newMovement = options.at(0);
    for (int x = 0; x != options.size(); x++) {
        if (newMovement.second >= options.at(x).second)
            newMovement = options.at(x);
    }
    return newMovement.first;
}

std::pair<long int, long int> setNewCoords(IObjectToDraw *ghost, games::Pacman::MOVEMENT move)
{
    long int ghostX = 0;
    long int ghostY = 0;


    switch (move) {
        case games::Pacman::UP:
            ghostY = ghost->getCoords().second - 16;
            ghostX = ghost->getCoords().first;
            break;
        case games::Pacman::LEFT:
            ghostX = ghost->getCoords().first - 16;
            ghostY = ghost->getCoords().second;
            if (ghostX == 0)
                ghostX = 928;
            break;
        case games::Pacman::RIGHT:
            ghostX = ghost->getCoords().first + 16;
            ghostY = ghost->getCoords().second;
            if (ghostX == 960)
                ghostX = 0;
            break;
        case games::Pacman::DOWN:
            ghostY = ghost->getCoords().second + 16;
            ghostX = ghost->getCoords().first;
            break;
    }
    return std::pair<long int, long int>(ghostX, ghostY);
}

void animate_ghost(IObjectToDraw *ghost)
{
    int x = std::get<0>(ghost->getSpritePos());
    
    x+= 32;
    if (x == 96)
        x = 32;
    static_cast<ObjectToDraw *>(ghost)->setSpritePos(x,0,32,32);
}

void games::Pacman::moveGhost(IObjectToDraw *ghost, int x)
{
    std::vector<std::pair<MOVEMENT, float>> options;
    if (static_cast<Ghost *>(ghost)->getDead() == true) {
        options = checkSurrounding(_map, ghost, _ghostMovement.at(x).first, static_cast<Ghost *>(ghost)->getStartField().first/32, static_cast<Ghost *>(ghost)->getStartField().second/32);
    }
    if (static_cast<Ghost *>(ghost)->getInside() == true) {
        options = checkSurrounding(_map, ghost, _ghostMovement.at(x).first, 15, 11);
    } else if (_chase == true && static_cast<Ghost *>(ghost)->getFlee() == false && static_cast<Ghost *>(ghost)->getDead() == false) {
        if (ghost->getId().compare("Ghost1") == 0)
            options = checkSurrounding(_map, ghost, _ghostMovement.at(x).first, _playerX, _playerY);
        else if (ghost->getId().compare("Ghost2") == 0) {
            std::pair<long int, long int> BlueGoal = calculateBlueTarget(_objects, _currentMove, _playerX, _playerY);
            options = checkSurrounding(_map, ghost, _ghostMovement.at(x).first, BlueGoal.first, BlueGoal.second);
        } else if (ghost->getId().compare("Ghost3") == 0) {
            float distance = getDistance(ghost->getCoords().first/32, ghost->getCoords().second/32, _playerX, _playerY);
            if (distance > 8.0f) {
                options = checkSurrounding(_map, ghost, _ghostMovement.at(x).first, _playerX, _playerY);
            } else {
                options = checkSurrounding(_map, ghost, _ghostMovement.at(x).first, static_cast<Ghost *>(ghost)->getScatterField().first, static_cast<Ghost *>(ghost)->getScatterField().second);
            }
        } else {
            std::pair<long int, long int> PinkGoal = calculatePinkTarget(_currentMove, _playerX, _playerY);
            options = checkSurrounding(_map, ghost, _ghostMovement.at(x).first, PinkGoal.first, PinkGoal.second);
        }
    } else if (_chase == false && static_cast<Ghost *>(ghost)->getFlee() == false &&  static_cast<Ghost *>(ghost)->getDead() == false) {
        options = checkSurrounding(_map, ghost, _ghostMovement.at(x).first, static_cast<Ghost *>(ghost)->getScatterField().first, static_cast<Ghost *>(ghost)->getScatterField().second);
    } else if (static_cast<Ghost *>(ghost)->getFlee() == true &&  static_cast<Ghost *>(ghost)->getDead() == false) {
        options = checkSurrounding(_map, ghost, _ghostMovement.at(x).first, 0, 0);
        _ghostMovement.at(x).first = getRandomDirection(options);
        if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - _fleeTime).count() > 6) {
            animate_ghost(ghost);
        }
    }

    if ((static_cast<Ghost *>(ghost)->getFlee() == false || static_cast<Ghost *>(ghost)->getDead() == true) && (options.size() > 1 || (options.size() == 1 && options.at(0).first != _ghostMovement.at(x).first))) {
        _ghostMovement.at(x).first = searchShortestPath(options);
    }
    std::pair<long int, long int> newCoords = setNewCoords(ghost, _ghostMovement.at(x).first);
    if ((newCoords.first/32 <= 18 && newCoords.first/32 >= 11) && (newCoords.second/32 <= 16 && newCoords.second/32 >= 12)) {
        static_cast<Ghost *>(ghost)->setInside(true);
        static_cast<Ghost *>(ghost)->setDead(false);
        static_cast<Ghost *>(ghost)->setFlee(false);
        static_cast<Ghost *>(ghost)->setSpritePos(0,0,32,32);
    } else {
        static_cast<Ghost *>(ghost)->setInside(false);
    }
    static_cast<ObjectToDraw *>(ghost)->setCoords(newCoords.first, newCoords.second);
}
