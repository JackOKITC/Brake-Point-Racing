#include "Play.h"

Play::Play(GameState *gameState)
{
	m_state = gameState;

	if (!m_backgroundTex.loadFromFile(".//resources//images//car_parts//all.png"))
	{
		std::cout << "Problem loading Texture for splash screen";
	}
	m_backgroundSprite.setTexture(m_backgroundTex);

	car = new Car();

	followPlayer.setCenter(car->m_position);
	followPlayer.setSize(900, 600); //in constructor
}

Play::~Play()
{
}

void Play::update(Xbox360Controller & controller, double dt)
{
	car->update(controller, dt);
}

void Play::render(sf::RenderWindow & window)
{
	window.draw(m_backgroundSprite);
	car->render(window);

	followPlayer.setCenter(car->m_position);
	window.setView(followPlayer);
}

