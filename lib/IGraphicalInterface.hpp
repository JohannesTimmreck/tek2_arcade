/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** description
*/

#ifndef OOP_ARCADE_2019_IGRAPHICALINTERFACE_HPP
#define OOP_ARCADE_2019_IGRAPHICALINTERFACE_HPP

#include <vector>

#include "../GlobalHeaders.hpp"


namespace graphical {

class IGraphicalInterface
{
  public:
    virtual ~IGraphicalInterface() = default;

  // initialize window
    virtual bool init() = 0;
  // initialize assets for each type of object
    virtual bool initAssets(std::vector<IObjectToDraw *> assets) = 0;
  // destroy assets for each type of object
    virtual bool destroyAssets() = 0;
  // destroy window
    virtual bool destroy() = 0;
  // get User Input
    virtual COMMAND getInput() = 0;
  // draw next frame
    virtual bool draw(std::vector<IObjectToDraw *> objects) = 0;
};

} // namespace graphical

#endif //OOP_ARCADE_2019_IGRAPHICALINTERFACE_HPP
