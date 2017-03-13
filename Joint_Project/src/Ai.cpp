#include "Ai.h"

Ai::Ai()
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
	m_carSprite.setScale(0.4, 0.4);
	m_carSprite.setRotation(m_rotation);

	m_carSprite.setOrigin(m_carSprite.getLocalBounds().width / 2, m_carSprite.getLocalBounds().height / 2);
}

Ai::~Ai()
{
}

void Ai::update(double dt)
{
	Seek(m_nodeNumber);
	m_carSprite.setPosition(m_position);
	m_carSprite.setRotation(m_rotation);
	
	sf::Vector2f newPos = sf::Vector2f(m_position.x + std::cos(DEG_TO_RAD *(m_rotation - 90)) * m_speed * (dt / 1000), m_position.y + std::sin(DEG_TO_RAD *(m_rotation - 90)) * m_speed * (dt / 1000));

	m_position = newPos;
}

void Ai::render(sf::RenderWindow & window)
{
	window.draw(m_carSprite);
}

void Ai::Seek(int nodeNumber)
{
}