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
#include "Fonts.h"

Fonts::Fonts()
: m_content(), m_bold()
{

}

void Fonts::load()
{
    m_content.loadFromFile("fonts/sawasdee.ttf");
    m_bold.loadFromFile("fonts/sawasdee-bold.ttf");
}

sf::Font const& Fonts::getContent() const
{
    return m_content;
}

sf::Font const& Fonts::getBold() const
{
    return m_bold;
}
