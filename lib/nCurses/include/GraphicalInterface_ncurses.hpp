/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** description
*/

#ifndef OOP_ARCADE_2019_GRAPHICALINTERFACE_HPP
#define OOP_ARCADE_2019_GRAPHICALINTERFACE_HPP

#include "../../IGraphicalInterface.hpp"
#include "Asset.hpp"

namespace graphical {

class GraphicalInterface_ncurses : public IGraphicalInterface
{
  private:
    int m_maxWidth;
    int m_maxLength;
    int m_terminalLength;
    int m_terminalWidth;
    std::vector<Asset> _assets;
  public:
    GraphicalInterface_ncurses();
    ~GraphicalInterface_ncurses();
    virtual bool init() override;
    virtual bool initAssets(std::vector<IObjectToDraw *> assets) override;
    virtual bool destroyAssets() {return true;};
    virtual bool destroy() {return true;};
    virtual COMMAND getInput() override;
    virtual bool draw(std::vector<IObjectToDraw *> objects) override;
};

} // namespace graphical

#endif //OOP_ARCADE_2019_GRAPHICALINTERFACE_HPP
