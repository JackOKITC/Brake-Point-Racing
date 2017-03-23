#ifndef AI_H
#define AI_H

/// <summary>
/// Author: Peter Daly, John O'Grady, Jack O'Kelly, D.J. O'Leary
/// Version: 1.0
/// Created: 13/03/2017
/// </summary>

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
#include <random>

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
	sf::Sprite m_carSprite;
	int m_currentNode;

	// Function to save the AI's time
	void setFinishTime(int time);

	// The AI's time upon finishing
	int m_finishTime;
	int m_lap;

private:

	const int NODE_TOLERANCE = 45.0f;

	sf::Texture m_carTex;
	sf::Vector2f m_velocity;
	
	float m_rotation;
	float m_speed;

	sf::Vector2f m_steering;

	std::vector<std::unique_ptr<Node>> &m_nodes;
	std::vector<sf::CircleShape> m_circles;

	const float MAX_FORCE = 10.0f;
	const float MAX_SPEED = 20.0f;

	const double PI = atan(1) * 4;
	const double DEG_TO_RAD = PI / 180.0f;



	const sf::CircleShape findMostThreateningObstacle(sf::Sprite);
	sf::Vector2f collisionAvoidance(sf::Sprite carSprite);
	const float MAX_SEE_AHEAD = 25.0f;	// The length of the m_ahead vector.
	const float MAX_AVOID_FORCE = 10.0f;	// Maximum force applied to the ai tank to avoid collision.
	sf::Vector2f m_ahead;	// Vector that stays ahead of the tank and detects walls before they are hit.
	sf::Vector2f m_halfAhead;	// Vector that stays ahead of the tank and detects walls before they are hit, is half the length of m_ahead to detect only closer objects
	float m_random;
	int m_setCarCounter = 0;

};
#endif // !AI_H