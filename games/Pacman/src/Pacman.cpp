/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Pacman
*/

#include "../include/Pacman.hpp"
#include <iostream>
#include <fstream>
#include <cmath>

std::vector<std::pair<std::string, unsigned int>> getOldScores();

extern "C" games::IGameInterface *entryPoint(void) {
    return new games::Pacman;
}

ObjectToDraw::ObjectToDraw(std::string id, std::string Path, Type type, std::string value, long int x, long int y,
unsigned int spriteX, unsigned int spriteY, unsigned int spriteHeight, unsigned int spriteWidth,
int red, int green, int blue, int alpha) :
_id(id), _path(Path), _type(type), _value(value), _coords(std::pair<long int, long int>(x, y)),
_spritePos(std::tuple<unsigned int, unsigned int, unsigned int, unsigned int>(spriteX, spriteY, spriteHeight, spriteWidth))
{
    _color = std::tuple<unsigned int, unsigned int, unsigned int, unsigned int>(red, green, blue, alpha);
}
Ghost::Ghost(std::string id, std::string Path, Type type ,std::string value, long int x, long int y,
    unsigned int spriteX, unsigned int spriteY, unsigned int spriteHeight, unsigned int spriteWidth,
    int red, int green, int blue, int alpha,
    unsigned int scatterX, unsigned int scatterY, unsigned int startX, unsigned int startY) :
