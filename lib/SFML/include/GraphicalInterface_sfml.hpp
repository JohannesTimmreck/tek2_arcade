/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** GraphicalInterface_sfml
*/

#ifndef GRAPHICALINTERFACE_SFML_HPP_
#define GRAPHICALINTERFACE_SFML_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>

#include "../../IGraphicalInterface.hpp"
#include "Asset.hpp"

namespace graphical {

class GraphicalInterface_sfml : public IGraphicalInterface
{
    public:
        GraphicalInterface_sfml();
        ~GraphicalInterface_sfml();
        bool init() override;
        bool initAssets(std::vector<IObjectToDraw *> assets) override;
        bool destroyAssets() override;
        bool destroy() override;
        COMMAND getInput() override;
        bool draw(std::vector<IObjectToDraw *> objects) override;
    private:
        sf::RenderWindow _window;
        sf::Event _event;
        std::vector<Asset> _assets;
};

}

#endif /* !GRAPHICALINTERFACE_SFML_HPP_ */
