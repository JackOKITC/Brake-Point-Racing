#include "EndScreen.h"

EndScreen::EndScreen(sf::Font font, GameState *gameState) :
	m_gameState(gameState),
	m_font(font)
{
	m_backButton = new Button(&m_backString, &sf::Vector2f(450, 500), &m_font);
	m_view.setCenter(450, 300);
	m_view.setSize(900, 600);
	m_label = new Label(&ss.str(), &m_font, &sf::Vector2f(300, 300), 15, sf::Color(0, 255, 0));
}

EndScreen::~EndScreen() {}

void EndScreen::update(Xbox360Controller & controller, sf::Time dt, int position)
{
	m_position = position;
	checkButton(controller.m_currentState, controller);
	ss.str("");
	if (m_position == 1)
	{
		ss << "Congratulations, you came in first place";
	}
	else if (m_position == 2)
	{
		ss << "Unlucky, you came in second place";
	}
	else if (m_position == 3)
	{
		ss << "Unlucky, you came in third place";
	}

	m_label->updateText(ss);
}

void EndScreen::render(sf::RenderWindow & window)
{
	window.setView(m_view);
	m_backButton->render(window);
	m_label->render(window);
}

// Function to check if the selected button has been pressed
void EndScreen::checkButton(GamePadState m_gamePadState, Xbox360Controller m_controller)
{
	if (m_gamePadState.A && !m_controller.m_previousState.A)
	{
		*m_gameState = GameState::MENU_STATE;
	}
	
}