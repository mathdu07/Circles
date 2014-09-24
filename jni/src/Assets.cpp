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

#include "Assets.h"

Assets::Assets()
: m_fonts(), m_graphics()
{

}

void Assets::loadAssets()
{
    m_fonts.load();
    m_graphics.load();
}

Fonts const& Assets::getFonts() const
{
    return m_fonts;
}

Graphics const& Assets::getGraphics() const
{
    return m_graphics;
}
