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
    Game(sf::RenderWindow &window, int aaLevel, unsigned int originalDefinition);
    virtual ~Game();

    sf::RenderWindow& getWindow();

    virtual bool create();
    void run();

    Graphics const& gfx();
    Fonts const& fonts();

    void setState(State* state);
    State* getState();

    virtual sf::Vector2u getSize() const;
    sf::Time getDelta() const;

    void switchToMainMenu();
    void switchToSettings();
    void play();

    void exit();

    virtual void setView(sf::View view); //Use a copy of the view, needs to be set each time the view is modified
    virtual void resetView();
    virtual sf::View getView() const;

    void saveMaxScore(int maxScore);
    int readMaxScore();

    unsigned int getOriginalDefinition() const;

    unsigned int getDefinition() const;

    float getScale() const;

    sf::Color getClearColor() const;
    void setClearColor(sf::Color color);

private:
    void handleEvent(sf::Event &event);

    virtual sf::RenderTarget& getRenderTarget();

    virtual void beforeHandleEvent(sf::Event &event);

    virtual void beforeRendering();
    virtual void afterRendering();

protected:
    sf::RenderWindow &m_window;
    Assets m_assets;
    State *m_oldState, *m_state;
    sf::String m_saveFolder;
    int m_aaLevel, m_originalDefinition;
    sf::Color m_clearColor;
};

#endif
