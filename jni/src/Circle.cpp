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

#include "Circle.h"
#include <cmath>

Circle::Circle(int x, int y, int radius, sf::Color color)
: m_shape(radius, 100), m_touched(false), m_speed(1/20.f)
{
	setThickness(3);
	setColor(color);
	m_shape.setFillColor(sf::Color(0, 0, 0, 0));
	m_shape.setPosition(sf::Vector2f(x, y));
	m_shape.setOrigin(sf::Vector2f(radius, radius));
}

void Circle::updateCoord()
{
	m_shape.setOrigin(sf::Vector2f(getRadius(), getRadius()));
}

void Circle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_shape);
}

bool Circle::contains(sf::Vector2f point) const
{
	sf::Vector2f center = getCenter();

	return pow(point.x - center.x, 2) + pow(point.y - center.y, 2) <= pow(getRadius(), 2);
}

sf::Vector2f Circle::getCenter() const
{
	return m_shape.getPosition();
}

void Circle::setCenter(sf::Vector2f center)
{
	m_shape.setPosition(center);
	updateCoord();
}

float Circle::getRadius() const
{
	return m_shape.getRadius();
}

void Circle::setRadius(float radius)
{
	if (radius < 0.f)
		radius = 0.f;

	m_shape.setRadius(radius);
	updateCoord();
}

void Circle::update(sf::Time delta)
{
	if (!isDead() && !isTouched())
	{
		setRadius(getRadius() - getSpeed() * delta.asMilliseconds());
	}
}

bool Circle::isDead() const
{
	return getRadius() == 0.f;
}

sf::Color Circle::getColor() const
{
	return m_shape.getOutlineColor();
}

void Circle::setColor(sf::Color color)
{
	m_shape.setOutlineColor(color);
}

int Circle::getThickness() const
{
	return m_shape.getOutlineThickness();
}

void Circle::setThickness(int thickness)
{
	m_shape.setOutlineThickness(thickness);
}

bool Circle::isTouched() const
{
	return m_touched;
}

void Circle::setTouched(bool touched)
{
	m_touched = touched;
}

float Circle::getSpeed() const
{
	return m_speed;
}

void Circle::setSpeed(float speed)
{
	if (speed < 0)
		speed = 0;

	m_speed = speed;
}

float Circle::getArea() const
{
	return pow(getRadius(), 2) * M_PI;
}
