#include "Menu.h"

Menu::Menu(sf::Font & font, GameState *gameState) :
	m_font(font)
	, TIME_PER_UPDATE(sf::microseconds(1450))
{
	m_gameState = gameState; // initialises the gamestate object

	/// <summary>
	/// The convex line variables initialised with their total points, their positions,
	/// And their starting colours to represent them being unselected.
	/// </summary>
#pragma region Convex Lines

	m_raceLine.setPointCount(4);
	m_raceLine.setPoint(0, sf::Vector2f(123.5, 102));
	m_raceLine.setPoint(1, sf::Vector2f(223.5, 67));
	m_raceLine.setPoint(2, sf::Vector2f(229.1, 77));
	m_raceLine.setPoint(3, sf::Vector2f(135, 122));
	m_raceLine.setFillColor(sf::Color(m_unselect));
	
	m_garLine.setPointCount(4);
	m_garLine.setPoint(0, sf::Vector2f(168.5, 205));
	m_garLine.setPoint(1, sf::Vector2f(269.5, 180));
	m_garLine.setPoint(2, sf::Vector2f(271.75, 190));
	m_garLine.setPoint(3, sf::Vector2f(172.5, 225));
	m_garLine.setFillColor(sf::Color(m_unselect));

	m_optLine.setPointCount(4);
	m_optLine.setPoint(0, sf::Vector2f(181, 290.5));
	m_optLine.setPoint(1, sf::Vector2f(284.5, 298));
	m_optLine.setPoint(2, sf::Vector2f(284.5, 308));
	m_optLine.setPoint(3, sf::Vector2f(181, 310.5));
	m_optLine.setFillColor(sf::Color(m_unselect));
	
	m_credLine.setPointCount(4);
	m_credLine.setPoint(0, sf::Vector2f(172.75, 378));
	m_credLine.setPoint(1, sf::Vector2f(271.5, 415));
	m_credLine.setPoint(2, sf::Vector2f(267.5, 426));
	m_credLine.setPoint(3, sf::Vector2f(167.5, 401));
	m_credLine.setFillColor(sf::Color(m_unselect));

	m_exitLine.setPointCount(4);
	m_exitLine.setPoint(0, sf::Vector2f(137, 478));
	m_exitLine.setPoint(1, sf::Vector2f(227, 527));
	m_exitLine.setPoint(2, sf::Vector2f(221.5, 537.5));
	m_exitLine.setPoint(3, sf::Vector2f(127, 498));
	m_exitLine.setFillColor(sf::Color(m_unselect));

#pragma endregion

	m_backgroundTex = ResourceManager::instance().m_holder["MenuBG"];	// sets the background texture to be the MenuBG from the yaml file
	
	// Variables setting the texture and position of the bg sprite
	m_backgroundSprite.setTexture(m_backgroundTex);
	m_backgroundSprite.setPosition(-1400, -200);

	m_flagTex = ResourceManager::instance().m_holder["Flag"];	// sets the flag texture to be Flag from the yaml file

	// Variables setting the texture, position, and scale of the flag sprite
	m_flagSprite.setTexture(m_flagTex);
	m_flagSprite.setPosition(0, 0);
	m_flagSprite.setScale(0.5, 0.6);

	m_timeStop = false;	// initialises m_timeStop to false;
	m_transitionStop = false;	// intialises m_transitionStop to false;

	if (!m_shader.loadFromFile(".\\resources\\Shader\\Vert.txt", ".\\resources\\Shader\\Frag.txt"))	// couts an error if the shader files can not be loaded
	{
		std::cout << "Error loading shader" << std::endl;
	}

	// sets the paramaters for the shader
	m_shader.setParameter("uTexture", m_flagTex);
	m_shader.setParameter("uPositionFreq", 0.1f);
	m_shader.setParameter("uSpeed", 10);
	m_shader.setParameter("uStrength", 0.01f);

	// an if statement which diffrentiates the x value of the labels in the array based on their
	// array position, due to fitting them properly around the curve of the wheel in the MenuBG sprite
	for (int i = 0; i < LABEL_COUNT; i++)
	{
		if (i < 1 || i > 3)
		{
			m_labels[i] = new Label(&m_strings[i], &m_font, &sf::Vector2f(290, 40 + (i * 130)), 28, sf::Color(140, 80, 160));
			m_outline[i] = new Label(&m_strings[i], &m_font, &sf::Vector2f(293, 40 + (i * 130)), 28, sf::Color(195, 80, 215));
		}
		else if (i == 1 || i == 3)
		{
			m_labels[i] = new Label(&m_strings[i], &m_font, &sf::Vector2f(365, 40 + (i * 130)), 28, sf::Color(140, 80, 160));
			m_outline[i] = new Label(&m_strings[i], &m_font, &sf::Vector2f(368, 40 + (i * 130)), 28, sf::Color(195, 80, 215));
		}
		else
		{
			m_labels[i] = new Label(&m_strings[i], &m_font, &sf::Vector2f(385, 40 + (i * 130)), 28, sf::Color(140, 80, 160));
			m_outline[i] = new Label(&m_strings[i], &m_font, &sf::Vector2f(388, 40 + (i * 130)), 28, sf::Color(195, 80, 215));
		}
		
		m_labels[i]->loseFocus();	// defaults all the labels to be unhighlighted
	}

	m_currentLab = 0;	// initialises m_currentLab to 0, so none are selected
	m_labels[m_currentLab]->getFocus();	// sets the current label in the array to be focused upon
}

