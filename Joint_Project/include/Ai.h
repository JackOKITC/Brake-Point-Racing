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
	/// <summary>
	/// Constructor that takes 2 arguments, them being:
	/// nodes the ai follows to complete the circuit,
	/// position the ai car will be placed in the game world.
	/// </summary>
	/// <param name="nodes"></param>
	/// <param name="position"></param>
	Ai(std::vector<std::unique_ptr<Node>> & nodes, sf::Vector2f & position);
	~Ai();	// De-constructor for the ai object.

	/// <summary>
	/// Takes 2 arguments, them being:
	/// dt which is the time between updates,
	/// carSprite which represents another car.
	/// 
	/// This is also where any other method that needs to be called frequently is called.
	/// </summary>
	/// <param name="dt"></param>
	/// <param name="carSprite"></param>
	void update(double dt, sf::Sprite carSprite);
	void render(sf::RenderWindow & window);	// Where everything gets drawn to the game window.

	sf::Vector2f m_followPath();	// Sets the ai after the next node.

	sf::Vector2f m_position;	//	The ai's position in the game world.
	sf::Sprite m_carSprite;	// The sprite used by the ai
	int m_currentNode;	//	The next node the ai is heading to.

	// Function to save the AI's time
	void setFinishTime(int time);

	// The AI's time upon finishing
	int m_finishTime;
	int m_lap;

private:

	const int NODE_TOLERANCE = 45.0f;	// The radius around each node that counts as being touched.

	sf::Texture m_carTex;	// Texture used to represent the ai.
	sf::Vector2f m_velocity;	// Velocity vector of the ai.
	
	float m_rotation;	// Stores the rotation of the ai.
	float m_speed;	// Stores the speed of the ai.

	sf::Vector2f m_steering;	// Vector that determines the direction of the ai.

	std::vector<std::unique_ptr<Node>> &m_nodes;	// Vector of nodes on the map.
	std::vector<sf::CircleShape> m_circles;	// Represent the nodes in the game world.

	const float MAX_FORCE = 10.0f;	// The max force applied to the ai to avoid other cars.
	const float MAX_SPEED = 20.0f;	// Max speed of the ai.

	const double PI = atan(1) * 4;	// Formula to deduce PI.
	const double DEG_TO_RAD = PI / 180.0f;	// Fomula to convert degrees to radians.

	const sf::CircleShape findMostThreateningObstacle(sf::Sprite);
	sf::Vector2f collisionAvoidance(sf::Sprite carSprite);
	const float MAX_SEE_AHEAD = 25.0f;	// The length of the m_ahead vector.
	const float MAX_AVOID_FORCE = 10.0f;	// Maximum force applied to the ai tank to avoid collision.
	sf::Vector2f m_ahead;	// Vector that stays ahead of the tank and detects walls before they are hit.
	sf::Vector2f m_halfAhead;	// Vector that stays ahead of the tank and detects walls before they are hit, is half the length of m_ahead to detect only closer objects
	float m_random;	// Stores the random value.
	int m_setCarCounter = 0;	// Used to lessen how often the random number is generated.

};
#endif // !AI_H