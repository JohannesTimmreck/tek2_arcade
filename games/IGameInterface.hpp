#ifndef OOP_ARCADE_2019_IGAMEINTERFACE_HPP
#define OOP_ARCADE_2019_IGAMEINTERFACE_HPP

#include <vector>

#include "../GlobalHeaders.hpp"

namespace games {

class IGameInterface
{
  public:
    virtual ~IGameInterface () = default;

    virtual bool start() = 0;                                       // initialize game
    virtual void setUsername(std::string username) = 0;             // set username for display of score
    virtual bool end() = 0;                                         // end game
    virtual std::vector<IObjectToDraw *> getAssets() const = 0;     // return the assets for display
    virtual COMMAND applyInput (COMMAND userInput) = 0;             // apply user input | specify return keys
    virtual std::vector<IObjectToDraw *> compute() = 0;             // calculate next game frame and return it
};

} // namespace games

#endif //OOP_ARCADE_2019_IGAMEINTERFACE_HPP
