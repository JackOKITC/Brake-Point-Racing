#include "Options.h"


Options::Options(sf::Font font, GameState *gameState, sf::Sound &music) :
	m_font(font)
{
	m_radioTex = ResourceManager::instance().m_holder["Radio"];	// initialises the radio texture to be Radio from the yaml file

	m_gameState = gameState;	// initialising the gamestate object

	m_volDif = 25;	// initialised the slider difference variable
	m_volume = music.getVolume();	// initialises volume to get the current musics volume (defaulted to 100)

	// initialising all the slider variables and the individual widget objects
	m_sliderValue = 5;
	m_volSlider = new Slider(&sf::Vector2f(380, 150), m_sliderValue);
	m_volSlider->setCurrentSegment(m_sliderValue - 1);
	m_screenRadio = new RadioButton(&m_radioTex, &sf::Vector2f(450, 300));
	m_exitButton = new Button(&m_exitString, &sf::Vector2f(450, 450), &m_font);
	m_muteLabel = new Label(&m_muteString, &m_font, &sf::Vector2f(350, 297), 20, sf::Color(140, 80, 160));
	m_volLabel = new Label(&m_volString, &m_font, &sf::Vector2f(280, 155), 20, sf::Color(140, 80, 160));

	// assigning each widget object to the array of widgets
	widgets[0] = m_volSlider;
	widgets[1] = m_screenRadio;
	widgets[2] = m_exitButton;
	widgets[3] = m_volLabel;
	widgets[4] = m_muteLabel;

	// defaulting focus on the first element of the array
	widgets[0]->getFocus();
	widgets[1]->loseFocus();
	widgets[2]->loseFocus();
	widgets[3]->loseFocus();
	widgets[4]->loseFocus();
}

Options::~Options()
{
}

void Options::update(GamePadState m_state, Xbox360Controller & m_controller, sf::Sound &music)
{
	m_volSlider->update();	// updates the volume slider
	checkButtonSelected(m_state, m_controller, music);	// checks which button is selected
	selectedButton(m_state, m_controller, music);	// selects the button
}

void Options::render(sf::RenderWindow & window)
{
	window.clear(sf::Color(30, 50, 90));	// sets the window to our preferred colour, royal blue
	
	// rendering each widget object
	m_volSlider->render(window);
	m_screenRadio->render(window);
	m_exitButton->render(window);
	m_muteLabel->render(window);
	m_volLabel->render(window);
}

// Function to check which button is selected
void Options::checkButtonSelected(GamePadState m_state, Xbox360Controller m_controller, sf::Sound & music)
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
	if (m_buttonSelected == optionsSelection::Option1)
	{
		if ((m_state.dpadLeft && !m_controller.m_previousState.dpadLeft) || (m_state.LeftThumbStick.x < -50 && m_controller.m_previousState.LeftThumbStick.x > -50))	// Decrements the slider if the player pushes the d-pad or thumbstick left.
		{
			m_sliderValue = m_volSlider->decrementSlider();

			if (m_volume != 0)
			{
				music.setVolume(m_volume -= m_volDif);
			}
		}

		if ((m_state.dpadRight && !m_controller.m_previousState.dpadRight) || (m_state.LeftThumbStick.x > 50 && m_controller.m_previousState.LeftThumbStick.x < 50))	// Increments the slider if the player pushes the d - pad or thumbstick left.
		{
			m_sliderValue = m_volSlider->incrementSlider();

			if (m_volume != 100)
			{
				music.setVolume(m_volume += m_volDif);
			}
		}
	}
}

// Function to check if the selected button has been pressed
void Options::selectedButton(GamePadState m_state, Xbox360Controller m_controller, sf::Sound &music)
{
	switch (m_buttonSelected) // Switch statement for the buttons
	{
	case optionsSelection::Option2:	// The mute button 
		if (m_state.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{
			music.setVolume(0);
		}
		break;
	case optionsSelection::Option3:	// The back button 
		if (m_state.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{
			*m_gameState = GameState::MENU_STATE;
		}
		break;
	default:
		break;
	}
}