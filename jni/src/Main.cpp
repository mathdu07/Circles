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

#include "Main.h"
#include <cstdlib>
#include <ctime>
#include "Game.h"

int main(int argc, char *argv[])
{
    sf::RenderWindow window;
    Game game(window);

    LOGI("Starting Circles (%s)", CIRCLES_VERSION);
    LOGD("Initializing random seed");
    srand(time(0));

    LOGD("Running game ...");
    game.run();

    return EXIT_SUCCESS;
}
