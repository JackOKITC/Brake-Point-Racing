#include <Garage.h>

Garage::Garage(sf::Font font, GameState * gameState) :
	m_font(font)
{
	m_state = gameState;
	if (!m_backgroundTex.loadFromFile(".//resources//images//car_parts//all.png"))
	{
		std::cout << "Problem loading Texture for splash screen";
	}
	m_backgroundSprite.setTexture(m_backgroundTex);
	m_backgroundSprite.setOrigin(m_backgroundTex.getSize().x / 2, m_backgroundTex.getSize().y / 2);
	m_backgroundSprite.setPosition(450, 300);

	for (int i = 0; i < BUTTON_COUNT; i++)
	{
		m_buttons[i] = new Button(&m_strings[i], &sf::Vector2f(150 + (i * 200), 400 ), &m_font);
	}
	m_backButton = new Button(&m_backString, &sf::Vector2f(450, 500), &m_font);
}

Garage::~Garage()
{
}

void Garage::update(Xbox360Controller & controller, sf::Time dt)
{
	checkButtonSelected(controller.m_currentState, controller);
	selectedButton(controller.m_currentState, controller);
}

void Garage::render(sf::RenderWindow & window)
{
	window.draw(m_backgroundSprite);
	for (int i = 0; i < BUTTON_COUNT; i++)
	{
		m_buttons[i]->render(window);
	}
	m_backButton->render(window);
}