Menu::~Menu()
{
}

void Menu::update(GamePadState m_state, Xbox360Controller & m_controller, sf::Time deltaTime)
{
	if (m_transitionStop)
	{
		checkButtonSelected(m_state, m_controller);	// checks which button is selected
		selectedButton(m_state, m_controller);	// selects the button
	}

	if (!m_timeStop)
	{
		deltaTime.Zero;	// resets time to zero
		m_timeStop = true;	// m_timeStop being true
	}

	// if statement letting the background sprite transition until 2 seconds has passed
	if (m_time.asSeconds() <= 2.0)
	{
		if (m_backgroundSprite.getPosition().x < -700)
		{
			m_backgroundSprite.move(0.6, 0);	// translates the background sprite onto the screen along the x axis
		}
		
		m_time += TIME_PER_UPDATE;	// updates the time
	}
	else
	{
		m_transitionStop = true;
	}
}

void Menu::render(sf::RenderWindow & window, sf::Clock clock)
{
	window.clear(sf::Color(30, 50, 90));	// clears the window to our desired colour, royal blue
	window.draw(m_flagSprite, &m_shader);	// draws the flag sprite and its used shader
	window.draw(m_backgroundSprite);	// draws the background sprite
	
	
	m_shader.setParameter("uTime", clock.getElapsedTime().asSeconds());	// changes the parameter of the shader based on time
	
	// will only draw the included objects when the bg transition is over
	if (m_transitionStop)
	{
		window.draw(m_raceLine);	// draws the line pointing to "Race"
		window.draw(m_garLine);		// draws the line pointing to "Garage"
		window.draw(m_optLine);		// draws the line pointing to "Options"
		window.draw(m_credLine);	// draws the line pointing to "Credits"
		window.draw(m_exitLine);	// draws the line pointing to "Exit"
		
		for (int i = 0; i < LABEL_COUNT; i++)
		{
			m_outline[i]->render(window);	// draws the outline of the labels
			m_labels[i]->render(window);	// draws the label array
		}
	}
}