_id(id), _path(Path), _type(type), _value(value), _coords(std::pair<long int, long int>(x, y)),
_spritePos(std::tuple<unsigned int, unsigned int, unsigned int, unsigned int>(spriteX, spriteY, spriteHeight, spriteWidth)),_dead(false), _flee(false), _inside(true)
{
    _color = std::tuple<unsigned int, unsigned int, unsigned int, unsigned int>(red, green, blue, alpha);
    _scatterField = std::pair<unsigned int, unsigned int>(scatterX, scatterY);
    _startField = std::pair<unsigned int, unsigned int>(startX, startY);
}
games::Pacman::Pacman() : _lives(3), _map({
"##############################",
"##............##............##",
"##.####.#####.##.#####.####.##",
"##U#__#.#___#.##.#___#.#__#U##",
"##.####.#####.##.#####.####.##",
"##..........................##",
"##.####.##.########.##.####.##",
"##.####.##.########.##.####.##",
"##......##....##....##......##",
"#######.#####_##_#####.#######",
"______#.#####_##_#####.#______",
"______#.##_____T____##.#______",
"______#.##_###--###_##.#______",
"#######.##_#______#_##.#######",
"_______.___#_IW_F_#___._______",
"#######.##_#______#_##.#######",
"______#.##_########_##.#______",
"______#.##_____P____##.#______",
"______#.##_########_##.#______",
"#######.##_########_##.#######",
"##............##............##",
"##.####.#####.##.#####.####.##",
"##.####.#####.##.#####.####.##",
"##U..##................##..U##",
"####.##.##.########.##.##.####",
"####.##.##.########.##.##.####",
"##......##....##....##......##",
"##.##########.##.##########.##",
"##.##########.##.##########.##",
"##..........................##",
"##############################",
"##############################"})
{
    createAssets();
    createObjects();
    _score = 0;
}
void games::Pacman::createAssets()
{
    ObjectToDraw *Wall = new ObjectToDraw(std::string("Wall"), std::string("games/Pacman/assets/wall"), IObjectToDraw::Type::objects, std::string(""), 0, 0, 0, 0, 32, 32, 14, 0, 158, 255);
    _assets.push_back(Wall);
    ObjectToDraw *Player = new ObjectToDraw(std::string("Player"), std::string("games/Pacman/assets/player"), IObjectToDraw::Type::objects, std::string(""), 0, 0, 0, 0, 32, 32, 215, 253, 0, 255);
    _assets.push_back(Player);
    ObjectToDraw *Dots = new ObjectToDraw(std::string("Dot"), std::string("games/Pacman/assets/dots"), IObjectToDraw::Type::objects, std::string(""), 0, 0, 0, 0, 32, 32, 25, 253, 0, 255);
    _assets.push_back(Dots);
    ObjectToDraw *PowerPill = new ObjectToDraw(std::string("PowerPill"), std::string("games/Pacman/assets/powerpill"), IObjectToDraw::Type::objects, std::string(""), 0, 0, 0, 0, 32, 32, 25, 253, 0, 255);
    _assets.push_back(PowerPill);
    ObjectToDraw *GhostOne = new ObjectToDraw(std::string("Ghost1"), std::string("games/Pacman/assets/ghost1"), IObjectToDraw::Type::objects, std::string(""), 0, 0, 0, 0, 32, 32, 250, 0, 0, 255);
    _assets.push_back(GhostOne);
    ObjectToDraw *GhostTwo = new ObjectToDraw(std::string("Ghost2"), std::string("games/Pacman/assets/ghost2"), IObjectToDraw::Type::objects, std::string(""), 0, 0, 0, 0, 32, 32, 205, 191, 255, 255);
    _assets.push_back(GhostTwo);
    ObjectToDraw *GhostThree = new ObjectToDraw(std::string("Ghost3"), std::string("games/Pacman/assets/ghost3"), IObjectToDraw::Type::objects, std::string(""), 0, 0, 0, 0, 32, 32, 257, 198, 0, 255);
    _assets.push_back(GhostThree);
    ObjectToDraw *GhostFour = new ObjectToDraw(std::string("Ghost4"), std::string("games/Pacman/assets/ghost4"), IObjectToDraw::Type::objects, std::string(""), 0, 0, 0, 0, 32, 32, 249, 128, 128, 255);
    _assets.push_back(GhostFour);
    _assets.push_back(new ObjectToDraw(std::string("score"), std::string("games/Pacman/assets/font"), IObjectToDraw::Type::text, std::string("0"), 1200, 0, 0, 0, 32, 32, 255, 255, 255, 255));
    _assets.push_back(new ObjectToDraw(std::string("oldscores"), std::string("games/Pacman/assets/font"), IObjectToDraw::Type::text, std::string("0"), 1200, 80, 0, 0, 32, 32, 255, 255, 255, 255));
    _assets.push_back(new ObjectToDraw(std::string("lives"), std::string("games/Pacman/assets/font"), IObjectToDraw::Type::text, std::string("0"), 1200, 40, 0, 0, 32, 32, 255, 255, 255, 255));
    _assets.push_back(new ObjectToDraw(std::string("countdown"), std::string("games/Pacman/assets/font"), IObjectToDraw::Type::text, std::string("0"), 1200, 40, 0, 0, 32, 32, 255, 255, 255, 255));
}

