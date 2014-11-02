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

#include "PlayState.h"
#include "TransitionState.h"
#include "GameOverState.h"
#include <cstdlib>
#include <sstream>
#include <cmath>

PlayState::PlayState(Game &game)
: State(game), m_score(0), m_scoreLabel(), m_circles(),
  m_cooldownMax(sf::seconds(1/2.f)), m_timeLived(),
  m_radius(100.f), m_gameover(false), m_lastCircle(-m_radius, -m_radius), m_scoreInfo(),
  m_lastOrientation(m_orientation)
{
	m_maxScore = game.readMaxScore();
	m_cooldown = m_cooldownMax;
	LOGI("Starting new game");
}

void PlayState::init()
{
	float scale = m_game.getScale();
	sf::Font const &font = m_game.fonts().getContent();

	m_scoreLabel.setText("Score: 0");
	m_scoreLabel.setFont(font);
	m_scoreLabel.setFontSize(42 * scale);
	m_scoreLabel.setFontColor(sf::Color::White);

	updateLayout();
}

void PlayState::updateLayout()
{
	sf::Vector2u size = m_game.getSize();

	m_scoreLabel.setPosition(sf::Vector2f(size.x / 2.f  - m_scoreLabel.getSize().x / 2.f, 5));

	if (m_orientation != m_lastOrientation)
	{
		std::set<Circle*>::iterator it;
		for (it = m_circles.begin(); it != m_circles.end(); it++)
		{
			Circle *circle = *it;
			sf::Vector2f center = circle->getCenter();
			circle->setCenter(sf::Vector2f(center.y, center.x));
		}

		std::set<sf::ui::Label*>::iterator itLab;
		for (itLab = m_scoreInfo.begin(); itLab != m_scoreInfo.end(); itLab++)
		{
			sf::ui::Label *label = *itLab;
			label->setPosition(sf::Vector2f(label->getPosition().y, label->getPosition().x));
		}
	}

	m_lastOrientation = m_orientation;
}

void PlayState::handleEvent(sf::Event const &event)
{
	State::handleEvent(event);

	switch (event.type)
	{
	case sf::Event::TouchBegan:
	case sf::Event::MouseButtonPressed:
	{
		int x = event.type == sf::Event::TouchBegan ? event.touch.x : event.mouseButton.x;
		int y = event.type == sf::Event::TouchBegan ? event.touch.y : event.mouseButton.y;
		bool check = event.type == sf::Event::TouchBegan ? event.touch.finger == 0 : event.mouseButton.button == sf::Mouse::Left;

		if (check)
		{
			std::set<Circle*>::iterator it;
			for (it = m_circles.begin(); it != m_circles.end(); it++)
			{
				if ((*it)->contains(sf::Vector2f(x, y)))
				{
					(*it)->setTouched(true);
					float multiplier = std::max(1.f, m_timeLived.asSeconds() / 30.f);
					int bonus = ceil(log((*it)->getArea()) * 10);
					bonus *= multiplier;
					m_score += bonus;

					std::ostringstream oss;
					oss << "+" << bonus;
					sf::ui::Label *bonusLabel(new sf::ui::Label);
					initLabel(*bonusLabel, oss.str());
					bonusLabel->setPosition(sf::Vector2f((*it)->getCenter()));
					bonusLabel->move(bonusLabel->getSize() / -2.f);
					m_scoreInfo.insert(bonusLabel);
				}
			}
		}
	}
	}

}

void PlayState::deInit()
{

}

void PlayState::render(sf::RenderTarget &target)
{
	target.clear(sf::Color(51, 51, 51));

	target.draw(m_scoreLabel);

	std::set<Circle*>::const_iterator it;
	for (it = m_circles.begin(); it != m_circles.end(); it++)
	{
		target.draw(**it);
	}

	std::set<sf::ui::Label*>::const_iterator labelIt;
	for (labelIt = m_scoreInfo.begin(); labelIt != m_scoreInfo.end(); labelIt++)
	{
		target.draw(**labelIt);
	}

	//DEBUG
	/*sf::Vector2u size = m_game.getSize();
	sf::RectangleShape xAxis(sf::Vector2f(size.x, 1)), yAxis(sf::Vector2f(1, size.y));
	xAxis.setPosition(sf::Vector2f(0, size.y/2));
	yAxis.setPosition(sf::Vector2f(size.x/2, 0));
	xAxis.setFillColor(sf::Color::White);
	yAxis.setFillColor(sf::Color::White);
	target.draw(xAxis);
	target.draw(yAxis);*/
}

