#include "Car.h"

Car::Car()
{
	if (!m_carTex.loadFromFile(".//resources//images//cars//Bus.png"))
	{
		std::cout << "Problem loading Texture for splash screen";
	}
	
	m_carSprite.setTexture(m_carTex);
	
	m_position = sf::Vector2f(100, 300);
	m_velocity = sf::Vector2f(0, 0);
	m_rotation = 90.0f;

	m_carSprite.setPosition(m_position);
	m_carSprite.scale(0.4, 0.4);
	m_carSprite.setRotation(90);

}

Car::~Car() {}

void Car::update(Xbox360Controller & controller, double dt)
{
	moveCar(controller);
	m_carSprite.setPosition(m_position);
	m_carSprite.setRotation(m_rotation);
	m_carSprite.setOrigin(m_carSprite.getLocalBounds().width / 2, m_carSprite.getLocalBounds().height / 2);

	sf::Vector2f newPos = sf::Vector2f(m_position.x + std::cos(DEG_TO_RAD  * (m_rotation - 90)) * m_speed * (dt / 1000),
		m_position.y + std::sin(DEG_TO_RAD * (m_rotation - 90)) * m_speed * (dt / 1000));

	m_position = newPos;
}

void Car::render(sf::RenderWindow & window)
{
	
	window.draw(m_carSprite);


}

void Car::moveCar(Xbox360Controller & controller)
{
	if (controller.m_currentState.Y)
	{
		if (m_speed < 60)
		{
			m_speed += 0.03;
		}
	}

	if (controller.m_currentState.B)
	{
		if (m_speed > -30)
		{
			m_speed -= 0.03;
		}
	}


	// Checks if the down button has been pressed
	if ((controller.m_currentState.dpadRight) || (controller.m_currentState.LeftThumbStick.x > 50))
	{
		if(((m_speed < -1 && m_speed < 0) || (m_speed > 1 && m_speed > 0)))
		m_rotation += 0.1;
	}

	// Checks if the up button has been pressed
	if ((controller.m_currentState.dpadLeft) || (controller.m_currentState.LeftThumbStick.x < -50))
	{
		if (((m_speed < -2 && m_speed < 0) || (m_speed > 2 && m_speed > 0)))
		m_rotation -= 0.1;
	}
}

