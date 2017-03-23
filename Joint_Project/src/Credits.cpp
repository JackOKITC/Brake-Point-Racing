#include "Credits.h"

Credits::Credits(sf::Font & font, GameState *gameState) :
	m_font(font) ,
	m_gameState(gameState)
{
	if (!m_movie.openFromFile(".\\resources\\movie\\Animation.mov"))	// couts an error if the movie can't be loaded
	{
		std::cout << "Error loading movie" << std::endl;
	}
	m_movie.setScale(1.0, 1.1);	// sets the scale so it can fit the screen
	m_string = "Press B to go back!";	// a string telling the player they can leave the screen
	m_label = new Label(&m_string, &m_font, &sf::Vector2f(450, 500), 50, sf::Color(140, 80, 160));	// the label that holds the string to display on screen
}

Credits::~Credits() {}

void Credits::update(Xbox360Controller & controller, sf::Time dt)
{
	m_movie.play();	// Tells the movie to play
	m_movie.update();	// updates the movie

	// if statement returning the player to the menu if they press B
	if (controller.m_currentState.B && !controller.m_previousState.B)
	{
		*m_gameState = GameState::MENU_STATE;
	}
}

void Credits::render(sf::RenderWindow & window)
{
	window.draw(m_movie);	// draws the movie
	m_label->render(window);	// renders the label
}