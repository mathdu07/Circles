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

 #include "State.h"

 State::State(Game &game)
 : m_game(game), m_orientation(game.getSize().x <= game.getSize().y ? PORTRAIT : LANDSCAPE)
 {

 }
 
 Game& State::getGame()
 {
    return m_game;
 }

 void State::handleEvent(sf::Event const &event)
 {
	 if (event.type == sf::Event::Resized)
	 {
		 m_orientation = (m_game.getSize().x <= m_game.getSize().y ? PORTRAIT : LANDSCAPE);
		 m_game.resetView();
		 updateLayout();
	 }
 }
