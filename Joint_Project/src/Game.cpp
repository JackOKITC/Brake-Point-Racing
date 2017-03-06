#include "Game.h"

Game::Game(sf::Font &font) :
	m_window(sf::VideoMode(900,600,32), "Team J", sf::Style::Default),
	m_font(font),
	m_currentGameState(GameState::SPLASH)
{
	m_controller = new Xbox360Controller();
	m_splashScreen = new Splash();
	m_menuScreen = new Menu(font);
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
	m_controller->update();
	checkGameStateChange();
	switch (m_currentGameState)
	{
	case SPLASH:
		m_splashScreen->update(m_controller);
		break;
	case MENU:
		m_menuScreen->update();
		break;
	case PLAY:

		break;
	case OPTIONS:

		break;
	case CREDITS:

		break;
	default:
		break;
	}
}

void Game::render(sf::RenderWindow &window)
{
	window.clear(sf::Color::Green);
	switch (m_currentGameState)
	{
	case SPLASH:
		m_splashScreen->render(window);
		break;
	case MENU:
		m_menuScreen->render(window);
		break;
	case PLAY:

		break;
	case OPTIONS:

		break;
	case CREDITS:

		break;

	default:
		break;
	}
	window.display();
}

void Game::checkGameStateChange()
{
	if (m_splashScreen->changeGameState())
	{
		m_currentGameState = GameState::MENU;
	}
}


