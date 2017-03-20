#include "Car.h"

Car::Car(bool isAi, std::vector<std::unique_ptr<Node>> & nodes, std::vector<std::unique_ptr<Checkpoint>> &checkpoints) :
	m_isAi(isAi),
	m_nodes(nodes),
	m_checkpoints(checkpoints)
{
	if (!m_isAi)
	{

		m_carTex = ResourceManager::instance().m_holder["BusTex"];
		m_carSprite.setTexture(m_carTex);

		m_position = sf::Vector2f(2145, 850);
		m_velocity = sf::Vector2f(0, 0);
		m_rotation = 45.0f;

		m_carSprite.setPosition(m_position);
		m_carSprite.scale(0.2, 0.2);

		m_carSprite.setRotation(m_rotation);

		m_carSprite.setOrigin(m_carSprite.getLocalBounds().width / 2, m_carSprite.getLocalBounds().height / 2);

		for (int i = 0; i < m_checkpoints.size(); i++)
		{
			sf::RectangleShape rectangle;
			m_checkpointRectangles.push_back(std::move(rectangle));
			m_checkpointRectangles.at(i).setOrigin(CHECKPOINT_TOLERANCE / 2, CHECKPOINT_TOLERANCE / 2);
			m_checkpointRectangles.at(i).setPosition(m_checkpoints.at(i)->m_position.x - CHECKPOINT_TOLERANCE / 2, m_checkpoints.at(i)->m_position.y - CHECKPOINT_TOLERANCE / 2);
			m_checkpointRectangles.at(i).setSize(sf::Vector2f(CHECKPOINT_TOLERANCE, CHECKPOINT_TOLERANCE));
			m_checkpointRectangles.at(i).setFillColor(sf::Color(255, 0, 0, 126));
		}
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


		sf::Vector2f newPos = sf::Vector2f(m_position.x + std::cos(DEG_TO_RAD  * (m_rotation)) * m_speed * (dt / 1000),
										   m_position.y + std::sin(DEG_TO_RAD * (m_rotation)) * m_speed * (dt / 1000));


		m_position = newPos;
		//std::cout << "Player Position = x : " << m_position.x << " y : " << m_position.y << std::endl;
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
		
		for (int i = 0; i < m_checkpointRectangles.size(); i++)
		{
			window.draw(m_checkpointRectangles.at(i));
		}
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
		if (m_speed < MAX_FORWARD_SPEED)
		{
			m_speed += -controller.m_currentState.triggers / 4000;
		}
	}
	else if (!controller.m_currentState.RTrigger && m_speed > 0.01f)
	{
		m_speed -= DECCELERATION_CAUSED_BY_FRICTION;
	}
	else
	{
		m_speed = 0;
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
		if (m_speed == 0)
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
	}

	// Checks if the up button has been pressed
	if ((controller.m_currentState.dpadLeft) || (controller.m_currentState.LeftThumbStick.x < -50))
	{
		if (m_speed == 0)
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
	}
	

	sf::Vector2f dist;
	dist = m_checkpoints.at(m_currentCheckpoint)->m_position - m_position;

	if ((dist.x < CHECKPOINT_TOLERANCE && dist.y < CHECKPOINT_TOLERANCE) && (dist.x > -CHECKPOINT_TOLERANCE && dist.y > -CHECKPOINT_TOLERANCE))
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