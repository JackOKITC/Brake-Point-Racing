#include "Car.h"

Car::Car()
{
	m_carTex = ResourceManager::instance().m_holder["BusTex"];

	m_carSprite.setTexture(m_carTex);
	
	m_position = sf::Vector2f(100, 100);
	m_velocity = sf::Vector2f(0, 0);
	m_rotation = 90.0f;

	m_carSprite.setPosition(m_position);
	m_carSprite.scale(0.2, 0.2);
	m_carSprite.setRotation(m_rotation);

	m_carSprite.setOrigin(m_carSprite.getLocalBounds().width / 2, m_carSprite.getLocalBounds().height / 2);
}

Car::~Car() {}

void Car::update(Xbox360Controller & controller, double dt)
{
	moveCar(controller);
	
	m_carSprite.setPosition(m_position);
	m_carSprite.setRotation(m_rotation);
	

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
	if (controller.m_currentState.RTrigger)
	{
		if (m_speed < 40)
		{
			m_speed += -controller.m_currentState.triggers / 4000;
		}
	}
	else if (!controller.m_currentState.RTrigger && m_speed > 0)
	{
		m_speed -= DECCELERATION_CAUSED_BY_FRICTION;
	}

	if (controller.m_currentState.LTrigger)
	{
		if (m_speed > -20)
		{
			m_speed -= controller.m_currentState.triggers / 5000;;
		}
	}
	else if (!controller.m_currentState.LTrigger && m_speed < 0)
	{
		m_speed += DECCELERATION_CAUSED_BY_FRICTION;
	}

	std::cout << m_speed << std::endl;

	//if (m_speed > 5 && (m_carSprite.getOrigin().y != m_carSprite.getLocalBounds().height - 10))
	//{
	//	m_carSprite.setOrigin(m_carSprite.getLocalBounds().width / 2, m_carSprite.getOrigin().y + 0.1);
	//}
	//else if (m_speed < 5 && (m_carSprite.getOrigin().y != 10))
	//{
	//	m_carSprite.setOrigin(m_carSprite.getLocalBounds().width / 2, m_carSprite.getOrigin().y - 0.1);
	//}

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