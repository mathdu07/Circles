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

#include "MainMenuState.h"

MainMenuState::MainMenuState(Game &game)
: State(game), m_title(), m_start(&game, &Game::play, 120 * game.getScale()),
  m_settings(&game, &Game::switchToSettings, 75 * game.getScale()),
  m_exit(&game, &Game::exit, 75 * game.getScale())
{
}

void MainMenuState::init()
{
	sf::Color background(51, 51, 51);
	float scale = m_game.getScale();

	m_title.setFont(m_game.fonts().getBold());
	m_title.setFontSize(128 * scale);
	m_title.setText("Circles");
	m_title.setFontColor(sf::Color(128, 128, 128));

	m_start.setFont(m_game.fonts().getBold());
	m_start.setFontSize(96 * scale);
	m_start.setText("Start");
	m_start.setFontColor(sf::Color::White);
	m_start.setOutlineCircleColor(sf::Color::Green);
	m_start.setFillCircleColor(background);
	m_start.setBorderRadius(5.f);
	m_start.setAnimationSpeed(0.4f * scale);

	m_settings.setFont(m_game.fonts().getContent());
	m_settings.setFontSize(44 * scale);
	m_settings.setText("Settings");
	m_settings.setFontColor(sf::Color::White);
	m_settings.setOutlineCircleColor(sf::Color::Blue);
	m_settings.setFillCircleColor(background);
	m_settings.setBorderRadius(3.f);
	m_settings.setAnimationSpeed(0.8f * scale);

	m_exit.setFont(m_game.fonts().getContent());
	m_exit.setFontSize(72 * scale);
	m_exit.setText("Exit");
	m_exit.setFontColor(sf::Color::White);
	m_exit.setOutlineCircleColor(sf::Color::Red);
	m_exit.setFillCircleColor(background);
	m_exit.setBorderRadius(3.f);
	m_exit.setAnimationSpeed(0.8f * scale);

	updateLayout();
}

void MainMenuState::updateLayout()
{
	sf::Vector2u size = m_game.getSize();
	m_start.setMaxRadius(std::max(size.x, size.y) /2 + 20);
	m_settings.setMaxRadius(std::max(size.x, size.y));
	m_exit.setMaxRadius(std::max(size.x, size.y));

	sf::Vector2f titleSize = m_title.getSize();

	if (m_orientation == PORTRAIT)
	{
		m_title.setPosition(sf::Vector2f(size.x/2 - titleSize.x/2, size.y/8 - titleSize.y/2));
		m_start.setPosition(sf::Vector2f(size.x/2, size.y/2));
		m_settings.setPosition(sf::Vector2f(size.x/4, size.y - m_settings.getRadius() - 10.f));
		m_exit.setPosition(sf::Vector2f(3 * size.x/4, size.y - m_exit.getRadius() - 10.f));
	}
	else
	{
		m_title.setPosition(sf::Vector2f((size.x - m_settings.getSize().x - 10.f)/2 - titleSize.x/2, size.y/8 - titleSize.y/2));
		m_start.setPosition(sf::Vector2f((size.x - m_settings.getSize().x - 10.f)/2,
				(size.y - m_title.getPosition().y - m_title.getSize().y)/2 + m_title.getPosition().y + m_title.getSize().y));
		m_settings.setPosition(sf::Vector2f(size.x - m_settings.getRadius() - 10.f, size.y/4));
		m_exit.setPosition(sf::Vector2f(size.x - m_settings.getRadius() - 10.f, 3 * size.y/4));
	}
}

void MainMenuState::handleEvent(sf::Event const &event)
{
	State::handleEvent(event);

	if (!m_start.isActived() && !m_settings.isActived() && !m_exit.isActived())
	{
		m_title.updateEvent(event);
		m_start.updateEvent(event);
		m_settings.updateEvent(event);
		m_exit.updateEvent(event);
	}
}

void MainMenuState::deInit()
{

}

void MainMenuState::render(sf::RenderTarget &target)
{
	target.clear(sf::Color(51, 51, 51));

	target.draw(m_title);

	if (!m_settings.isActived() || !m_exit.isActived())
		target.draw(m_start);
	if (!m_start.isActived() || !m_exit.isActived())
		target.draw(m_settings);
	if (!m_settings.isActived() || !m_start.isActived())
		target.draw(m_exit);

	if (m_start.isActived())
		target.draw(m_start);
	if (m_settings.isActived())
		target.draw(m_settings);
	if (m_exit.isActived())
		target.draw(m_exit);

	//DEBUG
	/*sf::Vector2u size = m_game.getSize();
	sf::RectangleShape xAxis(sf::Vector2f(size.x, 1)), yAxis(sf::Vector2f(1, size.y));
	xAxis.setPosition(sf::Vector2f(0, size.y/2));
	yAxis.setPosition(sf::Vector2f(size.x/2, 0));
	xAxis.setFillColor(sf::Color::White);
	yAxis.setFillColor(sf::Color::White);
	target.draw(xAxis);
	target.draw(yAxis);*/

}

void MainMenuState::update()
{
	m_title.updateFixed(m_game.getDelta());
	m_start.updateFixed(m_game.getDelta());
	m_settings.updateFixed(m_game.getDelta());
	m_exit.updateFixed(m_game.getDelta());
}
