#include "Ai.h"

Ai::Ai(std::vector<std::unique_ptr<Node>> & nodes, sf::Vector2f & position) :
	m_nodes(nodes),
	m_currentNode(0),
	m_steering(0, 0),
	m_position(position.x - 10, position.y) 
{

	m_carTex = ResourceManager::instance().m_holder["Bus2"];

	m_carSprite.setTexture(m_carTex);
	m_velocity = sf::Vector2f(0, 0);
	m_rotation = 45.0f;
	m_speed = 0;

	m_carSprite.setPosition(m_position);

	m_carSprite.setScale(0.2, 0.2);
	m_carSprite.setRotation(m_rotation);

	m_carSprite.setOrigin(m_carSprite.getLocalBounds().width / 2, m_carSprite.getLocalBounds().height / 2);

	for (int i = 0; i < nodes.size(); i++)
	{
		sf::CircleShape circle;
		m_circles.push_back(std::move(circle));
		m_circles.at(i).setOrigin(NODE_TOLERANCE / 2, NODE_TOLERANCE / 2);
		m_circles.at(i).setPosition(m_nodes.at(i)->m_position.x - NODE_TOLERANCE / 2, m_nodes.at(i)->m_position.y - NODE_TOLERANCE / 2);
		m_circles.at(i).setRadius(NODE_TOLERANCE);
		m_circles.at(i).setFillColor(sf::Color(0,0,255,126));
	}
}

Ai::~Ai()
{
}

void Ai::update(double dt)
{	
	sf::Vector2f newPos = m_position;

	sf::Vector2f vectorToNode = m_followPath();

	m_steering += thor::unitVector(vectorToNode);
	m_steering = Math::truncate(m_steering, MAX_FORCE);
	m_velocity = Math::truncate(m_velocity + m_steering, MAX_SPEED);

	// Now we need to convert our velocity vector into a rotation angle between 0 and 359 degrees.
	// The m_velocity vector works like this: vector(1,0) is 0 degrees, while vector(0, 1) is 90 degrees.
	// So for example, 223 degrees would be a clockwise offset from 0 degrees (i.e. along x axis).
	// Note: we add 180 degrees below to convert the final angle into a range 0 to 359 instead of -PI to +PI
	auto dest = atan2(-1 * m_velocity.y, -1 * m_velocity.x) / PI * 180 + 180;

	float currentRotation = m_rotation;

	// Find the shortest way to rotate towards the player (clockwise or anti-clockwise)
	if (std::round(currentRotation - dest) == 0.0)
	{
		m_steering.x = 0;
		m_steering.y = 0;
	}
	else if ((static_cast<int>(std::round(dest - currentRotation + 360))) % 360 < 180)
	{
		// rotate clockwise
		m_rotation = static_cast<int>((m_rotation) + 1) % 360;
		//m_carSprite.rotate(1.0f);
	}
	else
	{
		// rotate anti-clockwise
		m_rotation -= 1;
		if (m_rotation < 0)
		{
			m_rotation = 359;
		}
		//m_carSprite.rotate(-1.0f);
	}

	m_speed = thor::length(m_velocity);

	m_position.x += m_velocity.x * m_speed * (dt / 50000);
	m_position.y += m_velocity.y * m_speed * (dt / 50000);
	m_carSprite.setPosition(m_position);
	m_carSprite.setRotation(m_rotation);
}

void Ai::render(sf::RenderWindow & window)
{
	window.draw(m_carSprite);
	
	
}

sf::Vector2f Ai::m_followPath()
{
	sf::Vector2f dist;

	dist = m_nodes.at(m_currentNode)->m_position - m_position;

	if ((dist.x < NODE_TOLERANCE && dist.y < NODE_TOLERANCE) && (dist.x > -NODE_TOLERANCE && dist.y > -NODE_TOLERANCE))
	{
		m_currentNode++;

		if (m_currentNode >= m_nodes.size())
		{
			m_currentNode = 0;
		}
	}

	return dist;
}