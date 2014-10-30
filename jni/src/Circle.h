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

#ifndef CIRCLE_H
#define CIRCLE_H

#include "Main.h"

class Circle : public sf::Drawable
{
public:
	Circle(int x, int y, int radius, sf::Color color, float scale);

	bool contains(sf::Vector2f point) const;

	sf::Vector2f getCenter() const;

	void setCenter(sf::Vector2f center);

	float getRadius() const;

	void setRadius(float radius);

	void update(sf::Time delta);

	bool isDead() const;

	sf::Color getColor() const;

	void setColor(sf::Color color);

	int getThickness() const;

	void setThickness(int thickness);

	bool isTouched() const;

	void setTouched(bool touched);

	float getSpeed() const;

	void setSpeed(float speed);

	float getArea() const;

	float getScale() const;

	void setScale(float scale);

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void updateCoord();

private:
	sf::CircleShape m_shape;
	bool m_touched;
	float m_speed;
	float m_scale;

};

#endif
