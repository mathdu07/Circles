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

#include "TransitionState.h"

TransitionState::TransitionState(State *currentState, State *nextState, Transition transition)
: State(currentState->getGame()), m_currentState(currentState), m_nextState(nextState),
  m_transition(transition), m_speed(200.f),
  m_currentTexture(), m_nextTexture(), m_view(sf::FloatRect(0, 0, m_game.getSize().x, m_game.getSize().y)),
  m_currentSprite(), m_nextSprite(), m_lastOrientation(m_orientation)
{

}

void TransitionState::init()
{
	m_nextState->init();
	sf::Vector2u size = m_game.getSize();

	LOGD("Creating current's texture");
	if (!m_currentTexture.create(size.x, size.y))
	{
		LOGE("Can't create render texture of size (%d;%d)", m_game.getSize().x, m_game.getSize().y);
		m_game.exit();
	}

	LOGD("Creating next's texture");
	if (!m_nextTexture.create(size.x, size.y))
	{
		LOGE("Can't create render texture of size (%d;%d)", m_game.getSize().x, m_game.getSize().y);
		m_game.exit();
	}

	m_currentSprite.setTexture(m_currentTexture.getTexture());
	m_nextSprite.setTexture(m_nextTexture.getTexture());

	updateLayout();
}

void TransitionState::updateLayout()
{
	sf::Vector2u size = m_game.getSize();

	if (m_lastOrientation != m_orientation)
	{
		m_game.setState(m_nextState);
	}

	switch (m_transition)
	{
	case SLIDE_LEFT:
		m_nextSprite.setPosition(sf::Vector2f(-1.f * size.x, 0));
		break;
	case SLIDE_RIGHT:
		m_nextSprite.setPosition(sf::Vector2f(1.f * size.x, 0));
	}

	m_lastOrientation = m_orientation;
}

void TransitionState::deInit()
{
	m_currentState->deInit();
	m_game.resetView();
}

void TransitionState::render(sf::RenderTarget &target)
{
	m_currentTexture.clear();
	m_nextTexture.clear();
	m_currentState->render(m_currentTexture);
	m_nextState->render(m_nextTexture);
	m_currentTexture.display();
	m_nextTexture.display();

	target.draw(m_currentSprite);
	target.draw(m_nextSprite);
}

void TransitionState::update()
{
	switch (m_transition)
	{
	case SLIDE_LEFT:
	case SLIDE_RIGHT:
	{
		m_view.move(sf::Vector2f(m_speed, 0) * m_game.getDelta().asSeconds() * (m_transition == SLIDE_LEFT ? -1.f : 1.f));
		sf::Vector2f center = m_view.getCenter();
		sf::Vector2u size = m_game.getSize();

		if (center.x > -1.f * size.x/2.f && center.x < 3 * size.x/2.f)
		{
			m_game.setView(m_view);
		}
		else
		{
			m_game.setState(m_nextState);
		}

		break;
	}
	}
}

void TransitionState::setSpeed(float speed)
{
	if (speed < 0.f)
		speed = 0.f;

	m_speed = speed;
}

float TransitionState::getSpeed() const
{
	return m_speed;
}
