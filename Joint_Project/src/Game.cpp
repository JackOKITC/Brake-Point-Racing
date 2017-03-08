#include "Game.h"

Game::Game(sf::Font &font) :
	m_window(sf::VideoMode(900,600,32), "Team J", sf::Style::Default),
	m_font(font),
	m_currentGameState(GameState::SPLASH_STATE)
{
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
	m_controller.update();
	checkGameStateChange();
	switch (m_currentGameState)
	{
	case GameState::SPLASH_STATE:
		m_splashScreen->update(&m_controller, deltaTime);
		break;
	case GameState::MENU_STATE:
		m_menuScreen->update(m_controller.m_currentState, m_controller, deltaTime);
		break;
	case GameState::PLAY_STATE:

		break;
	case GameState::OPTIONS_STATE:

		break;
	case GameState::CREDITS_STATE:

		break;
	default:
		break;
	}
}

void Game::render(sf::RenderWindow &window)
{
	window.clear(sf::Color(235, 233, 247));
	switch (m_currentGameState)
	{
	case GameState::SPLASH_STATE:
		m_splashScreen->render(window);
		break;
	case GameState::MENU_STATE:
		m_menuScreen->render(window);
		break;
	case GameState::PLAY_STATE:

		break;
	case GameState::OPTIONS_STATE:

		break;
	case GameState::CREDITS_STATE:

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
		m_currentGameState = GameState::MENU_STATE;
	}
}