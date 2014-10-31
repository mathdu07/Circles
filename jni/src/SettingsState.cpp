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

#include "SettingsState.h"
#include <sstream>

SettingsState::SettingsState(Game &game)
: State(game), m_title(), m_dev(), m_version(),
  m_back(&game, &Game::switchToMainMenu, 75 * game.getScale())
{

}

void SettingsState::init()
{
	float scale = m_game.getScale();
	sf::Font const &font = m_game.fonts().getContent();
	sf::Color background(51, 51, 51);

	m_title.setFont(m_game.fonts().getBold());
	m_title.setFontSize(128 * scale);
	m_title.setText("Circles");
	m_title.setFontColor(sf::Color(128, 128, 128));

	m_dev.setText("A game by : Mathieu Margier");
	m_dev.setFont(font);
	m_dev.setFontColor(sf::Color::White);
	m_dev.setFontSize(32 * scale);

	std::ostringstream oss;
	oss << "Version : " << CIRCLES_VERSION;
	m_version.setText(oss.str());
	m_version.setFont(font);
	m_version.setFontColor(sf::Color::White);
	m_version.setFontSize(32 * scale);

	m_back.setText("Back");
	m_back.setFont(font);
	m_back.setFontSize(64 * scale);
	m_back.setFontColor(sf::Color::White);
	m_back.setOutlineCircleColor(sf::Color::Red);
	m_back.setFillCircleColor(background);
	m_back.setBorderRadius(3.f);
	m_back.setAnimationSpeed(0.8f * scale);

	updateLayout();
}

void SettingsState::updateLayout()
{
	sf::Vector2u size = m_game.getSize();
	m_back.setMaxRadius(std::max(size.x, size.y));

	sf::Vector2f titleSize = m_title.getSize();
	m_title.setPosition(sf::Vector2f(size.x/2 - titleSize.x/2, size.y/8 - titleSize.y/2));
	m_back.setPosition(size.x/2.f, size.y - m_back.getRadius() - 5);

	if (m_orientation == PORTRAIT)
	{
		m_dev.setPosition(size.x/2.f - m_dev.getSize().x/2.f, 5 * size.y/16.f - m_dev.getSize().y/2.f);
		m_version.setPosition(size.x/2.f - m_version.getSize().x/2.f, 3 * size.y/8.f - m_version.getSize().y/2.f);
	}
	else
	{
		m_dev.setPosition(10.f, 6 * size.y/16.f - m_dev.getSize().y/2.f);
		m_version.setPosition(size.x/4 - m_version.getSize().x/2 + size.x/2, 6 * size.y/16.f - m_version.getSize().y/2.f);
	}
}

void SettingsState::handleEvent(sf::Event const &event)
{
	State::handleEvent(event);

	if (!m_back.isActived())
	{
		m_dev.updateEvent(event);
		m_version.updateEvent(event);
		m_back.updateEvent(event);
	}
}

void SettingsState::deInit()
{

}

void SettingsState::render(sf::RenderTarget &target)
{
	target.clear(sf::Color(51, 51, 51));
	target.draw(m_title);
	target.draw(m_dev);
	target.draw(m_version);
	target.draw(m_back);
}

void SettingsState::update()
{
	m_title.updateFixed(m_game.getDelta());
	m_dev.updateFixed(m_game.getDelta());
	m_version.updateFixed(m_game.getDelta());
	m_back.updateFixed(m_game.getDelta());
}
