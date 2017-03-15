#include "Game.h"

static double const MS_PER_UPDATE = 10.0;

Game::Game(sf::Font &font, sf::Font &titleFont) :
	m_titleFont(titleFont),
	m_window(sf::VideoMode(900,600,32), "Brake Point Racing", sf::Style::Default),
	m_font(font)
{

	// pointer to GameState object, will be passed to each menu state so
	// they can change the state in their own source files
	m_currentGameState = new GameState();
	*m_currentGameState = GameState::PLAY_STATE;
	m_playScreen = new Play(m_currentGameState);
	m_splashScreen = new Splash(m_currentGameState, m_titleFont);
	m_menuScreen = new Menu(font, m_currentGameState);
	m_upgradeScreen = new Garage(font, m_currentGameState);
	m_optionsScreen = new Options(font, m_currentGameState);
}

Game::~Game()
{
}

void Game::run()
{
	
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

	switch (*m_currentGameState)
	{
	case GameState::SPLASH_STATE:
		m_splashScreen->update(&m_controller, deltaTime);
		break;
	case GameState::MENU_STATE:
		m_menuScreen->update(m_controller.m_currentState, m_controller, deltaTime);
		break;
	case GameState::PLAY_STATE:
		m_playScreen->update(m_controller, MS_PER_UPDATE);
		break;
	case GameState::UPGRADE_STATE:
		m_upgradeScreen->update(m_controller, deltaTime);
		break;
	case GameState::OPTIONS_STATE:
		m_optionsScreen->update(m_controller.m_currentState, m_controller);
		break;
	case GameState::CREDITS_STATE:

		break;
	default:
		break;
	}
}

void Game::render(sf::RenderWindow &window)
{
	window.clear(sf::Color(0, 0, 0));
	switch (*m_currentGameState)
	{
	case GameState::SPLASH_STATE:
		m_splashScreen->render(window);
		break;
	case GameState::MENU_STATE:
		m_menuScreen->render(window);
		break;
	case GameState::PLAY_STATE:
		m_playScreen->render(window);
		break;
	case GameState::UPGRADE_STATE:
		m_upgradeScreen->render(window);
		break;
	case GameState::OPTIONS_STATE:
		m_optionsScreen->render(window);
		break;
	case GameState::CREDITS_STATE:

		break;

	default:
		break;
	}
	window.display();
}