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

#ifndef ASSETS_H
#define ASSETS_H

#include "Main.h"

#include "Fonts.h"
#include "Graphics.h"

class Assets
{
public:
    Assets();

    void loadAssets();

    Fonts const& getFonts() const;

    Graphics const& getGraphics() const;

private:
   Fonts m_fonts;
   Graphics m_graphics;
};

#endif