void games::Pacman::createObjects()
{
    for(int y = 0; y != _map.size(); y++) {
        for(int x = 0; x != _map.at(y).length(); x++) {
            if (_map[y][x] == '.') {
                _objects.push_back(new ObjectToDraw(std::string("Dot"), std::string("games/Pacman/assets/dots"), IObjectToDraw::Type::objects, std::string(""), x*32, y*32, 0, 0, 32, 32,
                25, 253, 0, 255));
            } else if (_map[y][x] == '#') {
                _objects.push_back(new ObjectToDraw(std::string("Wall"), std::string("games/Pacman/assets/wall"), IObjectToDraw::Type::objects, std::string(""), x*32, y*32, 0, 0, 32, 32,
                14, 0, 158, 255));
            } else if (_map[y][x] == 'U') {
                _objects.push_back(new ObjectToDraw(std::string("PowerPill"), std::string("games/Pacman/assets/powerpill"), IObjectToDraw::Type::objects, std::string(""), x*32, y*32, 0, 0, 32, 32,
                25, 253, 0, 255));
            }
        }
    }
    _objects.push_back(new ObjectToDraw(std::string("Player"), std::string("games/Pacman/assets/player"), IObjectToDraw::Type::objects, std::string(""), 15*32, 17*32, 0, 0, 32, 32,
    215, 253, 0, 255));
    _objects.push_back(new Ghost(std::string("Ghost1"), std::string("games/Pacman/assets/ghost1"), IObjectToDraw::Type::objects, std::string(""), 15*32, 11*32, 0, 0, 32, 32,
    250, 0, 0, 255,
    31, 0, 15*32, 11*32));
    _objects.push_back(new Ghost(std::string("Ghost2"), std::string("games/Pacman/assets/ghost2"), IObjectToDraw::Type::objects, std::string(""), 14*32, 14*32, 0, 0, 32, 32,
    205, 191, 255, 255,
    31, 31, 14*32, 14*32));
    _objects.push_back(new Ghost(std::string("Ghost3"), std::string("games/Pacman/assets/ghost3"), IObjectToDraw::Type::objects, std::string(""), 16*32, 14*32, 0, 0, 32, 32,
    257, 198, 0, 255,
    3, 31, 16*32, 14*32));
    _objects.push_back(new Ghost(std::string("Ghost4"), std::string("games/Pacman/assets/ghost4"), IObjectToDraw::Type::objects, std::string(""), 13*32, 14*32, 0, 0, 32, 32,
    249, 128, 128, 255,
    0, 0, 13*32, 14*32));
    _objects.push_back(new ObjectToDraw(std::string("score"), std::string("games/Pacman/assets/font"), IObjectToDraw::Type::text, std::string("score: 0"), 1200, 0, 0, 0, 32, 32, 255, 255, 255, 255));
    _objects.push_back(new ObjectToDraw(std::string("lives"), std::string("games/Pacman/assets/font"), IObjectToDraw::Type::text, std::string("0"), 1200, 40, 0, 0, 32, 32, 255, 255, 255, 255));
    _countdown.push_back(new ObjectToDraw(std::string("countdown"), std::string("games/Pacman/assets/font"), IObjectToDraw::Type::text, std::string("   Game loads"), 800, 500, 0, 0, 32, 32, 255, 255, 255, 255));

    _ghostMovement.push_back(std::pair<MOVEMENT, std::string>(RIGHT, "Ghost1"));
    _ghostMovement.push_back(std::pair<MOVEMENT, std::string>(UP, "Ghost2"));
    _ghostMovement.push_back(std::pair<MOVEMENT, std::string>(UP, "Ghost3"));
    _ghostMovement.push_back(std::pair<MOVEMENT, std::string>(UP, "Ghost4"));

    _ghostModeTime = std::chrono::steady_clock::now();
    _oldScores = getOldScores();
    _playerTime = std::chrono::steady_clock::now();
    _ghostTime = std::chrono::steady_clock::now();
    _startCountdown = std::chrono::steady_clock::now();
    _DeadTime = std::chrono::steady_clock::now();
    _ghostActive = false;
    _chase = false;
    _flee = false;
    _start = 5;
    _killCounter = 0;
    _ghostComputeSpeed = 83;
    _dotsLeft = 242;
    _playerX = 15;
    _playerY = 17;
    _currentMove = LEFT;
    _nextMove = LEFT;
    std::srand(std::time(nullptr));
    std::string Highschore;
    _objects.push_back(new ObjectToDraw(std::string("oldscores"), std::string("games/Pacman/assets/font"), IObjectToDraw::Type::text, std::string("Top 10 Highscores:"), 1200, 160, 0, 0, 32, 32, 255, 255, 255, 255));
    for (int x = 0; x < _oldScores.size(); x++) {
        Highschore = _oldScores.at(x).first + " ";
        for (int y = 0; y < 7 - std::to_string(_oldScores.at(x).second).size(); y++) {
            Highschore = Highschore + "0";
        }
        Highschore = Highschore + std::to_string(_oldScores.at(x).second);
        _objects.push_back(new ObjectToDraw(std::string("oldscores"), std::string("games/Pacman/assets/font"), IObjectToDraw::Type::text, Highschore, 1200, 210 + (x*40), 0, 0, 32, 32, 255, 255, 255, 255));
    }

}