void PlayState::update()
{
	if (!m_gameover)
	{
		sf::Vector2u size = m_game.getSize();
		m_timeLived += m_game.getDelta();
		m_cooldown -= m_game.getDelta();

		m_cooldownMax = sf::seconds(std::min(std::max(1.f / (0.1f * m_timeLived.asSeconds()), 0.2f), 1.f));
		m_radius = std::max(150.f / std::max(0.1f * m_timeLived.asSeconds(), 1.f), 100.f);

		std::set<Circle*>::iterator it;
		std::set<Circle*> toRemove;
		for (it = m_circles.begin(); it != m_circles.end(); it++)
		{
			(*it)->update(m_game.getDelta());

			if ((*it)->isDead())
			{
				LOGI("Game over ! Final score : %d", m_score);
				setGameOver(true);
			}

			if ((*it)->isTouched())
				toRemove.insert(*it);
		}

		std::set<Circle*>::iterator remIt;
		for (remIt = toRemove.begin(); remIt != toRemove.end(); remIt++)
		{
			m_circles.erase(*remIt);
			delete *remIt;
		}

		if (m_cooldown.asMilliseconds() <= 0)
		{
			spawnCircle();
			m_cooldown = m_cooldownMax;
		}

		std::set<sf::ui::Label*> infoToRem;
		std::set<sf::ui::Label*>::iterator infoIt;
		for (infoIt = m_scoreInfo.begin(); infoIt != m_scoreInfo.end(); infoIt++)
		{
			sf::ui::Label *label = *infoIt;

			if (label->getFontColor().a == 0)
			{
				infoToRem.insert(label);
			}
			else
			{
				sf::Color color = label->getFontColor();

				if (color.a <= 20)
					color.a = 0;
				else
					color.a -= 20;

				label->setFontColor(color);
				label->move(sf::Vector2f(-2.f, -2.f));
			}
		}

		for (std::set<sf::ui::Label*>::iterator lIt = infoToRem.begin(); lIt != infoToRem.end(); lIt++)
		{
			sf::ui::Label *label = *lIt;
			m_scoreInfo.erase(label);
			delete label;
		}

		m_scoreLabel.setText(printScore("Score : "));
		m_scoreLabel.setPosition(sf::Vector2f(size.x / 2.f  - m_scoreLabel.getSize().x / 2.f, 5));
	}
	else
	{
		TransitionState *state = new TransitionState(this, new GameOverState(this), SLIDE_RIGHT);
		state->setSpeed(m_game.getSize().x * 1.5f * m_game.getScale());
		m_game.setState(state);
	}
}

void PlayState::spawnCircle()
{
	sf::Vector2u size = m_game.getSize();
	float scale = m_game.getScale();

	int minX = m_radius * scale + 5, maxX = size.x - m_radius * scale - 5;
	int minY = m_scoreLabel.getPosition().y + m_scoreLabel.getSize().y + m_radius * scale + 5;
	int maxY = size.y - m_radius * scale - 5;

	int x;
	int y;
	int tries = 0, maxTries = 10;

	do
	{
		x = rand() % (maxX - minX + 1) + minX;
		y = rand() % (maxY - minY + 1) + minY;
		tries++;
	}
	while ((x > m_lastCircle.x - 2 * m_radius * scale && x < m_lastCircle.x + 2 * m_radius * scale)
			&& (y > m_lastCircle.y - 2 * m_radius * scale && y < m_lastCircle.y + 2 * m_radius * scale)
			&& tries < maxTries);

	m_lastCircle = sf::Vector2i(x, y);

	sf::Color color;
	switch (rand() % 7)
	{
	case 0:
		color = sf::Color(255, 255, 255);
		break;
	case 1:
		color = sf::Color(255, 0, 0);
		break;
	case 2:
		color = sf::Color(0, 255, 0);
		break;
	case 3:
		color = sf::Color(0, 0, 255);
		break;
	case 4:
		color = sf::Color(255, 255, 0);
		break;
	case 5:
		color = sf::Color(255, 0, 255);
		break;
	case 6:
		color = sf::Color(0, 255, 255);
		break;
	default:
		color = sf::Color(255, 255, 255);
		break;
	}

	m_circles.insert(new Circle(x, y, m_radius, color, scale));
}

std::string PlayState::printScore(std::string prefix) const
{
	std::ostringstream oss;
	oss << prefix << m_score;
	return oss.str();
}

sf::ui::Label& PlayState::initLabel(sf::ui::Label &label, sf::String text)
{
	label.setFont(m_game.fonts().getContent());
	label.setFontSize(48);
	label.setText(text);
	label.setFontColor(sf::Color::White);

	return label;
}

bool PlayState::isGameOver() const
{
	return m_gameover;
}

void PlayState::setGameOver(bool gameover)
{
	m_gameover = gameover;

	if (m_gameover && m_score > m_maxScore)
	{
		m_maxScore = m_score;
		m_game.saveMaxScore(m_maxScore);
		LOGD("Max Score : %d", m_maxScore);
	}
}

int PlayState::getScore() const
{
	return m_score;
}

int PlayState::getMaxScore() const
{
	return m_maxScore;
}
