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

#ifndef GAME_OVER_STATE_H
#define GAME_OVER_STATE_H

#include "State.h"
#include "PlayState.h"
#include "CircleButton.h"

class GameOverState : public State
{
public:
	/*
	 * Warning : do not save *play to another pointer,
	 * as it will be delete by the state manager
	 * after the call of the constructor
	 */
	GameOverState(PlayState *play);

    void init();

    void handleEvent(sf::Event const &event);

    void deInit();

    void render(sf::RenderTarget &target);

    void update();

    void retry();

    void back();

protected:
    int m_score;
    sf::ui::Label m_gameoverLabel;
    sf::ui::Label m_scoreLabel;
    CircleButton m_retry, m_back;
};

#endif
