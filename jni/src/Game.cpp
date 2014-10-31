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

#include "Game.h"
#include "State.h"
#include "MainMenuState.h"
#include "SettingsState.h"
#include "PlayState.h"
#include <fstream>
#include <cmath>

Game::Game(sf::RenderWindow &window, int aaLevel, unsigned int originalDefinition)
: m_window(window), m_assets(), m_oldState(0), m_state(0),
  m_saveFolder("/data/data/fr.mathdu07.circles/files/"),
  m_aaLevel(aaLevel), m_originalDefinition(originalDefinition),
  m_clearColor(sf::Color(51, 51, 51))
{

}

Game::~Game()
{
    if (m_oldState)
    {
        delete m_oldState;
    }

    if (m_state)
    {
        delete m_state;
    }
}

sf::RenderWindow& Game::getWindow()
{
    return m_window;
}

bool Game::create()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = m_aaLevel;
	m_window.create(sf::VideoMode::getDesktopMode(), "Circles", sf::Style::Titlebar | sf::Style::Close, settings);

	return true;
}

void Game::run()
{
	if (!create())
		return;

	m_assets.loadAssets();
	setState(new MainMenuState(*this));

    sf::Event event;
    sf::Time updateDelta(getDelta());
    sf::Clock updateClock;
    sf::Time nextUpdate(updateClock.getElapsedTime());

    while (m_window.isOpen())
    {
        while (m_window.pollEvent(event))
            handleEvent(event);

        if (nextUpdate <= updateClock.getElapsedTime())
        {
            sf::Time currentTime(updateClock.getElapsedTime());
            while (nextUpdate <= currentTime)
            {
                m_state->update();
                nextUpdate += updateDelta;
            }

            m_window.clear(m_clearColor);
            beforeRendering();
            m_state->render(getRenderTarget());
            afterRendering();
            m_window.display();
        }
        else
        {
            sf::Time sleepTime(nextUpdate - updateClock.getElapsedTime());
            sf::sleep(sleepTime);
        }

    }
}

sf::Time Game::getDelta() const
{
	return sf::seconds(1/30.f);
}

void Game::handleEvent(sf::Event &event)
{
    switch (event.type)
    {
    case sf::Event::Closed:
        exit();
        break;
    default:
        break;
    }

    if (m_window.isOpen() && m_state != 0)
    {
    	beforeHandleEvent(event);
        m_state->handleEvent(event);
    }
}

void Game::exit()
{
	LOGI("Exit");
    m_window.close();
}

Graphics const& Game::gfx()
{
    return m_assets.getGraphics();
}

Fonts const& Game::fonts()
{
    return m_assets.getFonts();
}

void Game::setState(State *newState)
{
    if (newState != m_state && m_state != 0 && newState != 0)
    {
        m_state->deInit();

        if (m_oldState)
            delete m_oldState;

        m_oldState = m_state;
        m_state = 0;
    }

    if (newState)
    {
        m_state = newState;
        m_state->init();
    }
}

State* Game::getState()
{
    return m_state;
}

sf::Vector2u Game::getSize() const
{
    return m_window.getSize();
}

void Game::setView(sf::View view)
{
	m_window.setView(view);
}

void Game::resetView()
{
	setView(sf::View(sf::FloatRect(0, 0, getSize().x, getSize().y)));
}

sf::View Game::getView() const
{
	return m_window.getView();
}

void Game::saveMaxScore(int maxScore)
{
	std::ofstream file(m_saveFolder + "score-b1", std::ofstream::out | std::ofstream::trunc | std::ofstream::binary);

	file << maxScore;

	file.close();
}

int Game::readMaxScore()
{
	std::ifstream file(m_saveFolder + "score-b1", std::ifstream::in | std::ifstream::binary);

	if (!file)
		return 0;

	int maxScore;
	file >> maxScore;

	file.close();

	return maxScore;
}

sf::RenderTarget& Game::getRenderTarget()
{
	return m_window;
}

void Game::beforeHandleEvent(sf::Event &event)
{

}

void Game::beforeRendering()
{

}

void Game::afterRendering()
{

}

unsigned int Game::getOriginalDefinition() const
{
	return m_originalDefinition;
}

unsigned int Game::getDefinition() const
{
	return std::min(getSize().x, getSize().y);
}

float Game::getScale() const
{
	return getDefinition() / (float) getOriginalDefinition();
}

sf::Color Game::getClearColor() const
{
	return m_clearColor;
}

void Game::setClearColor(sf::Color color)
{
	m_clearColor = color;
}

void Game::switchToMainMenu()
{
    setState(new MainMenuState(*this));
}

void Game::switchToSettings()
{
    setState(new SettingsState(*this));
}

void Game::play()
{
    setState(new PlayState(*this));
}
