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

#include "CircleButton.h"
#include <cmath>
#include <SFML/UI/SFMLUtils.h>

void CircleButton::onClick()
{
	m_active = true;
}

void CircleButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_circle);
	target.draw(m_text);
}

void CircleButton::updateCoord()
{
	sf::FloatRect bounds = m_circle.getLocalBounds();
	sf::Vector2f center(bounds.width/2.f, bounds.height/2.f);
	m_circle.setOrigin(sf::Vector2f(getRadius(), getRadius()));
	m_circle.setPosition(getPosition());

	sf::Vector2f textSize = sf::ui::SFMLUtils::getLocalSize(m_text);
	m_text.setOrigin(textSize / 2.f);
	m_text.setPosition(getPosition());
}

void CircleButton::doClick()
{

}

sf::Vector2f CircleButton::getCenter() const
{
	return getPosition();
}

bool CircleButton::isCoordOnComponent(int x, int y) const
{
	sf::Vector2f center = getCenter();

	return pow(x - center.x, 2) + pow(y - center.y, 2) <= pow(getRadius() + m_circle.getOutlineThickness(), 2);
}

void CircleButton::updateFixed(sf::Time delta)
{
	if (m_active)
	{
		if (getRadius() >= m_maxRadius || m_animationSpeed <= 0)
		{
			m_task->run();
			m_active = false;
			return;
		}

		setRadius(getRadius() + delta.asMilliseconds() * m_animationSpeed);


	}
}

bool CircleButton::isActived() const
{
	return m_active;
}

const sf::String& CircleButton::getText() const
{
	return m_text.getString();
}

void CircleButton::setText(sf::String const &text)
{
	m_text.setString(text);
	updateCoord();
}

const sf::Font* CircleButton::getFont() const
{
	return m_text.getFont();
}

void CircleButton::setFont(sf::Font const &font)
{
	m_text.setFont(font);
	updateCoord();
}

unsigned int CircleButton::getFontSize() const
{
	return m_text.getCharacterSize();
}

void CircleButton::setFontSize(unsigned int size)
{
	m_text.setCharacterSize(size);
	updateCoord();
}

sf::Color CircleButton::getFontColor() const
{
	return m_text.getColor();
}

void CircleButton::setFontColor(sf::Color color)
{
	m_text.setColor(color);
}

float CircleButton::getRadius() const
{
	return m_circle.getRadius();
}

void CircleButton::setRadius(float radius)
{
	m_circle.setRadius(radius);
	updateCoord();
}

float CircleButton::getMaxRadius() const
{
	return m_maxRadius;
}

void CircleButton::setMaxRadius(float maxRadius)
{
	m_maxRadius = maxRadius;
}

sf::Color CircleButton::getOutlineCircleColor() const
{
	return m_circle.getOutlineColor();
}

void CircleButton::setOutlineCircleColor(sf::Color color)
{
	m_circle.setOutlineColor(color);
}

sf::Color CircleButton::getFillCircleColor() const
{
	return m_circle.getFillColor();
}

void CircleButton::setFillCircleColor(sf::Color color)
{
	m_circle.setFillColor(color);
}

float CircleButton::getBorderRadius() const
{
	return m_circle.getOutlineThickness();
}

void CircleButton::setBorderRadius(float radius)
{
	m_circle.setOutlineThickness(radius);
}

float CircleButton::getAnimationSpeed() const
{
	return m_animationSpeed;
}

void CircleButton::setAnimationSpeed(float speed)
{
	m_animationSpeed = speed;
}

sf::Vector2f CircleButton::getSize() const
{
	return sf::Vector2f(getRadius()*2.f, getRadius()*2.f);
}