void games::Pacman::resetGame()
{
    for (int x = 0; x != _objects.size(); x++) {
        if (_objects.at(x)->getId().find("Ghost") != std::string::npos) {
            static_cast<Ghost *>(_objects.at(x))->setCoords(static_cast<Ghost *>(_objects.at(x))->getStartField().first, static_cast<Ghost *>(_objects.at(x))->getStartField().second);
            static_cast<Ghost *>(_objects.at(x))->setDead(false);
            static_cast<Ghost *>(_objects.at(x))->setFlee(false);
            if (_objects.at(x)->getId() != "Ghost1")
                static_cast<Ghost *>(_objects.at(x))->setInside(true);
            else
                static_cast<Ghost *>(_objects.at(x))->setInside(false);
            static_cast<Ghost *>(_objects.at(x))->setSpritePos(0,0,32,32);
        }
        if (_objects.at(x)->getId().compare("Player") == 0) {
            static_cast<ObjectToDraw *>(_objects.at(x))->setCoords(15*32, 17*32);
            _playerX = 15;
            _playerY = 17;
        }
    }
    static_cast<ObjectToDraw *>(_countdown.at(0))->setValue("Game is reseting");
    _ghostModeTime = std::chrono::steady_clock::now();
    _playerTime = std::chrono::steady_clock::now();
    _ghostTime = std::chrono::steady_clock::now();
    _startCountdown = std::chrono::steady_clock::now();
    _DeadTime = std::chrono::steady_clock::now();
    _chase = false;
    _flee = false;
    _start = 5;
    _killCounter = 0;
    _ghostComputeSpeed = 83;
    _currentMove = LEFT;
    _nextMove = LEFT;
}

games::Pacman::~Pacman()
{
}

bool games::Pacman::start()
{
    return true;
}
bool games::Pacman::end()
{
    return true;
}

std::vector<std::pair<std::string, unsigned int>> getOldScores()
{
    std::fstream fs;
    fs.open("./games/Pacman/.highscore.txt", std::ios::out | std::ios::app);
    fs.close();
    std::ifstream input ("./games/Pacman/.highscore.txt");
    std::vector<std::pair<std::string, unsigned int>> old_records;
    for( std::string line; std::getline(input, line ); )
    {
        old_records.push_back(std::pair<std::string, unsigned int>(line.substr(0, line.find_last_of(" ")), std::stoi(line.substr(line.find_last_of(" "), line.size()))));
    };
    return old_records;
}

void setHighScore(std::string user, unsigned int score, std::vector<std::pair<std::string, unsigned int>> old_records)
{
    bool set = false;

    for (int x = 0; x != old_records.size(); x++) {
        if (score > old_records.at(x).second) {
            old_records.insert(old_records.begin()+x, std::pair<std::string, unsigned int>(user, score));
            set = true;
            break;
        }
    }
    if (set == false)
        old_records.push_back(std::pair<std::string, unsigned int>(user, score));
    
    std::ofstream output ("./games/Pacman/.highscore.txt");
    for (int x = 0; x != old_records.size() && x != 10; x++) {
        output << std::string(old_records.at(x).first + " " + std::to_string(old_records.at(x).second));
        if (x + 1 != old_records.size() && x + 1 != 10)
            output << std::endl;
    }
}

