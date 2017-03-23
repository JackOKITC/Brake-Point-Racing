#include "Game.h"

// Updates per milliseconds
static sf::Int32 MS_PER_UPDATE = 10.0;;

Game::Game(sf::Font &font, sf::Font &titleFont) :
	m_titleFont(titleFont),
	m_window(sf::VideoMode(900,600,32), "Brake Point Racing"),
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

	// Initialising all the screen objects
	m_currentGameState = new GameState(GameState::SPLASH_STATE);
	m_preRaceScreen = new PreRace(m_titleFont, m_currentGameState, m_player);
	m_playScreen = new Play(m_font, m_currentGameState, m_preRaceScreen->m_whichLabel, m_player, &m_level);
	m_splashScreen = new Splash(m_currentGameState, m_titleFont);
	m_menuScreen = new Menu(m_titleFont, m_currentGameState);
	m_optionsScreen = new Options(m_titleFont, m_currentGameState, music);
	m_upgradeScreen = new Garage(m_titleFont, m_font, m_currentGameState, m_player);
	m_endScreen = new EndScreen(m_titleFont, m_currentGameState);
	m_credits = new Credits(m_titleFont, m_currentGameState);

	// Initialises the soundbuffer to store the music loaded from yaml
	sBuffer = ResourceManager::instance().m_soundHolder["MusicBG"];
	music.setBuffer(sBuffer);

	DefaultView = m_window.getDefaultView();	// Initialises the view to the default view
}

Game::~Game()
{
}

void Game::run()
{
	// Plays and loops the music
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
	m_controller.update();	// updates the controller object

	// A switch statement for changing the current gamestate and hence, game screen
	switch (*m_currentGameState)
	{
	case GameState::SPLASH_STATE:
		m_window.setView(DefaultView);	// Sets the view to default, so the resized viewport in PLAY_STATE doesn't affect other screens
		m_splashScreen->update(&m_controller, deltaTime);	// updating splash screen
		break;
	case GameState::MENU_STATE:
		m_window.setView(DefaultView);
		m_menuScreen->update(m_controller.m_currentState, m_controller, deltaTime);	// updaying menu screen
		break;
	case GameState::PLAY_STATE:
		m_playScreen->update(m_controller, MS_PER_UPDATE, m_preRaceScreen->m_whichLabel);	// updating play screen
		break;
	case GameState::UPGRADE_STATE:
		m_window.setView(DefaultView);
		m_upgradeScreen->update(m_controller, deltaTime);	// updating upgrade screen
		break;
	case GameState::OPTIONS_STATE:
		m_window.setView(DefaultView);
		m_optionsScreen->update(m_controller.m_currentState, m_controller, music);	// updating options screen
		break;
	case GameState::CREDITS_STATE:
		m_window.setView(DefaultView);
		m_credits->update(m_controller, deltaTime);	// updating credits screen
		break;
	case GameState::PRERACE_STATE:
		m_window.setView(DefaultView);
		m_preRaceScreen->update(m_controller.m_currentState, m_controller);	// updating prerace screen
		break;
	case GameState::END_STATE:
		m_endScreen->update(m_controller, deltaTime, m_playScreen->m_racePosition);	// updating post race screen
		break;
	default:
		break;
	}
}

void Game::render(sf::RenderWindow &window)
{
	window.clear(sf::Color(30, 50, 90));	// clears the window to our preferred colour, a royal blue
	
	// switch statement for rendering each screen object
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
		m_credits->render(window);
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