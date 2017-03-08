#include <Garage.h>

Garage::Garage(sf::Font font, GameState * gameState) :
	m_font(font)
{
	m_gameState = gameState;
	if (!m_backgroundTex.loadFromFile(".//resources//images//car_parts//all.png"))
	{
		std::cout << "Problem loading Texture for splash screen";
	}
	m_backgroundSprite.setTexture(m_backgroundTex);
	m_backgroundSprite.setOrigin(m_backgroundTex.getSize().x / 2, m_backgroundTex.getSize().y / 2);
	m_backgroundSprite.setPosition(450, 300);
	m_currentBtn = 0;

	for (int i = 0; i < BUTTON_COUNT; i++)
	{
		m_buttons[i] = new Button(&m_strings[i], &sf::Vector2f(150 + (i * 200), 400 ), &m_font);
		m_buttons[i]->loseFocus();
	}

	m_backButton = new Button(&m_backString, &sf::Vector2f(450, 500), &m_font);

	m_backButton->loseFocus(); // unhighlight the back button
	m_buttons[m_currentBtn]->getFocus(); // sets the first button to be highlighted
}

Garage::~Garage()
{
}

void Garage::update(Xbox360Controller & controller, sf::Time dt)
{
	checkButtonSelected(controller.m_currentState, controller);
	selectedButton(controller.m_currentState, controller);
}

void Garage::render(sf::RenderWindow &window)
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
	//if the currently selected button is not the back button run this series of code
	if (m_buttonSelected != (upgradebutton)4)
	{
		// if left toggled
		if ((m_state.dpadLeft && !m_controller.m_previousState.dpadLeft) || (m_state.LeftThumbStick.x > 50 && m_controller.m_previousState.LeftThumbStick.x < 50))
		{
			m_buttons[m_currentBtn]->loseFocus(); // currently selected button loses focus, unhighlighted
			m_currentBtn = m_currentBtn + 1; // currentBtn selected incremented
			if (m_currentBtn > BUTTON_COUNT - 1)
			{
				m_currentBtn = m_currentBtn - 1; // safe guard to stop out of bound behaviour
			}

			m_buttons[m_currentBtn]->getFocus(); // newly seleted button highlighted
			m_buttonSelected = (upgradebutton)m_currentBtn; // enum for buttons set to current int value of current button
		}

		// if right toggled, same behaviour as above except the counter is decremented
		if ((m_state.dpadRight && !m_controller.m_previousState.dpadRight) || (m_state.LeftThumbStick.x < -50 && m_controller.m_previousState.LeftThumbStick.x > -50))
		{
			m_buttons[m_currentBtn]->loseFocus();
			m_currentBtn = m_currentBtn - 1;
			if (m_currentBtn < 0)
			{
				m_currentBtn = 0;
			}

			m_buttons[m_currentBtn]->getFocus();
			m_buttonSelected = (upgradebutton)m_currentBtn;
		}

		// if down is pressed, keep track of current row of buttons selection and move to the back button
		if ((m_state.dpadDown && !m_controller.m_previousState.dpadDown) || (m_state.LeftThumbStick.y > 50 && m_controller.m_previousState.LeftThumbStick.y < 50))
		{
			m_buttonSelected = (upgradebutton)4;
			m_buttons[m_currentBtn]->loseFocus();
			m_backButton->getFocus();
		}
	}

	// if back is selected and up toggled return to the button row
	if (m_buttonSelected == (upgradebutton)4)
	{
		if ((m_state.dpadUp && !m_controller.m_previousState.dpadUp) || (m_state.LeftThumbStick.y < -50 && m_controller.m_previousState.LeftThumbStick.y > -50))
		{
			m_buttonSelected = (upgradebutton)m_currentBtn;
			m_buttons[m_currentBtn]->getFocus();
			m_backButton->loseFocus();
		}
	}
}

// Function to check if the selected button has been pressed
void Garage::selectedButton(GamePadState m_state, Xbox360Controller m_controller)
{
	switch (m_buttonSelected) // Switch statement for the buttons
	{
	case upgradebutton::Engine:	// The engine button 
		if (m_state.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{

		}
		break;
	case upgradebutton::Turbo:	// The turbo button
		if (m_state.A && !m_controller.m_previousState.A)
		{
			
		}
		break;
	case upgradebutton::Handling:	// The handling button 
		if (m_state.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{

		}
		break;
	case upgradebutton::Tires:	// The tires button 
		if (m_state.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{
			
		}
		break;
	case upgradebutton::Back:	// The back button
		if (m_state.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{
			*m_gameState = GameState::MENU_STATE;
		}
	default:
		break;
	}

}
