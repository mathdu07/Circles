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

#include "GameOverState.h"
#include "TransitionState.h"
#include "MainMenuState.h"
#include <sstream>

GameOverState::GameOverState(PlayState *play)
: State(play->getGame()), m_score(play->getScore()),
  m_gameoverLabel(), m_scoreLabel(),
  m_retry(this, &GameOverState::retry, 75, 75),
  m_back(this, &GameOverState::back, 75, 75)
{

}

void GameOverState::init()
{
	sf::Vector2u size = m_game.getSize();
	sf::Color background(51, 51, 51);
	sf::Font const &title = m_game.fonts().getBold();
	sf::Font const &content = m_game.fonts().getContent();

	m_gameoverLabel.setFont(title);
	m_gameoverLabel.setFontSize(82);
	m_gameoverLabel.setText("Game Over!");
	m_gameoverLabel.setFontColor(sf::Color(128, 128, 128));
	sf::Vector2f goSize = m_gameoverLabel.getSize();
	m_gameoverLabel.setPosition(sf::Vector2f(size.x/2 - goSize.x/2, size.y/8 - goSize.y/2));

	m_scoreLabel.setFont(content);
	m_scoreLabel.setFontSize(58);
	std::ostringstream oss;
	oss << "Score: " << m_score;
	m_scoreLabel.setText(oss.str());
	m_scoreLabel.setFontColor(sf::Color::White);
	m_scoreLabel.setPosition(sf::Vector2f(size.x/2 - m_scoreLabel.getSize().x/2,
			size.y/2 - m_scoreLabel.getSize().y/2));

	m_retry.setFont(content);
	m_retry.setFontSize(52);
	m_retry.setText("Retry");
	m_retry.setFontColor(sf::Color::White);
	m_retry.setOutlineCircleColor(sf::Color::Green);
	m_retry.setFillCircleColor(background);
	m_retry.setBorderRadius(3.f);
	m_retry.setPosition(sf::Vector2f(size.x/4, size.y - m_retry.getRadius() - 10.f));

	m_back.setFont(content);
	m_back.setFontSize(52);
	m_back.setText("Back");
	m_back.setFontColor(sf::Color::White);
	m_back.setOutlineCircleColor(sf::Color::Red);
	m_back.setFillCircleColor(background);
	m_back.setBorderRadius(3.f);
	m_back.setPosition(sf::Vector2f(3 * size.x/4, size.y - m_back.getRadius() - 10.f));
}

void GameOverState::handleEvent(sf::Event const &event)
{
	m_retry.updateEvent(event);
	m_back.updateEvent(event);
}

void GameOverState::deInit()
{

}

void GameOverState::render(sf::RenderTarget &target)
{
	sf::Color background(51, 51, 51);
	target.clear(background);

	target.draw(m_gameoverLabel);
	target.draw(m_scoreLabel);

	target.draw(m_retry);
	target.draw(m_back);
}

void GameOverState::update()
{
	m_retry.updateFixed(m_game.getDelta());
	m_back.updateFixed(m_game.getDelta());
}

void GameOverState::retry()
{
	TransitionState *state = new TransitionState(this, new PlayState(m_game), SLIDE_LEFT);
	state->setSpeed(600.f);
	m_game.setState(state);
}

void GameOverState::back()
{
	TransitionState *state = new TransitionState(this, new MainMenuState(m_game), SLIDE_RIGHT);
	state->setSpeed(600.f);
	m_game.setState(state);
}
