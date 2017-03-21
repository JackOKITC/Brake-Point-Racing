#include "Car.h"


Car::Car()
{
		m_position = sf::Vector2f(100, 300);
		m_velocity = sf::Vector2f(0, 0);
		m_rotation = 45.0f;

		m_carSprite.setPosition(m_position);
		m_carSprite.scale(0.2, 0.2);

		m_carSprite.setRotation(m_rotation);

		m_carSprite.setOrigin(m_carSprite.getLocalBounds().width / 2, m_carSprite.getLocalBounds().height / 2);
}


Car::~Car() 
{
}

void Car::update(Xbox360Controller & controller, double dt)
{
		moveCar(controller);
		m_nodePlacement.setPosition(m_position);
		m_nodePlacement.setRotation(m_rotation);
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
			m_speed += -controller.m_currentState.triggers / 4000;
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
		if (((m_speed > -1 && m_speed < 0) || (m_speed < 1 && m_speed > 0)))
		{
		}
		else if (((m_speed > -5 && m_speed < 0) || (m_speed < 5 && m_speed > 0)))
		{
			m_rotation += 0.01;
		}
		else if (m_speed < 10 && m_speed > 0)
		{
			m_rotation += 0.075;
		}
		else if (m_speed >= 10 && m_speed > 0)
		{
			m_rotation += 0.15;
		}
		//m_rotation += 0.15;
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
			m_rotation -= 0.01;
		}
		else if (m_speed < 10 && m_speed > 0)
		{
			m_rotation -= 0.075;
		}
		else if (m_speed >= 10 && m_speed > 0)
		{
			m_rotation -= 0.15;
		}

		//m_rotation -= 0.15;

		if (m_rotation < 0)
		{
			m_rotation = 359.0f;
		}
	}

	if (controller.m_currentState.A && !controller.m_previousState.A)
	{
		m_nodePlacementNumber++;
		std::cout << "   - number: " << m_nodePlacementNumber << std::endl;
		std::cout << "     position: {x: " << m_position.x << ", y: " << m_position.y << "}" << std::endl;
		std::cout << "     rotation: " << m_rotation << std::endl;
	}
	

	if (m_carSprite.getGlobalBounds().intersects(m_checkpointRectangles.at(m_currentCheckpoint).getGlobalBounds()))
	{
		m_currentCheckpoint++;
		std::cout << m_currentCheckpoint << std::endl;

		if (m_currentCheckpoint >= m_checkpoints.size())
		{
			m_currentCheckpoint = 0;
			if (m_lap < MAX_LAPS)
			{
				m_lap++;
			}
			else if (m_lap = MAX_LAPS)
			{
				//finished the race.
			}
		}
	}
}

void Car::slowCar(bool slow)
{
	if (slow && m_speed > 5)
	{
		m_speed--;
	}
}