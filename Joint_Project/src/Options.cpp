#include "Options.h"


Options::Options(sf::Font font, GameState *gameState) :
	m_font(font)
{
	m_sliderValue = 5;
	m_button = new Button(&m_string, &sf::Vector2f(450, 200), &m_font);
	m_slider = new Slider(&sf::Vector2f(380, 300), m_sliderValue);

	widgets[0] = m_button;
	widgets[1] = m_slider;

	widgets[0]->getFocus();
	widgets[1]->loseFocus();
}

Options::~Options()
{
}

void Options::update(GamePadState m_state, Xbox360Controller & m_controller)
{
	m_slider->update();
	checkButtonSelected(m_state, m_controller);
	selectedButton(m_state, m_controller);
}

void Options::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::White);
	m_button->render(window);
	m_slider->render(window);
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
			m_buttonSelected = (optionsButton)m_currentBtn; // enum for buttons set to current int value of current button
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
			m_buttonSelected = (optionsButton)m_currentBtn;
		}

		// if the currently selected button is the slider button before these actions only of left and right pressed
		if (m_buttonSelected == optionsButton::Option2)
		{
			if ((m_state.dpadLeft && !m_controller.m_previousState.dpadLeft) || (m_state.LeftThumbStick.x < -50 && m_controller.m_previousState.LeftThumbStick.x > -50))	// Decrements the slider if the player pushes the d-pad or thumbstick left.
			{
				m_sliderValue = m_slider->decrementSlider();
			}

			if ((m_state.dpadRight && !m_controller.m_previousState.dpadRight) || (m_state.LeftThumbStick.x > 50 && m_controller.m_previousState.LeftThumbStick.x < 50))	// Increments the slider if the player pushes the d - pad or thumbstick left.
			{
				m_sliderValue = m_slider->incrementSlider();
			}
		}
}

// Function to check if the selected button has been pressed
void Options::selectedButton(GamePadState m_state, Xbox360Controller m_controller)
{
	switch (m_buttonSelected) // Switch statement for the buttons
	{
	case optionsButton::Option1:	// The play button 
		if (m_state.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{

		}
		break;
	case optionsButton::Option2:	// The options button 
		if (m_state.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{

		}
		break;
	case optionsButton::Option3:	// The exit button 
		if (m_state.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{
			
		}
		break;
	default:
		break;
	}
}