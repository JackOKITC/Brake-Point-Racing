#include "Car.h"

Car::Car()
{
}

Car::Car(sf::Texture & carTex, int brake, int handling, int acceleration)
{
	m_carTex = carTex;
	m_carSprite.setTexture(m_carTex);
	m_velocity = sf::Vector2f(0, 0);
	m_deceleration = brake;
	m_handling = handling;
	m_acceleration = acceleration;
	m_carSprite.setPosition(sf::Vector2f(450, 400));

	m_carSprite.setOrigin(m_carSprite.getLocalBounds().width / 3, m_carSprite.getLocalBounds().height / 2);
	m_carSprite.setScale(.25, .25);
}

Car::~Car() 
{
}

void Car::update(Xbox360Controller & controller, double dt)
{
		moveCar(controller);
		m_carSprite.setPosition(m_position);
		m_carSprite.setRotation(m_rotation);

		m_position = sf::Vector2f(m_position.x + std::cos(DEG_TO_RAD  * (m_rotation)) * m_speed * (dt / 1000),
								  m_position.y + std::sin(DEG_TO_RAD * (m_rotation)) * m_speed * (dt / 1000));
}

void Car::render(sf::RenderWindow & window)
{
		window.draw(m_carSprite);
}

void Car::moveCar(Xbox360Controller & controller)
{
	if (controller.m_currentState.RTrigger)
	{
		if (m_speed < MAX_FORWARD_SPEED)
		{
			m_speed += -controller.m_currentState.triggers / 5000;
		}
	}
	else if (!controller.m_currentState.RTrigger && m_speed > 0.01f)
	{
		m_speed -= DECCELERATION_CAUSED_BY_FRICTION;
	}

	if (controller.m_currentState.LTrigger)
	{
		if (m_speed > MAX_REVERSE_SPEED)
		{
			m_speed -= controller.m_currentState.triggers / 10000;;
		}
	}
	else if (!controller.m_currentState.LTrigger && m_speed < 0)
	{
		m_speed += DECCELERATION_CAUSED_BY_FRICTION;
	}

	// Checks if the down button has been pressed
	if ((controller.m_currentState.dpadRight) || (controller.m_currentState.LeftThumbStick.x > 50))
	{
		if (((m_speed > -1 && m_speed < 0) || (m_speed < 1 && m_speed > 0)))
		{
		}
		else if (((m_speed > -5 && m_speed < 0) || (m_speed < 5 && m_speed > 0)))
		{
			m_rotation += 0.1;
		}
		else if (m_speed < 10 && m_speed > 0)
		{
			m_rotation += 0.08;
		}
		else if (m_speed >= 10 && m_speed > 0)
		{
			m_rotation += 0.06;
		}

		if (m_rotation > 360)
		{
			m_rotation = 1.0f;
		}

	}

	// Checks if the up button has been pressed
	if ((controller.m_currentState.dpadLeft) || (controller.m_currentState.LeftThumbStick.x < -50))
	{
		if (((m_speed > -1 && m_speed < 0) || (m_speed < 1 && m_speed > 0)))
		{
		}
		else if (((m_speed > -5 && m_speed < 0) || (m_speed < 5 && m_speed > 0)))
		{
			m_rotation -= 0.1;
		}
		else if (m_speed < 10 && m_speed > 0)
		{
			m_rotation -= 0.08;
		}
		else if (m_speed >= 10 && m_speed > 0)
		{
			m_rotation -= 0.06;
		}

		if (m_rotation < 0)
		{
			m_rotation = 359.0f;
		}
	}
}

void Car::slowCar(bool slow)
{
	if (slow && m_speed > 5)
	{
		m_speed -= 0.25;
	}
}

void Car::initCar()
{
	m_rotation = 45;
	m_velocity = sf::Vector2f(0, 0);
}