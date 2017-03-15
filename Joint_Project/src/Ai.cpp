#include "Ai.h"


Ai::Ai(std::vector<std::unique_ptr<Node>> & nodes, float speed, float rotation, sf::Vector2f velocity, sf::Texture &carTexture, sf::Sprite &carSprite) :
	m_nodes(nodes),
	m_currentNode(0),
	m_steering(0, 0),
	MAX_FORCE(500.0),
	MAX_SPEED(50.0),
	m_speed(speed),
	m_rotation(rotation),
	m_velocity(velocity),
	m_carTex(carTexture),
	m_carSprite(carSprite)
{
	m_carSprite.setTexture(m_carTex);
	m_position = sf::Vector2f(100,300);
	m_velocity = sf::Vector2f(0, 0);
	m_rotation = 90.0f;

	m_carSprite.setPosition(m_position);
	m_carSprite.setScale(0.4, 0.4);
	m_carSprite.setRotation(m_rotation);

	m_carSprite.setOrigin(m_carSprite.getLocalBounds().width / 2, m_carSprite.getLocalBounds().height / 2);
}

Ai::~Ai()
{
}

void Ai::update(double dt)
{
	m_carSprite.setPosition(m_position);
	m_carSprite.setRotation(m_rotation);
	
	sf::Vector2f newPos = m_steering;			/*sf::Vector2f(m_position.x + std::cos(DEG_TO_RAD *(m_rotation - 90)) * m_speed * (dt / 1000),
													m_position.y + std::sin(DEG_TO_RAD *(m_rotation - 90)) * m_speed * (dt / 1000));*/
	sf::Vector2f vectorToNode = m_followPath();
	
	if (thor::length(vectorToNode) <= 1)
	{
		m_currentNode++;

		if (m_currentNode == 8)
		{
			m_currentNode = 0;
		}
	}

	m_steering += (thor::unitVector(vectorToNode) * m_speed);
	//m_steering = Math::truncate(m_steering, MAX_FORCE);
	m_velocity = Math::truncate(m_steering + m_velocity, MAX_SPEED);

	std::cout << m_currentNode << std::endl;

	m_position = newPos;
}

void Ai::render(sf::RenderWindow & window)
{
	window.draw(m_carSprite);
}

sf::Vector2f Ai::m_followPath() const
{
	sf::Vector2f dist;

	dist = m_nodes.at(m_currentNode)->m_position - m_position;

	return dist;
}