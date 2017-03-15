#include "Ai.h"

Ai::Ai(std::vector<std::unique_ptr<Node>> & nodes) :
	m_nodes(nodes),
	m_currentNode(0),
	m_steering(0, 0)
{
	m_carTex = g_manager.m_holder["BusTex"];
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

	sf::Vector2f newPos = m_position;			/*sf::Vector2f(m_position.x + std::cos(DEG_TO_RAD *(m_rotation - 90)) * m_speed * (dt / 1000),
													m_position.y + std::sin(DEG_TO_RAD *(m_rotation - 90)) * m_speed * (dt / 1000));*/
	sf::Vector2f vectorToNode = m_followPath();

	m_steering += thor::unitVector(vectorToNode);
	m_steering = Math::truncate(m_steering, MAX_FORCE);
	m_velocity = Math::truncate(m_velocity + m_steering, MAX_SPEED);

	std::cout << "Current node : " << m_currentNode << std::endl;

	// Now we need to convert our velocity vector into a rotation angle between 0 and 359 degrees.
	// The m_velocity vector works like this: vector(1,0) is 0 degrees, while vector(0, 1) is 90 degrees.
	// So for example, 223 degrees would be a clockwise offset from 0 degrees (i.e. along x axis).
	// Note: we add 180 degrees below to convert the final angle into a range 0 to 359 instead of -PI to +PI
	auto dest = atan2(-1 * m_velocity.y, -1 * m_velocity.x) / PI * 180 + 180;

	// Find the shortest way to rotate towards the player (clockwise or anti-clockwise)
	if (std::round(m_rotation - dest) == 0.0)
	{
		m_steering.x = 0;
		m_steering.y = 0;
	}
	else if ((static_cast<int>(std::round(dest - m_rotation + 360))) % 360 < 180)
	{
		// rotate clockwise
		m_rotation += 1;
	}
	else
	{
		// rotate anti-clockwise
		m_rotation -= 1;
	}

	m_speed = thor::length(m_velocity);

	m_position = newPos;
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