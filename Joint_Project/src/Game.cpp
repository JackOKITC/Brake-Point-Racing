#include "Game.h"

Game::Game(sf::Font &font) :
	m_window(sf::VideoMode(900,600,32), "Joint Project", sf::Style::Default),
	m_font(font)
{
}

Game::~Game()
{
}

void Game::run()
{
	static double const MS_PER_UPDATE = 10.0;
	sf::Clock clock;
	sf::Int32 lag = 0;

	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();

		lag += dt.asMilliseconds();

		while (lag > MS_PER_UPDATE)
		{
			update(dt);
			lag -= MS_PER_UPDATE;
		}
		update(dt);
		render(m_window);
	}
}

void Game::update(sf::Time deltaTime)
{
}

void Game::render(sf::RenderWindow &window)
{
}
