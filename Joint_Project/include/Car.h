#ifndef CAR_H
#define CAR_H

#include "Xbox360Controller.h"
#include <iostream>
#include "Ai.h"
#include "ResouceManager.h"

class Car
{
public:
	Car(bool isAi, std::vector<std::unique_ptr<Node>> & m_nodes);
	~Car();

	void update(Xbox360Controller & controller, double dt);
	void render(sf::RenderWindow & window);

	void moveCar(Xbox360Controller & controller);

	sf::Vector2f m_position;

private:

	sf::Texture m_carTex;
	sf::Sprite m_carSprite;

	Xbox360Controller * m_controller;

	bool m_isAi;

	sf::Vector2f m_velocity;
	float m_rotation;
	float m_speed = 0.0f;

	Ai *m_aiCar;

	std::vector<std::unique_ptr<Node>> &m_nodes;

	const double DEG_TO_RAD = 3.14159 / 180.0f;
	
	/// <summary>
	/// coefficient of friction from this site.
	/// http://hyperphysics.phy-astr.gsu.edu/hbase/Mechanics/frictire.html
	/// </summary>
	const float DECCELERATION_CAUSED_BY_FRICTION = (0.7 * 9.81) / 1000;
	
};
#endif // !CAR_H
