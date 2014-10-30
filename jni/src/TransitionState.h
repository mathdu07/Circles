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

#ifndef TRANSITION_STATE_H
#define TRANSITION_STATE_H

#include "State.h"

enum Transition
{
	SLIDE_LEFT,
	SLIDE_RIGHT
};

class TransitionState : public State
{
public:
	TransitionState(State *currentState, State *nextState, Transition transition);

    virtual void init();

    virtual void updateLayout();

    virtual void deInit();

    virtual void render(sf::RenderTarget &target);

    virtual void update();

    void setSpeed(float speed);

    float getSpeed() const;

protected:
	State *m_currentState, *m_nextState;
	Transition m_transition;
	float m_speed;
	sf::RenderTexture m_currentTexture, m_nextTexture;
	sf::View m_view;
	sf::Sprite m_currentSprite, m_nextSprite;
};


#endif