COMMAND games::Pacman::applyInput (COMMAND userInput)
{
    int x = 0;
    bool leftRight = true;
    bool upDown = true;

    for (int x = 0; x != _objects.size(); x++) {
        if (_objects.at(x)->getId().compare("Player") == 0) {
            if (_objects.at(x)->getCoords().first%32 == 16)
                upDown = false;
            if (_objects.at(x)->getCoords().second%32 == 16)
                leftRight = false;
            break;
        }
    }
    switch (userInput) {
        case COMMAND::UP:
            if (upDown == true && _playerY != 0 && _map[_playerY - 1][_playerX] != '#')
                _currentMove = UP;
            _nextMove = UP;
            break;
        case COMMAND::LEFT:
            if (leftRight == true && _playerX != 0 && _map[_playerY][_playerX-1] != '#')
                _currentMove = LEFT;
            _nextMove = LEFT;
            break;
        case COMMAND::RIGHT:
            if (leftRight == true && _playerX != 31 && _map[_playerY][_playerX+1] != '#')
                _currentMove = RIGHT;
            _nextMove = RIGHT;
            break;
        case COMMAND::DOWN:
            if (upDown == true && _playerY != 31 && _map[_playerY + 1][_playerX] != '#' && _map[_playerY + 1][_playerX] != '-')
                _currentMove = DOWN;
            _nextMove = DOWN;
            break;
    }
    if (_lives == 0) {
        setHighScore(_username, _score, _oldScores);
        return COMMAND::MAIN_MENU;
    }
    return userInput;
}

std::vector<std::pair<games::Pacman::MOVEMENT, std::string>> ghostTurnAround(
    std::vector<std::pair<games::Pacman::MOVEMENT, std::string>> ghostMoves)
{
    for (int x = 0; x != ghostMoves.size(); x++) {
        switch (ghostMoves.at(x).first) {
            case games::Pacman::UP:
                ghostMoves.at(x).first = games::Pacman::DOWN;
                break;
            case games::Pacman::DOWN:
                ghostMoves.at(x).first = games::Pacman::UP;
                break;
            case games::Pacman::LEFT:
                ghostMoves.at(x).first = games::Pacman::RIGHT;
                break;
            case games::Pacman::RIGHT:
                ghostMoves.at(x).first = games::Pacman::LEFT;
                break;
        }
    }
    return ghostMoves;
}

void animatePlayer(IObjectToDraw *player, games::Pacman::MOVEMENT currMove)
{
    static int animation_state = 0;
    static int close_open = 1;
    int y = 0;

    switch (currMove) {
        case games::Pacman::MOVEMENT::UP:
            y = 32;
            break;
        case games::Pacman::MOVEMENT::DOWN:
            y = 0;
            break;
        case games::Pacman::MOVEMENT::LEFT:
            y = 96;
            break;
        case games::Pacman::MOVEMENT::RIGHT:
            y = 64;
            break;
    }
    animation_state += (32 * close_open);
    if (animation_state == 64 || animation_state == 0)
        close_open = close_open *-1;
    if (animation_state == 0)
        y = 0;
    static_cast<ObjectToDraw *>(player)->setSpritePos(animation_state, y, 32, 32);
}

bool games::Pacman::checkPlayerCollision(IObjectToDraw *player)
{
    for (int x = 0; x != _objects.size(); x++) {
        if (_objects.at(x)->getId().find("Ghost") != std::string::npos) {
            if (_objects.at(x)->getCoords().first == player->getCoords().first && _objects.at(x)->getCoords().second == player->getCoords().second) {
                if (static_cast<Ghost *>(_objects.at(x))->getFlee() == false && static_cast<Ghost *>(_objects.at(x))->getDead() == false) {
                    resetGame();
                    _lives -= 1;
                    return true;
                } else if (static_cast<Ghost *>(_objects.at(x))->getFlee() == true && static_cast<Ghost *>(_objects.at(x))->getDead() == false) {
                        static_cast<Ghost *>(_objects.at(x))->setDead(true);
                        static_cast<Ghost *>(_objects.at(x))->setSpritePos(96, 0, 32, 32);
                        if (_killCounter == 0)
                            _killCounter = 200;
                        else
                            _killCounter = _killCounter * 2;
                        _score += _killCounter;
                }
            }
        }
    }
    return false;
}

