#ifndef CAR_H
#define CAR_H

#include "Xbox360Controller.h"
#include <iostream>
#include "Ai.h"
#include "ResourceManager.h"
#include "Checkpoint.h"


class Car
{
public:
	Car(bool isAi, std::vector<std::unique_ptr<Node>> & nodes, std::vector<std::unique_ptr<Checkpoint>> &checkpoints);
	~Car();

	void update(Xbox360Controller & controller, double dt);
	void render(sf::RenderWindow & window);

	void moveCar(Xbox360Controller & controller);

	sf::Vector2f m_position;

private:

	sf::Texture m_carTex;
	sf::Sprite m_carSprite;
	sf::RenderTexture renTex;

	Xbox360Controller * m_controller;

	bool m_isAi;

	int m_currentCheckpoint;
	int m_lap;

	sf::Vector2f m_velocity;
	float m_rotation;
	float m_speed;

	Ai *m_aiCar;

	sf::CircleShape m_nodePlacement;
	int m_nodePlacementNumber;

	std::vector<std::unique_ptr<Node>> &m_nodes;
	std::vector<std::unique_ptr<Checkpoint>> &m_checkpoints;
	std::vector<sf::RectangleShape> m_checkpointRectangles;

	const double MAX_FORWARD_SPEED = 5;
	const double MAX_REVERSE_SPEED = -10;
	const double DEG_TO_RAD = 3.14159 / 180.0f;
	const float CHECKPOINT_TOLERANCE = 50.0f;
	const int MAX_LAPS = 3;

	/// <summary>
	/// coefficient of friction from this site.
	/// http://hyperphysics.phy-astr.gsu.edu/hbase/Mechanics/frictire.html
	/// </summary>
	const float DECCELERATION_CAUSED_BY_FRICTION = (0.7 * 9.81) / 1000;
	
};
#endif // !CAR_H
