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

#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "State.h"
#include "CircleButton.h"

class MainMenuState : public State
{
public:
	MainMenuState(Game &game);

	virtual void init();

	virtual void updateLayout();

    virtual void handleEvent(sf::Event const &event);

	virtual void deInit();

	virtual void render(sf::RenderTarget &target);

	virtual void update();

private:
	sf::ui::Label m_title;
	CircleButton m_start;
	CircleButton m_settings, m_exit;

};

#endif