bool testNextMove(games::Pacman::MOVEMENT nextMove, int playerY, int playerX, std::array<std::string, 32> map)
{
    switch (nextMove) {
        case games::Pacman::UP:
            if (map[playerY-1][playerX] != '#')
                return true;
            break;
        case games::Pacman::LEFT:
            if (map[playerY][playerX-1] != '#')
                return true;
            break;
        case games::Pacman::DOWN:
            if (map[playerY+1][playerX] != '#' && map[playerY+1][playerX] != '-')
                return true;
            break;
        case games::Pacman::RIGHT:
            if (map[playerY][playerX+1] != '#')
                return true;
            break;
    }
    return false;
}

void games::Pacman::movePlayer(IObjectToDraw *player)
{
    bool updateXY = false;
    int newX = player->getCoords().first;
    int newY = player->getCoords().second;

    if (newX%32 == 0 && newY%32 == 0 && _currentMove != _nextMove && true == testNextMove(_nextMove, _playerY, _playerX, _map))
        _currentMove = _nextMove;
    if (newX%32 == 16 || newY%32 == 16)
        updateXY = true;
    switch (_currentMove) {
        case UP:
            if (_playerY != 0 && _map[_playerY - 1][_playerX] != '#')
                newY = newY-16;
            if (updateXY == true && newY != _playerY*32)
                _playerY -= 1;
            break;
        case LEFT:
            if (newX == 0) {
                _playerX = 30;
                newX = 960;
            }
            if (_playerX != 0 && _map[_playerY][_playerX-1] != '#')
                newX = newX-16;
            if (updateXY == true && newX != _playerX*32)
                _playerX -= 1;
            break;
        case RIGHT:
            if (_playerX != 30 && _map[_playerY][_playerX+1] != '#') {
                newX = newX+16;
                if (updateXY == true && newX != _playerX*32)
                    _playerX += 1;
                if (newX == 960) {
                    _playerX = 0;
                    newX = 0;
                }
            }
            break;
        case DOWN:
            if (_playerY != 31 && _map[_playerY + 1][_playerX] != '#')
                newY = newY+16;
            if (updateXY == true && newY != _playerY*32)
                _playerY += 1;
            break;
    }
    static_cast<ObjectToDraw *>(player)->setCoords(newX, newY);
    animatePlayer(player, _currentMove);
}

