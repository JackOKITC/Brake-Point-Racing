#include "Menu.h"

Menu::Menu(sf::Font & font, GameState *gameState) :
	m_font(font)
	, TIME_PER_UPDATE(sf::microseconds(650))
{
	m_gameState = gameState;

	// Loading in the main menu background texture
	if (!m_backgroundTex.loadFromFile(".//resources//images//UI//bg2.png"))
	{
		std::cout << "Problem loading Texture for menu screen";
	}

	m_backgroundSprite.setTexture(m_backgroundTex);
	m_backgroundSprite.setScale(0.01f, 0.01f);
	m_backgroundSprite.setOrigin(m_backgroundTex.getSize().x / 2, m_backgroundTex.getSize().y / 2);
	m_backgroundSprite.setPosition(450, 310);

	m_timeStop = false;
	m_transitionStop = false;

	for (int i = 0; i < BUTTON_COUNT; i++)
	{
		m_buttons[i] = new Button(&m_strings[i], &sf::Vector2f(450, 200 + (i * 100)), &m_font);
		m_buttons[i]->loseFocus();
	}

	m_currentBtn = 0;
	m_buttons[m_currentBtn]->getFocus();
}

Menu::~Menu()
{
}

void Menu::update(GamePadState m_state, Xbox360Controller & m_controller, sf::Time deltaTime)
{
	if (m_transitionStop)
	{
		checkButtonSelected(m_state, m_controller);
		selectedButton(m_state, m_controller);
	}

	if (!m_timeStop)
	{
		deltaTime.Zero;
		m_timeStop = true;
	}

	if (m_time.asSeconds() <= 3.6)
	{
		m_backgroundSprite.setRotation(m_backgroundSprite.getRotation() - 2);
		m_backgroundSprite.scale(1.003, 1.003);
		m_time += TIME_PER_UPDATE;
	}
	else
	{
		m_transitionStop = true;
	}
}

void Menu::render(sf::RenderWindow & window)
{
	window.clear(sf::Color(0,0,0));
	window.draw(m_backgroundSprite);
	if (m_transitionStop)
	{
		for (int i = 0; i < BUTTON_COUNT; i++)
		{
			m_buttons[i]->render(window);

		}
	}
}


// Function to check which button is selected
void Menu::checkButtonSelected(GamePadState m_state, Xbox360Controller m_controller)
{
	// if Down toggled
	if ((m_state.dpadDown && !m_controller.m_previousState.dpadDown) || (m_state.LeftThumbStick.y > 50 && m_controller.m_previousState.LeftThumbStick.y < 50))
	{
		m_buttons[m_currentBtn]->loseFocus(); // currently selected button loses focus, unhighlighted
		m_currentBtn = m_currentBtn + 1; // currentBtn selected incremented
		if (m_currentBtn > BUTTON_COUNT - 1)
		{
			m_currentBtn = m_currentBtn - 1; // safe guard to stop out of bound behaviour
		}

		m_buttons[m_currentBtn]->getFocus(); // newly seleted button highlighted
		m_buttonSelected = (button)m_currentBtn; // enum for buttons set to current int value of current button
	}

	// if Up toggled, same behaviour as above except the counter is decremented
	if ((m_state.dpadUp && !m_controller.m_previousState.dpadUp) || (m_state.LeftThumbStick.y < -50 && m_controller.m_previousState.LeftThumbStick.y > -50))
	{
		m_buttons[m_currentBtn]->loseFocus();
		m_currentBtn = m_currentBtn - 1;
		if (m_currentBtn < 0)
		{
			m_currentBtn = 0;
		}

		m_buttons[m_currentBtn]->getFocus();
		m_buttonSelected = (button)m_currentBtn;
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
			*m_gameState = GameState::PLAY_STATE;
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