// Function to check which button is selected
void Menu::checkButtonSelected(GamePadState m_state, Xbox360Controller m_controller)
{
	// a switch statement which unhighlights the lines pointing to each label based on which label is curerntly selected
	switch (m_currentLab)
	{
	case 0:	// if race is selected:
		m_raceLine.setFillColor(sf::Color(m_select));
		m_garLine.setFillColor(sf::Color(m_unselect));
		m_optLine.setFillColor(sf::Color(m_unselect));
		m_credLine.setFillColor(sf::Color(m_unselect));
		m_exitLine.setFillColor(sf::Color(m_unselect));	
		break;
	case 1:	// if garage is selected:
		m_raceLine.setFillColor(sf::Color(m_unselect));
		m_garLine.setFillColor(sf::Color(m_select));
		m_optLine.setFillColor(sf::Color(m_unselect));
		m_credLine.setFillColor(sf::Color(m_unselect));
		m_exitLine.setFillColor(sf::Color(m_unselect));
		break;
	case 2:	// if options is selected:
		m_raceLine.setFillColor(sf::Color(m_unselect));
		m_garLine.setFillColor(sf::Color(m_unselect));
		m_optLine.setFillColor(sf::Color(m_select));
		m_credLine.setFillColor(sf::Color(m_unselect));
		m_exitLine.setFillColor(sf::Color(m_unselect));
		break;
	case 3: // if credits is selected:
		m_raceLine.setFillColor(sf::Color(m_unselect));
		m_garLine.setFillColor(sf::Color(m_unselect));
		m_optLine.setFillColor(sf::Color(m_unselect));
		m_credLine.setFillColor(sf::Color(m_select));
		m_exitLine.setFillColor(sf::Color(m_unselect));
		break;
	case 4: // if exit is selected:
		m_raceLine.setFillColor(sf::Color(m_unselect));
		m_garLine.setFillColor(sf::Color(m_unselect));
		m_optLine.setFillColor(sf::Color(m_unselect));
		m_credLine.setFillColor(sf::Color(m_unselect));
		m_exitLine.setFillColor(sf::Color(m_select));
		break;
	}

	// if Down toggled
	if ((m_state.dpadDown && !m_controller.m_previousState.dpadDown) || (m_state.LeftThumbStick.y > 50 && m_controller.m_previousState.LeftThumbStick.y < 50))
	{
		m_labels[m_currentLab]->loseFocus(); // currently selected button loses focus, unhighlighted
		m_currentLab = m_currentLab + 1; // currentBtn selected incremented
		if (m_currentLab > LABEL_COUNT - 1)
		{
			m_currentLab = m_currentLab - 1; // safe guard to stop out of bound behaviour
		}

		m_labels[m_currentLab]->getFocus(); // newly seleted button highlighted
		m_buttonSelected = (button)m_currentLab; // enum for buttons set to current int value of current button
	}

	// if Up toggled, same behaviour as above except the counter is decremented
	if ((m_state.dpadUp && !m_controller.m_previousState.dpadUp) || (m_state.LeftThumbStick.y < -50 && m_controller.m_previousState.LeftThumbStick.y > -50))
	{
		m_labels[m_currentLab]->loseFocus();
		m_currentLab = m_currentLab - 1;
		if (m_currentLab < 0)
		{
			m_currentLab = 0;
		}

		m_labels[m_currentLab]->getFocus();
		m_buttonSelected = (button)m_currentLab;
	}
}

// Function to check if the selected button has been pressed
void Menu::selectedButton(GamePadState m_gamePadState, Xbox360Controller m_controller)
{
	switch (m_buttonSelected) // Switch statement for the buttons
	{
	case button::Play:	// The play button 
		if (m_gamePadState.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{
			*m_gameState = GameState::PRERACE_STATE;
		}
		break;
	case button::Garage:
		if (m_gamePadState.A && !m_controller.m_previousState.A)
		{
			*m_gameState = GameState::UPGRADE_STATE;
		}
		  break;
	case button::Options:	// The options button 
		if (m_gamePadState.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{
			*m_gameState = GameState::OPTIONS_STATE;
		}
		break;
	case button::Credits:
		if (m_gamePadState.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{
			*m_gameState = GameState::CREDITS_STATE;	// Exits the game
		}
		break;
	case button::Exit:	// The exit button 
		if (m_gamePadState.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{
			exit(0);	// Exits the game
		}
		break;
	default:
		break;
	}
}