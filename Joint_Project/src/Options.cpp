#include "Options.h"


Options::Options(sf::Font font, GameState *gameState) :
	m_font(font)
{
	m_radioTex = ResourceManager::instance().m_holder["Radio"];
	
	m_gameState = gameState;

	m_volDif = 20;
	m_volume = vol.getVolume();

	m_sliderValue = 5;
	m_helpButton = new Button(&m_helpString, &sf::Vector2f(450, 200), &m_font);
	m_volSlider = new Slider(&sf::Vector2f(380, 300), m_sliderValue);
	m_screenRadio = new RadioButton(&m_radioTex, &sf::Vector2f(450, 400));
	m_exitButton = new Button(&m_exitString, &sf::Vector2f(450, 500), &m_font);

	widgets[0] = m_helpButton;
	widgets[1] = m_volSlider;
	widgets[2] = m_screenRadio;
	widgets[3] = m_exitButton;

	widgets[0]->getFocus();
	widgets[1]->loseFocus();
	widgets[2]->loseFocus();
	widgets[3]->loseFocus();
}

Options::~Options()
{
}

void Options::update(GamePadState m_state, Xbox360Controller & m_controller)
{
	m_volSlider->update();
	checkButtonSelected(m_state, m_controller);
	selectedButton(m_state, m_controller);
}

void Options::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::White);
	m_helpButton->render(window);
	m_volSlider->render(window);
	m_screenRadio->render(window);
	m_exitButton->render(window);
}

// Function to check which button is selected
void Options::checkButtonSelected(GamePadState m_state, Xbox360Controller m_controller)
{
		// if Down toggled
		if ((m_state.dpadDown && !m_controller.m_previousState.dpadDown) || (m_state.LeftThumbStick.y > 50 && m_controller.m_previousState.LeftThumbStick.y < 50))
		{
			widgets[m_currentBtn]->loseFocus(); // currently selected button loses focus, unhighlighted
			m_currentBtn = m_currentBtn + 1; // currentBtn selected incremented
			if (m_currentBtn > BUTTON_COUNT - 1)
			{
				m_currentBtn = m_currentBtn - 1; // safe guard to stop out of bound behaviour
			}

			widgets[m_currentBtn]->getFocus(); // newly seleted button highlighted
			m_buttonSelected = (optionsSelection)m_currentBtn; // enum for buttons set to current int value of current button
		}

		// if Up toggled, same behaviour as above except the counter is decremented
		if ((m_state.dpadUp && !m_controller.m_previousState.dpadUp) || (m_state.LeftThumbStick.y < -50 && m_controller.m_previousState.LeftThumbStick.y > -50))
		{
			widgets[m_currentBtn]->loseFocus();
			m_currentBtn = m_currentBtn - 1;
			if (m_currentBtn < 0)
			{
				m_currentBtn = 0;
			}

			widgets[m_currentBtn]->getFocus();
			m_buttonSelected = (optionsSelection)m_currentBtn;
		}

		// if the currently selected button is the slider button before these actions only of left and right pressed
		if (m_buttonSelected == optionsSelection::Option2)
		{
			if ((m_state.dpadLeft && !m_controller.m_previousState.dpadLeft) || (m_state.LeftThumbStick.x < -50 && m_controller.m_previousState.LeftThumbStick.x > -50))	// Decrements the slider if the player pushes the d-pad or thumbstick left.
			{
				m_sliderValue = m_volSlider->decrementSlider();

				if (m_volume != 0)
				{
					vol.setVolume(m_volume -= m_volDif);
				}

				std::cout << m_volume;
			}

			if ((m_state.dpadRight && !m_controller.m_previousState.dpadRight) || (m_state.LeftThumbStick.x > 50 && m_controller.m_previousState.LeftThumbStick.x < 50))	// Increments the slider if the player pushes the d - pad or thumbstick left.
			{
				m_sliderValue = m_volSlider->incrementSlider();

				if (m_volume != 100)
				{
					vol.setVolume(m_volume += m_volDif);
				}

				std::cout << m_volume;
			}
		}
}

// Function to check if the selected button has been pressed
void Options::selectedButton(GamePadState m_state, Xbox360Controller m_controller)
{
	switch (m_buttonSelected) // Switch statement for the buttons
	{
	case optionsSelection::Option1:	// The help button 
		if (m_state.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{

		}
		break;
	case optionsSelection::Option2:	// The volume slider 
		if (m_state.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{

		}
		break;
	case optionsSelection::Option3:	// The mute button 
		if (m_state.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{

		}
		break;
	case optionsSelection::Option4:	// The exit button 
		if (m_state.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{
			*m_gameState = GameState::MENU_STATE;
		}
		break;
	default:
		break;
	}
}