/*
 *  Copyright © 2014 Margier Mathieu
 *  This file is part of Circles.
 *
 *  Circles is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Circles is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Circles. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GAME_H
#define GAME_H

//Forward class
class State;

#include "Main.h"
#include "Assets.h"

class Game
{
public:
    Game(sf::RenderWindow &window);
    virtual ~Game();

    sf::RenderWindow& getWindow();

    void run();

    Graphics const& gfx();
    Fonts const& fonts();

    void setState(State* state);
    State* getState();

    sf::Vector2u getSize() const;
    sf::Time getDelta() const;

    void switchToMainMenu();
    void switchToSettings();
    void play();

    void exit();

    void setView(sf::View view); //Use a copy of the view, needs to be set each time the view is modified
    void resetView();
    sf::View getView() const;

private:
    void handleEvent(sf::Event const &event);

private:
    sf::RenderWindow &m_window;
    Assets m_assets;
    State *m_oldState, *m_state;
};

#endif
