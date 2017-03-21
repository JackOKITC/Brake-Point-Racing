#include "Car.h"


Car::Car(bool isAi, std::vector<std::unique_ptr<Node>> & nodes, std::vector<std::unique_ptr<Checkpoint>> &checkpoints, sf::Vector2f & position) :
	m_isAi(isAi),
	m_nodes(nodes),
	m_checkpoints(checkpoints),
	m_position(position)
{
	if (!m_isAi)
	{
		m_carTex = ResourceManager::instance().m_holder["Bus0"];
		m_carSprite.setTexture(m_carTex);
		m_velocity = sf::Vector2f(0, 0);
		m_rotation = 45.0f;

		m_carSprite.setPosition(m_position);
		m_carSprite.scale(0.2, 0.2);

		m_carSprite.setRotation(m_rotation);

		m_carSprite.setOrigin(m_carSprite.getLocalBounds().width / 2, m_carSprite.getLocalBounds().height / 2);

		m_nodePlacement.setSize(sf::Vector2f(10.0f, 120.0f));
		m_nodePlacement.setOrigin(5, 60);
		m_nodePlacement.setFillColor(sf::Color(255, 0, 0, 126));

		for (int i = 0; i < m_checkpoints.size(); i++)
		{
			sf::RectangleShape rectangle;
			m_checkpointRectangles.push_back(std::move(rectangle));
			m_checkpointRectangles.at(i).setOrigin(CHECKPOINT_WIDTH / 2, CHECKPOINT_HEIGHT / 2);
			m_checkpointRectangles.at(i).setPosition(m_checkpoints.at(i)->m_position.x, m_checkpoints.at(i)->m_position.y);
			m_checkpointRectangles.at(i).setRotation(m_checkpoints.at(i)->m_rotation);
			m_checkpointRectangles.at(i).setSize(sf::Vector2f(CHECKPOINT_WIDTH, CHECKPOINT_HEIGHT));
			m_checkpointRectangles.at(i).setFillColor(sf::Color(255, 0, 0, 126));
		}
	}
	else
	{
		m_aiCar = new Ai(m_nodes, m_position);
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
		m_nodePlacement.setPosition(m_position);
		m_nodePlacement.setRotation(m_rotation);
		m_carSprite.setPosition(m_position);
		m_carSprite.setRotation(m_rotation);


		m_position = sf::Vector2f(m_position.x + std::cos(DEG_TO_RAD  * (m_rotation)) * m_speed * (dt / 1000),
										   m_position.y + std::sin(DEG_TO_RAD * (m_rotation)) * m_speed * (dt / 1000));
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
		window.draw(m_checkpointRectangles.at(m_currentCheckpoint));
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