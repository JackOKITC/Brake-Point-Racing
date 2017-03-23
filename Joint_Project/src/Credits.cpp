#include "Credits.h"

Credits::Credits(sf::Font & font, GameState *gameState) :
	m_font(font) ,
	m_gameState(gameState)
{
	if (!m_movie.openFromFile(".\\resources\\movie\\Animation.mov"))
	{
		std::cout << "Error loading movie" << std::endl;
	}
	m_movie.setScale(1.0, 1.1);
	m_string = "Press B to go back!";
	m_label = new Label(&m_string, &m_font, &sf::Vector2f(450, 500), 50, sf::Color(140, 80, 160));
}

Credits::~Credits() {}

void Credits::update(Xbox360Controller & controller, sf::Time dt)
{
	m_movie.play();
	m_movie.update();

	if (controller.m_currentState.B && !controller.m_previousState.B)
	{
		*m_gameState = GameState::MENU_STATE;
	}
}

void Credits::render(sf::RenderWindow & window)
{
	window.draw(m_movie);
	m_label->render(window);
}