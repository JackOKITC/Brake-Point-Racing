#include "Game.h"

// Updates per milliseconds
static sf::Int32 MS_PER_UPDATE = 10.0;;

Game::Game(sf::Font &font, sf::Font &titleFont) :
	m_titleFont(titleFont),
	m_window(sf::VideoMode(900,600,32), "Brake Point Racing", sf::Style::Default),
	m_font(font)
{
	// pointer to GameState object, will be passed to each menu state so
	// they can change the state in their own source files


	int currentLevel = 1;
	if (!LevelLoader::load(currentLevel, m_level))
	{
		std::cout << "Level not loaded" << std::endl;
	}

	ResourceManager::instance().loadData(m_level);
	m_player = new Player(m_level);

	m_currentGameState = new GameState(GameState::SPLASH_STATE);
	m_preRaceScreen = new PreRace(m_titleFont, m_currentGameState, m_player);
	m_playScreen = new Play(m_font, m_currentGameState, m_preRaceScreen->m_whichLabel, m_player, &m_level);
	m_splashScreen = new Splash(m_currentGameState, m_titleFont);
	m_menuScreen = new Menu(m_titleFont, m_currentGameState);
	m_upgradeScreen = new Garage(m_titleFont, m_font, m_currentGameState, m_player);
	m_endScreen = new EndScreen(m_titleFont, m_currentGameState);
	
	sBuffer = ResourceManager::instance().m_soundHolder["MusicBG"];
	music.setBuffer(sBuffer);

	m_optionsScreen = new Options(m_titleFont, m_currentGameState, music);
	
	DefaultView = m_window.getDefaultView();
}

Game::~Game()
{
}

void Game::run()
{
	music.play();
	music.setLoop(true);
	
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
		m_window.setView(DefaultView);
		m_splashScreen->update(&m_controller, deltaTime);
		break;
	case GameState::MENU_STATE:
		m_window.setView(DefaultView);
		m_menuScreen->update(m_controller.m_currentState, m_controller, deltaTime);
		break;
	case GameState::PLAY_STATE:
		m_playScreen->update(m_controller, MS_PER_UPDATE, m_preRaceScreen->m_whichLabel);
		break;
	case GameState::UPGRADE_STATE:
		m_window.setView(DefaultView);
		m_upgradeScreen->update(m_controller, deltaTime);
		break;
	case GameState::OPTIONS_STATE:
		m_window.setView(DefaultView);
		m_optionsScreen->update(m_controller.m_currentState, m_controller, music);
		break;
	case GameState::CREDITS_STATE:
		m_window.setView(DefaultView);
		break;
	case GameState::PRERACE_STATE:
		m_window.setView(DefaultView);
		m_preRaceScreen->update(m_controller.m_currentState, m_controller);
		break;
	case GameState::END_STATE:
		m_endScreen->update(m_controller, deltaTime, m_playScreen->m_position);
		break;
	default:
		break;
	}
}

void Game::render(sf::RenderWindow &window)
{
	window.clear(sf::Color(30, 50, 90));
	switch (*m_currentGameState)
	{
	case GameState::SPLASH_STATE:
		m_splashScreen->render(window);
		break;
	case GameState::MENU_STATE:	
		m_menuScreen->render(window, m_clock);
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
	case GameState::PRERACE_STATE:
		m_preRaceScreen->render(window);
		break;
	case GameState::END_STATE:
		m_endScreen->render(window);
		break;
	default:
		break;
	}
	window.display();
}