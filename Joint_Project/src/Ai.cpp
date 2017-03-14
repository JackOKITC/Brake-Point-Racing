#include "Ai.h"


Ai::Ai(std::vector<std::unique_ptr<Node>> & nodes) :
	m_nodes(nodes),
	m_currentNode(0),
	m_steering(0,0)
{
	if (!m_carTex.loadFromFile(".//resources//images//cars//car_4.png"))
	{
		std::cout << "Problem loading texture for ai car" << std::endl;
	}

	m_carSprite.setTexture(m_carTex);
	m_position = sf::Vector2f(100,300);
	m_velocity = sf::Vector2f(0, 0);
	m_rotation = 90.0f;

	m_carSprite.setPosition(m_position);
	m_carSprite.setScale(0.3, 0.3);
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
	
	sf::Vector2f newPos = sf::Vector2f(m_position.x + std::cos(DEG_TO_RAD *(m_rotation - 90)) * m_speed * (dt / 1000), 
									   m_position.y + std::sin(DEG_TO_RAD *(m_rotation - 90)) * m_speed * (dt / 1000));

	sf::Vector2f vectorToNode = m_followPath();

	if (thor::length(vectorToNode) <= 3)
	{
		m_currentNode++;
	}

	m_steering += thor::unitVector(vectorToNode);

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
