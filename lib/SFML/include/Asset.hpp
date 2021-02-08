/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** description
*/

#ifndef OOP_ARCADE_2019_Asset_HPP
#define OOP_ARCADE_2019_Asset_HPP

#include <SFML/Graphics.hpp>
#include "../../../GlobalHeaders.hpp"

namespace graphical {

class Asset
{
  private:
    IObjectToDraw::Type _type;
    std::string _id;

  // for Object Type
    sf::Texture _texture;
    sf::Rect<int> _rect;
    sf::Sprite _sprite;

  // for text type
    sf::Font _font;
    sf::Text _text;

    bool _loaded;
  public:
    explicit Asset(std::string path, IObjectToDraw::Type type, std::string id);
    ~Asset() = default;
    void setAnimRect(std::tuple<unsigned int, unsigned int, unsigned int, unsigned int> rect);
    void updateTexture() {}
    std::string getId() {return _id;}
    void handle(IObjectToDraw *instance, sf::RenderWindow &window);
};

} // namespace graphical

#endif //OOP_ARCADE_2019_Asset_HPP
