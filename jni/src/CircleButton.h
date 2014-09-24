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

#ifndef CIRCLE_BUTTON_H
#define CIRCLE_BUTTON_H

#include "Main.h"

class CircleButton : public sf::ui::AbstractButton, public sf::ui::IText
{
public:
	template<typename C>
	CircleButton(C *object, void(C::*function)(), float radius, float maxRadius)
	: AbstractButton(), m_circle(radius, 100),
	  m_text(), m_active(false), m_maxRadius(maxRadius), m_animationSpeed(0.2f),
	  m_task(new sf::priv::ThreadMemberFunc<C>(function, object))
	{
		setBorderRadius(2.f);
	}

protected:
	virtual void onClick();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual void updateCoord();

	virtual bool isCoordOnComponent(int x, int y) const;

public:
	sf::Vector2f getCenter() const;

	void doClick();

	virtual void updateFixed(sf::Time delta);

	bool isActived() const;

	virtual const sf::String& getText() const;

	virtual void setText(sf::String const &text);

	virtual const sf::Font* getFont() const;

	virtual void setFont(sf::Font const &font);

	virtual unsigned int getFontSize() const;

	virtual void setFontSize(unsigned int size);

	virtual sf::Color getFontColor() const;

	virtual void setFontColor(sf::Color color);

	float getRadius() const;

	void setRadius(float radius);

	sf::Color getOutlineCircleColor() const;

	void setOutlineCircleColor(sf::Color color);

	sf::Color getFillCircleColor() const;

	void setFillCircleColor(sf::Color color);

	float getBorderRadius() const;

	void setBorderRadius(float radius);

	float getAnimationSpeed() const;

	void setAnimationSpeed(float speed);

	sf::Vector2f getSize() const;

private:
	sf::CircleShape m_circle;
	sf::Text m_text;
	bool m_active;
	float m_maxRadius;
	float m_animationSpeed;
	sf::priv::ThreadFunc *m_task;

};

#endif
