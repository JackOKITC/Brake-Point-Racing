#include "Car.h"

Car::Car()
{
}

Car::Car(sf::Texture & carTex, int brake, int handling, int acceleration)
{
	// initialising all the car variables
	m_carTex = carTex;
	m_carSprite.setTexture(m_carTex);
	m_velocity = sf::Vector2f(0, 0);
	m_deceleration = brake;
	m_handling = handling;
	m_acceleration = acceleration;
	
	// setting the car sprites' position, origin, and scale
	m_carSprite.setPosition(sf::Vector2f(450, 400));
	m_carSprite.setOrigin(m_carSprite.getLocalBounds().width / 2, m_carSprite.getLocalBounds().height / 2);
	m_carSprite.setScale(0.2, 0.2);

	// initialising each upgrade segment to be empty
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
		moveCar(controller);	// move the car based on controller input
		m_carSprite.setPosition(m_position);	// setting the car's position
		m_carSprite.setRotation(m_rotation);	// updating the car's rotation

		// updating the position based on time, speed, and rotation
		m_position = sf::Vector2f(m_position.x + std::cos(DEG_TO_RAD  * (m_rotation)) * m_speed * (dt / 1000),
								  m_position.y + std::sin(DEG_TO_RAD * (m_rotation)) * m_speed * (dt / 1000));

}

void Car::render(sf::RenderWindow & window)
{
		window.draw(m_carSprite);	// drawing the car sprite
}

void Car::moveCar(Xbox360Controller & controller)
{
	// If the right trigger is being held down.
	if (controller.m_currentState.RTrigger)
	{
		if (m_speed < MAX_FORWARD_SPEED)
		{
			m_speed += (-controller.m_currentState.triggers / 50000) * (m_acceleration);
		}
	}
	// If the right trigger is not being held down and speed is greater than .01;
	else if (!controller.m_currentState.RTrigger && m_speed > 0.01f)
	{
		m_speed -= DECCELERATION_CAUSED_BY_FRICTION;
	}

	if (controller.m_currentState.LTrigger)
	{
		if (m_speed > MAX_REVERSE_SPEED)
		{
			m_speed -= (controller.m_currentState.triggers / 100000) * (m_deceleration);
		}
	}
	// If the left trigger is being held down.
	else if (!controller.m_currentState.LTrigger && m_speed < 0)
	{
		m_speed += DECCELERATION_CAUSED_BY_FRICTION;
	}

	// Checks if the right button has been pressed
	if ((controller.m_currentState.dpadRight) || (controller.m_currentState.LeftThumbStick.x > 50))
	{
		if (m_speed < 0.1 && m_speed > 0)
		{
		}
		else if (m_speed < 5 && m_speed > 0)
		{
			m_rotation += (m_handling * 0.00133);
		}
		else if (m_speed < 10 && m_speed > 0)
		{
			m_rotation += (m_handling * 0.00115);
		}
		else if (m_speed >= 10 && m_speed > 0)
		{
			m_rotation += (m_handling * 0.009);
		}
		else if ((m_speed < 0))
		{
			m_rotation += (m_handling * 0.009);
		}

		if (m_rotation > 360)
		{
			m_rotation = 0.1f;
		}

	}

	// Checks if the left button has been pressed
	if ((controller.m_currentState.dpadLeft) || (controller.m_currentState.LeftThumbStick.x < -50))
	{
		if (m_speed < 0.1 && m_speed > 0)
		{
		}
		else if (m_speed < 5 && m_speed > 0)
		{
			m_rotation -= (m_handling * 0.00133);
		}
		else if (m_speed < 10 && m_speed > 0)
		{
			m_rotation -= (m_handling * 0.00115);
		}
		else if (m_speed >= 10 && m_speed > 0)
		{
			m_rotation -= (m_handling * 0.009);
		}
		else if ((m_speed < 0))
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
	// increases the Brakes stat if updated with this stat
	if(stat == "Brakes")
	{
		m_deceleration++;
	}

	// increases the Handling stat if updated with this stat
	if (stat == "Handling")
	{
		m_handling++;
	}

	// increases the Acceleration stat if updated with this stat
	if (stat == "Acceleration")
	{
		m_acceleration++;
	}
}

// returns m_deceleration
int Car::returnDecel()
{
	return m_deceleration;
}

// returns m_handling
int Car::returnHandle()
{
	return m_handling;
}

// returns m_acceleration
int Car::returnAcel()
{
	return m_acceleration;
}
