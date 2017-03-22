#ifndef AI_H
#define AI_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "Node.h"
#include <Thor\Vectors.hpp>
#include "BTMath.h"
#include <Thor\Math.hpp>
#include <Thor\Shapes.hpp>
#include <Thor\Vectors.hpp>
#include "ResourceManager.h"

class Ai
{
public:
	Ai();
	Ai(std::vector<std::unique_ptr<Node>> & nodes, sf::Vector2f & position);
	~Ai();

	void update(double dt, sf::Sprite carSprite);
	void render(sf::RenderWindow & window);

	sf::Vector2f m_followPath();

	sf::Vector2f m_position;

private:

	const int NODE_TOLERANCE = 40.0f;

	sf::Texture m_carTex;
	sf::Sprite m_carSprite;

	int m_currentNode;

	sf::Vector2f m_velocity;
	
	float m_rotation;
	float m_speed;

	sf::Vector2f m_steering;

	std::vector<std::unique_ptr<Node>> &m_nodes;
	std::vector<sf::CircleShape> m_circles;

	const float MAX_FORCE = 10.0f;
	const float MAX_SPEED = 27.5f;

	const double PI = atan(1) * 4;
	const double DEG_TO_RAD = PI / 180.0f;



	const sf::CircleShape findMostThreateningObstacle(sf::Sprite);
	sf::Vector2f collisionAvoidance(sf::Sprite carSprite);
	const float MAX_SEE_AHEAD = 50.0f;	// The length of the m_ahead vector.
	const float MAX_AVOID_FORCE = 50.0f;	// Maximum force applied to the ai tank to avoid collision.
	sf::Vector2f m_ahead;	// Vector that stays ahead of the tank and detects walls before they are hit.
	sf::Vector2f m_halfAhead;	// Vector that stays ahead of the tank and detects walls before they are hit, is half the length of m_ahead to detect only closer objects
};
#endif // !AI_H