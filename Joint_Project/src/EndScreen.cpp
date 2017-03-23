#include "EndScreen.h"

EndScreen::EndScreen(sf::Font font, GameState *gameState) :
	m_gameState(gameState),
	m_font(font)
{
	m_backButton = new Button(&m_backString, &sf::Vector2f(450, 500), &m_font);	// constructs the back button
	m_view.setCenter(450, 300);	// initialises the view's centre
	m_view.setSize(900, 600);	// initialises the view's size
	m_label = new Label(&ss.str(), &m_font, &sf::Vector2f(300, 300), 15, sf::Color(0, 255, 0));	// constructs the label
}

EndScreen::~EndScreen() {}

void EndScreen::update(Xbox360Controller & controller, sf::Time dt, int position)
{
	m_position = position;	// initialising and updating position
	checkButton(controller.m_currentState, controller);	// checking which button is in use
	ss.str("");	// setting the stringstream to be empty
	if (m_position == 1)
	{
		ss << "Congratulations, you came in first place";	// setting the stringstream to be this if you came first
	}
	else if (m_position == 2)
	{
		ss << "Unlucky, you came in second place";	// setting the stringstream to be this if you came second
	}
	else if (m_position == 3)
	{
		ss << "Unlucky, you came in third place";	// setting the stringstream to be this if you came third
	}

	m_label->updateText(ss);	// updates the label given the stringstream
}

void EndScreen::render(sf::RenderWindow & window)
{
	window.setView(m_view);	// sets the view to the chosen view
	m_backButton->render(window);	// rendering back button
	m_label->render(window);	// rendering the label
}

// Function to check if the selected button has been pressed
void EndScreen::checkButton(GamePadState m_gamePadState, Xbox360Controller m_controller)
{
	if (m_gamePadState.A && !m_controller.m_previousState.A)
	{
		*m_gameState = GameState::MENU_STATE;
	}
	
}