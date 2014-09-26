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

#ifndef PLAY_STATE
#define PLAY_STATE

#include "State.h"
#include <set>
#include "Circle.h"
#include "CircleButton.h"

class PlayState : public State
{
public:
	PlayState(Game &game);

	virtual void init();

    virtual void handleEvent(sf::Event const &event);

	virtual void deInit();

	virtual void render(sf::RenderTarget &target);

	virtual void update();

	std::string printScore(std::string prefix) const;

	bool isGameOver() const;

	void setGameOver(bool gameover);

	int getScore() const;

protected:
	void spawnCircle();

private:
	int m_score;
	sf::ui::Label m_scoreLabel;
	std::set<Circle*> m_circles;
	sf::Time m_cooldown, m_cooldownMax;
	sf::Time m_timeLived;
	float m_radius;
	bool m_gameover;
	sf::Vector2i m_lastCircle;

};

#endif
