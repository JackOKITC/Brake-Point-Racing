#ifndef AI_H
#define AI_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "Node.h"
#include <Thor\Vectors.hpp>


class Ai
{
public:
	Ai(std::vector<std::unique_ptr<Node>> & nodes);
	~Ai();

	void update(double dt);
	void render(sf::RenderWindow & window);

	sf::Vector2f m_position;

private:

	int m_currentNode;

	sf::Texture m_carTex;
	sf::Sprite m_carSprite;

	sf::Vector2f m_velocity;

	sf::Vector2f m_steering;

	sf::Vector2f m_followPath() const;

	std::vector<std::unique_ptr<Node>> &m_nodes;

	float m_rotation;
	float m_speed = 0.0f;

	const double DEG_TO_RAD = 3.14159 / 180.0f;
};
#endif // !AI_H