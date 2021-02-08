/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** description
*/

#include "../include/Snake.hpp"

namespace games {

void Body::move (Snake *part) {
    _lastCoords = _coords;
    _coords = part->getLastCoords();
    _direction = part->getDirection();
}

void Head::move (Snake *part) {
    (void) part;
    _lastCoords = _coords;
    _direction = _nextDirection;
    switch (_direction) {
        case UP:
            std::get<1>(_coords) -= 32;
            break;
        case LEFT:
            std::get<0>(_coords) -= 32;
            break;
        case RIGHT:
            std::get<0>(_coords) += 32;
            break;
        case DOWN:
            std::get<1>(_coords) += 32;
            break;
    }
}

void Head::turn(Direction direction) {
    switch (_direction) {
        case UP:
            if (direction == LEFT)
                _nextDirection = LEFT;
            else if (direction == RIGHT)
                _nextDirection = RIGHT;
            break;
        case LEFT:
            if (direction == UP)
                _nextDirection = UP;
            else if (direction == DOWN)
                _nextDirection = DOWN;
            break;
        case RIGHT:
            if (direction == UP)
                _nextDirection = UP;
            else if (direction == DOWN)
                _nextDirection = DOWN;
            break;
        case DOWN:
            if (direction == LEFT)
                _nextDirection = LEFT;
            else if (direction == RIGHT)
                _nextDirection = RIGHT;
            break;
    }
}

bool Head::checkBlocked(std::array<std::string, 32> &map) {
    unsigned int x = std::get<0>(_coords)/32;
    unsigned int y = std::get<1>(_coords)/32;
    switch (_nextDirection) {
        case UP:
            if (map[y - 1][x] == '#' || map[y - 1][x + 1] == '#') {
                if (_nextDirection != _direction) {
                    _nextDirection = _direction;
                    return checkBlocked(map);
                } else
                    return true;
            }
            return false;
        case RIGHT:
            if (map[y][x + 2] == '#' || map[y + 1][x + 2] == '#') {
                if (_nextDirection != _direction) {
                    _nextDirection = _direction;
                    return checkBlocked(map);
                } else
                    return true;
            }
            return false;
        case LEFT:
            if (map[y][x - 1] == '#' || map[y + 1][x - 1] == '#') {
                if (_nextDirection != _direction) {
                    _nextDirection = _direction;
                    return checkBlocked(map);
                } else
                    return true;
            }
            return false;
        case DOWN:
            if (map[y + 2][x] == '#' || map[y + 2][x + 1] == '#') {
                if (_nextDirection != _direction) {
                    _nextDirection = _direction;
                    return checkBlocked(map);
                } else
                    return true;
            }
            return false;
    }
    return false;
}

} // namespace games