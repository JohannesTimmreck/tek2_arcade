/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** description
*/

#ifndef OOP_ARCADE_2019_MAINMENU_HPP
#define OOP_ARCADE_2019_MAINMENU_HPP

#include "../../games/IGameInterface.hpp"

namespace core {

  class MainMenu : public games::IGameInterface
{
  private:
      std::vector<IObjectToDraw *> _assets;
      std::vector<IObjectToDraw *> _objects;
      int _curGame;
      std::vector<std::string> _availableGames;
      std::vector<std::string> _availableGraphics;
  public:
    MainMenu(std::vector<std::string> &games, std::vector<std::string> &graphics);
    ~MainMenu();
    std::vector<IObjectToDraw *> getAssets() const override { return _assets;};
      virtual void setUsername(std::string username) override ;
      bool start() override { return true;}
    bool end() override { return true;}
      COMMAND applyInput (COMMAND userInput) override;
      std::vector<IObjectToDraw *> compute() override;
};

} // namespace core

#endif //OOP_ARCADE_2019_MAINMENU_HPP
