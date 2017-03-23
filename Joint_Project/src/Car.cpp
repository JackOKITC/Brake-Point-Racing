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

	m_carSprite.setOrigin(m_carSprite.getLocalBounds().width / 2, m_carSprite.getLocalBounds().height / 2);
	m_carSprite.setScale(0.2, 0.2);

	for (int i = 0; i < 3; i++)
	{
		m_upgradeLevels[i] = 0;
	}
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
	if (controller.m_currentState.A && !controller.m_previousState.A)
	{
		std::cout << "Handling: " << m_handling << std::endl;
		std::cout << "Braking: " << m_deceleration << std::endl;
		std::cout << "Acceleration: " << m_acceleration << std::endl;
	}

	if (controller.m_currentState.RTrigger)
	{
		if (m_speed < MAX_FORWARD_SPEED)
		{
			m_speed += (-controller.m_currentState.triggers / 5000) * (m_acceleration + 1);
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
			m_speed -= (controller.m_currentState.triggers / 10000) * (m_deceleration + 1);
		}
	}
	else if (!controller.m_currentState.LTrigger && m_speed < 0)
	{
		m_speed += DECCELERATION_CAUSED_BY_FRICTION;
	}

	// Checks if the down button has been pressed
	if ((controller.m_currentState.dpadRight) || (controller.m_currentState.LeftThumbStick.x > 50))
	{
		if ((m_speed > -1 && m_speed < 0) || (m_speed < 1 && m_speed > 0))
		{
		}
		else if ((m_speed > -5 && m_speed < 0) || (m_speed < 5 && m_speed > 0))
		{
			m_rotation += (m_handling * 0.0133);
		}
		else if ((m_speed > -10 && m_speed < 0) || (m_speed < 10 && m_speed > 0))
		{
			m_rotation += (m_handling * 0.0011);
		}
		else if ((m_speed <= -10 && m_speed < 0) || (m_speed >= 10 && m_speed > 0))
		{
			m_rotation += (m_handling * 0.009);
		}

		if (m_rotation > 360)
		{
			m_rotation = 0.1f;
		}

	}

	// Checks if the up button has been pressed
	if ((controller.m_currentState.dpadLeft) || (controller.m_currentState.LeftThumbStick.x < -50))
	{
		if ((m_speed > -1 && m_speed < 0) || (m_speed < 1 && m_speed > 0))
		{
		}
		else if ((m_speed > -5 && m_speed < 0) || (m_speed < 5 && m_speed > 0))
		{
			m_rotation -= (m_handling * 0.0133);
		}
		else if ((m_speed > -10 && m_speed < 0) || (m_speed < 10 && m_speed > 0))
		{
			m_rotation -= (m_handling * 0.0011);
		}
		else if ((m_speed <= -10 && m_speed < 0) || (m_speed >= 10 && m_speed > 0))
		{
			m_rotation -= (m_handling * 0.009);
		}

		if (m_rotation < 0)
		{
			m_rotation = 359.9f;
		}
	}
}

void Car::slowCar(bool slow)
{
	if (slow && m_speed > 5)
	{
		m_speed -= 0.1f;
	}
	else if (slow && m_speed < -2.5)
	{
		m_speed += 0.1f;
	}
}

void Car::updateStat(std::string stat)
{
	if(stat == "Brakes")
	{
		m_deceleration++;
	}

	if (stat == "Handling")
	{
		m_handling++;
	}

	if (stat == "Acceleration")
	{
		m_acceleration++;
	}
}

int Car::returnDecel()
{
	return m_deceleration;
}

int Car::returnHandle()
{
	return m_handling;
}

int Car::returnAcel()
{
	return m_acceleration;
}