std::vector<IObjectToDraw *> games::Pacman::compute()
{
    std::chrono::time_point<std::chrono::steady_clock> currentTime = std::chrono::steady_clock::now();
    if (_start > 0) {
        if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - _startCountdown).count() > (5- _start)) {
            static_cast<ObjectToDraw *>(_countdown.at(0))->setValue("Game begins in "+ std::to_string(_start-2));
            if (_start <= 2) {
                static_cast<ObjectToDraw *>(_countdown.at(0))->setValue("      Ready");
                _ghostModeTime = std::chrono::steady_clock::now();
            }
            _start -= 1;
            if (_start == 0)
                _ghostSpawn = std::chrono::steady_clock::now();
        }
        return _countdown;
    }
    if (_ghostActive == false) {
        if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - _ghostSpawn).count() > 10)
            _ghostActive = true;
    }
    if (_chase == true && std::chrono::duration_cast<std::chrono::seconds>(currentTime - _ghostModeTime).count() > 20) {
        _chase = false;
        _ghostModeTime = std::chrono::steady_clock::now();
        if (_flee == true)
            _ghostMovement = ghostTurnAround(_ghostMovement);
    } else if (_chase == false && std::chrono::duration_cast<std::chrono::seconds>(currentTime - _ghostModeTime).count() > 7) {
        _chase = true;
        _ghostModeTime = std::chrono::steady_clock::now();
        if (_flee == true)
            _ghostMovement = ghostTurnAround(_ghostMovement);
    } else if (_flee == true && std::chrono::duration_cast<std::chrono::seconds>(currentTime - _fleeTime).count() > 10) {
        _flee = false;
        _ghostComputeSpeed = 83;
        for (int change = 0; change != _objects.size(); change++) {
            if (_objects.at(change)->getId().find("Ghost") != std::string::npos) {
                if (static_cast<Ghost *>(_objects.at(change))->getFlee() == true &&
                    static_cast<Ghost *>(_objects.at(change))->getDead() != true) {
                    static_cast<ObjectToDraw *>(_objects.at(change))->setSpritePos(0,0,32,32);
                    static_cast<Ghost *>(_objects.at(change))->setFlee(false);
                }
            }
        }
    }

    bool playerCompute = false;
    bool ghostCompute = false;
    bool deadCompute = false;
    if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - _playerTime).count() > 83) {
        playerCompute = true;
        _playerTime = std::chrono::steady_clock::now();
    }
    if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - _ghostTime).count() > _ghostComputeSpeed) {
        ghostCompute = true;
        _ghostTime = std::chrono::steady_clock::now();
    }
    if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - _DeadTime).count() > 48) {
        deadCompute = true;
        _DeadTime = std::chrono::steady_clock::now();
    }
    int damage = 0;
    for (int x = 0; x != _objects.size(); x++) {
        if (playerCompute == true && _objects.at(x)->getId().compare("Player") == 0) {
            if (checkPlayerCollision(_objects.at(x)) == true)
                break;
            movePlayer(_objects.at(x));
            if (checkPlayerCollision(_objects.at(x)) == true)
                break;
        }
        if (_objects.at(x)->getCoords().first == _playerX*32 && _objects.at(x)->getCoords().second == _playerY*32
            && (_objects.at(x)->getId().compare("Dot") == 0 || _objects.at(x)->getId().compare("PowerPill") == 0)) {
            if (_objects.at(x)->getId().compare("PowerPill") == 0) {
                if (_flee == false)
                    _ghostMovement = ghostTurnAround(_ghostMovement);
                _flee = true;
                _killCounter = 0;
                _ghostComputeSpeed = 116;
                _fleeTime = std::chrono::steady_clock::now();
                for (int change = 0; change != _objects.size(); change++) {
                    if (_objects.at(change)->getId().find("Ghost") != std::string::npos &&
                        static_cast<Ghost *>(_objects.at(change))->getDead() == false) {
                        static_cast<ObjectToDraw *>(_objects.at(change))->setSpritePos(32,0,32,32);
                        static_cast<Ghost *>(_objects.at(change))->setFlee(true);
                    }
                }
            } else {
                if (_score < 9999990)
                    _score += 10;
                _dotsLeft -= 1;
            }
            _objects.erase(_objects.begin() + x);
        }
        if (_objects.at(x)->getId().compare("score") == 0) {
            static_cast<ObjectToDraw *>(_objects.at(x))->setValue("score: " + std::to_string(_score));
        }
        if (_objects.at(x)->getId().compare("lives") == 0) {
            static_cast<ObjectToDraw *>(_objects.at(x))->setValue("lives: " + std::to_string(_lives));
        }
        if (ghostCompute == true) {
            if (_objects.at(x)->getId().compare("Ghost1") == 0)
                moveGhost(_objects.at(x), 0);
            if (_ghostActive == true && _dotsLeft <= 211 && _objects.at(x)->getId().compare("Ghost2") == 0)
                moveGhost(_objects.at(x), 1);
            if (_ghostActive == true && _dotsLeft <= 161 && _objects.at(x)->getId().compare("Ghost3") == 0)
                moveGhost(_objects.at(x), 2);
            if (_ghostActive == true && _objects.at(x)->getId().compare("Ghost4") == 0)
                moveGhost(_objects.at(x), 3);
        } else if (deadCompute == true) {
            if (_objects.at(x)->getId().find("Ghost") != std::string::npos &&
                static_cast<Ghost *>(_objects.at(x))->getDead() == true) {
                    moveGhost(_objects.at(x), (int)_objects.at(x)->getId().at(5) -49);
                }
        }
    }
    if (_dotsLeft == 0) {
        _countdown.clear();
        _objects.clear();
        createObjects();
        _lives += 1;
    }
    return _objects;
}
