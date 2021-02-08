/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** description
*/

#ifndef OOP_ARCADE_2019_Asset_HPP
#define OOP_ARCADE_2019_Asset_HPP

#include "../../../GlobalHeaders.hpp"

namespace graphical {

class Asset
{
  private:
    IObjectToDraw::Type _type;
    std::string _id;
    std::string _symbol;
    std::pair<long int, long int> _coords;
    std::pair<long int, long int> _oldCoords;
  public:
    bool loadSymbolFromFile(std::string path);
    explicit Asset(std::string path, IObjectToDraw::Type type, std::string id);
    ~Asset() = default;
    std::string getId() {return _id;};
    void handle(IObjectToDraw *instance);
};

} // namespace graphical

#endif //OOP_ARCADE_2019_Asset_HPP