// Function to check which button is selected
void Garage::checkButtonSelected(GamePadState m_state, Xbox360Controller m_controller)
{
	switch (m_buttonSelected)	// Switch statement for every button
	{

	case upgradebutton::Engine:	// The engine button

						// Sets the engine button to be highlighted and the other buttons to be not
		m_buttons[0]->getFocus();
		m_buttons[1]->loseFocus();
		m_buttons[2]->loseFocus();
		m_buttons[3]->loseFocus();
		m_backButton->loseFocus();

		// Checks if the down button has been pressed
		if ((m_state.dpadRight && !m_controller.m_previousState.dpadRight) || (m_state.LeftThumbStick.x > 50 && m_controller.m_previousState.LeftThumbStick.x < 50))
		{
			m_buttonSelected = upgradebutton::Turbo;	// Switches to the turbo button
		}

		// Checks if the up button has been pressed
		if ((m_state.dpadLeft && !m_controller.m_previousState.dpadLeft) || (m_state.LeftThumbStick.x < -50 && m_controller.m_previousState.LeftThumbStick.x > -50))
		{
			m_buttonSelected = upgradebutton::Tires;	// Switches to the tires button
		}

		// Checks if the down button has been pressed
		if ((m_state.dpadDown && !m_controller.m_previousState.dpadDown) || (m_state.LeftThumbStick.y > 50 && m_controller.m_previousState.LeftThumbStick.y < 50))
		{
			m_buttonSelected = upgradebutton::Back;	// Switches to the Engine button
		}

		// Checks if the up button has been pressed
		if ((m_state.dpadUp && !m_controller.m_previousState.dpadUp) || (m_state.LeftThumbStick.y < -50 && m_controller.m_previousState.LeftThumbStick.y > -50))
		{
			m_buttonSelected = upgradebutton::Back;	// Switches to the Engine button
		}
		break;
	case upgradebutton::Turbo: // The turbo button 

						 // Sets the turbo button to be highlighted and the other buttons to be not
		m_buttons[0]->loseFocus();
		m_buttons[1]->getFocus();
		m_buttons[2]->loseFocus();
		m_buttons[3]->loseFocus();
		m_backButton->loseFocus();

		// Checks if the down button has been pressed
		if ((m_state.dpadRight && !m_controller.m_previousState.dpadRight) || (m_state.LeftThumbStick.x > 50 && m_controller.m_previousState.LeftThumbStick.x < 50))
		{
			m_buttonSelected = upgradebutton::Handling;	// Switches to the handling button
		}

		// Checks if the up button has been pressed
		if ((m_state.dpadLeft && !m_controller.m_previousState.dpadLeft) || (m_state.LeftThumbStick.x < -50 && m_controller.m_previousState.LeftThumbStick.x > -50))
		{
			m_buttonSelected = upgradebutton::Engine;	// Switches to the engine button
		}

		// Checks if the down button has been pressed
		if ((m_state.dpadDown && !m_controller.m_previousState.dpadDown) || (m_state.LeftThumbStick.y > 50 && m_controller.m_previousState.LeftThumbStick.y < 50))
		{
			m_buttonSelected = upgradebutton::Back;	// Switches to the Engine button
		}

		// Checks if the up button has been pressed
		if ((m_state.dpadUp && !m_controller.m_previousState.dpadUp) || (m_state.LeftThumbStick.y < -50 && m_controller.m_previousState.LeftThumbStick.y > -50))
		{
			m_buttonSelected = upgradebutton::Back;	// Switches to the Engine button
		}
		break;
	case upgradebutton::Handling:	// The handling button

							// Sets the options button to be highlighted and the other buttons to be not
		m_buttons[0]->loseFocus();
		m_buttons[1]->loseFocus();
		m_buttons[2]->getFocus();
		m_buttons[3]->loseFocus();
		m_backButton->loseFocus();

		// Checks if the down button has been pressed
		if ((m_state.dpadRight && !m_controller.m_previousState.dpadRight) || (m_state.LeftThumbStick.x > 50 && m_controller.m_previousState.LeftThumbStick.x < 50))
		{
			m_buttonSelected = upgradebutton::Tires;	// Switches to the tires button
		}

		// Checks if the up button has been pressed
		if ((m_state.dpadLeft && !m_controller.m_previousState.dpadLeft) || (m_state.LeftThumbStick.x < -50 && m_controller.m_previousState.LeftThumbStick.x > -50))
		{
			m_buttonSelected = upgradebutton::Turbo;	// Switches to the turbo button
		}

		// Checks if the down button has been pressed
		if ((m_state.dpadDown && !m_controller.m_previousState.dpadDown) || (m_state.LeftThumbStick.y > 50 && m_controller.m_previousState.LeftThumbStick.y < 50))
		{
			m_buttonSelected = upgradebutton::Back;	// Switches to the Engine button
		}

		// Checks if the up button has been pressed
		if ((m_state.dpadUp && !m_controller.m_previousState.dpadUp) || (m_state.LeftThumbStick.y < -50 && m_controller.m_previousState.LeftThumbStick.y > -50))
		{
			m_buttonSelected = upgradebutton::Back;	// Switches to the Engine button
		}
		break;
	case upgradebutton::Tires:	// The tire button

						// Sets the exit button to be highlighted and the other buttons to be not
		m_buttons[0]->loseFocus();
		m_buttons[1]->loseFocus();
		m_buttons[2]->loseFocus();
		m_buttons[3]->getFocus();
		m_backButton->loseFocus();

		// Checks if the down button has been pressed
		if ((m_state.dpadRight && !m_controller.m_previousState.dpadRight) || (m_state.LeftThumbStick.x > 50 && m_controller.m_previousState.LeftThumbStick.x < 50))
		{
			m_buttonSelected = upgradebutton::Engine;	// Switches to the engine button
		}

		// Checks if the up button has been pressed
		if ((m_state.dpadLeft && !m_controller.m_previousState.dpadLeft) || (m_state.LeftThumbStick.x < -50 && m_controller.m_previousState.LeftThumbStick.x > -50))
		{
			m_buttonSelected = upgradebutton::Handling;	// Switches to the handling button
		}

		// Checks if the down button has been pressed
		if ((m_state.dpadDown && !m_controller.m_previousState.dpadDown) || (m_state.LeftThumbStick.y > 50 && m_controller.m_previousState.LeftThumbStick.y < 50))
		{
			m_buttonSelected = upgradebutton::Back;	// Switches to the Engine button
		}

		// Checks if the up button has been pressed
		if ((m_state.dpadUp && !m_controller.m_previousState.dpadUp) || (m_state.LeftThumbStick.y < -50 && m_controller.m_previousState.LeftThumbStick.y > -50))
		{
			m_buttonSelected = upgradebutton::Back;	// Switches to the Engine button
		}
		break;
	case upgradebutton::Back:
		m_buttons[0]->loseFocus();
		m_buttons[1]->loseFocus();
		m_buttons[2]->loseFocus();
		m_buttons[3]->loseFocus();
		m_backButton->getFocus();

		// Checks if the down button has been pressed
		if ((m_state.dpadDown && !m_controller.m_previousState.dpadDown) || (m_state.LeftThumbStick.y > 50 && m_controller.m_previousState.LeftThumbStick.y < 50))
		{
			m_buttonSelected = upgradebutton::Engine;	// Switches to the Engine button
		}

		// Checks if the up button has been pressed
		if ((m_state.dpadUp && !m_controller.m_previousState.dpadUp) || (m_state.LeftThumbStick.y < -50 && m_controller.m_previousState.LeftThumbStick.y > -50))
		{
			m_buttonSelected = upgradebutton::Engine;	// Switches to the Engine button
		}

	default:
		break;
	}
}

// Function to check if the selected button has been pressed
void Garage::selectedButton(GamePadState m_gamePadState, Xbox360Controller m_controller)
{
	switch (m_buttonSelected) // Switch statement for the buttons
	{
	case upgradebutton::Engine:	// The engine button 
		if (m_gamePadState.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{

		}
		break;
	case upgradebutton::Turbo:	// The turbo button
		if (m_gamePadState.A && !m_controller.m_previousState.A)
		{
			
		}
		break;
	case upgradebutton::Handling:	// The handling button 
		if (m_gamePadState.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{

		}
		break;
	case upgradebutton::Tires:	// The tires button 
		if (m_gamePadState.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{
			
		}
		break;
	case upgradebutton::Back:	// The back button
		if (m_gamePadState.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{
			*m_state = GameState::MENU_STATE;
		}
	default:
		break;
	}

}
