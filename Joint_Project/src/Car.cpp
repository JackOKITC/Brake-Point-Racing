#include "Car.h"

Car::Car(bool isAi, std::vector<std::unique_ptr<Node>> & nodes) :
	m_isAi(isAi),
	m_nodes(nodes)
{
	if (!m_isAi)
	{
		m_carTex = g_manager.m_holder["BusTex"];
		m_carSprite.setTexture(m_carTex);

		m_position = sf::Vector2f(100, 300);
		m_velocity = sf::Vector2f(0, 0);
		m_rotation = 90.0f;

		m_carSprite.setPosition(m_position);
		m_carSprite.scale(0.4, 0.4);
		m_carSprite.setRotation(m_rotation);

		m_carSprite.setOrigin(m_carSprite.getLocalBounds().width / 2, m_carSprite.getLocalBounds().height / 2);
	}
	else
	{
		m_aiCar = new Ai(m_nodes);
	}
}

Car::~Car() 
{
}

void Car::update(Xbox360Controller & controller, double dt)
{
	if (!m_isAi)
	{
		moveCar(controller);

		m_carSprite.setPosition(m_position);
		m_carSprite.setRotation(m_rotation);

		sf::Vector2f newPos = sf::Vector2f(m_position.x + std::cos(DEG_TO_RAD  * (m_rotation - 90)) * m_speed * (dt / 1000),
			m_position.y + std::sin(DEG_TO_RAD * (m_rotation - 90)) * m_speed * (dt / 1000));

		m_position = newPos;
	}
	else
	{
		m_aiCar->update(dt);
	}
}

void Car::render(sf::RenderWindow & window)
{
	if (!m_isAi)
	{
		window.draw(m_carSprite);
	}
	else
	{
		m_aiCar->render(window);
	}
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