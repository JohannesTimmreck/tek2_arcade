/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** description
*/

#ifndef OOP_ARCADE_2019_GRAPHICALINTERFACE_HPP
#define OOP_ARCADE_2019_GRAPHICALINTERFACE_HPP

#include "../../IGraphicalInterface.hpp"

namespace graphical {

class GraphicalInterface : public IGraphicalInterface
{
  public:
    GraphicalInterface();
    ~GraphicalInterface();
    virtual bool init() {return true;};                // initialize window
    virtual bool initAssets(std::vector<IObjectToDraw *> assets) {return true;};           // initialize textures/sprites
    virtual bool destroyAssets() {return true;};           // destroy textures/sprites
    virtual bool destroy() {return true;};             //  destroy window
    virtual COMMAND getInput() { return EXIT;};   // get User Input
    virtual bool draw(std::vector<IObjectToDraw *> objects) {return true;};                // draw next frame
};

} // namespace graphical

#endif //OOP_ARCADE_2019_GRAPHICALINTERFACE_HPP
