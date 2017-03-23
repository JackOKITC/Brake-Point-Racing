#ifndef CAR_H
#define CAR_H

#include "Xbox360Controller.h"
#include <iostream>
#include "Checkpoint.h"

class Car
{
public:
	Car();
	Car(sf::Texture &carTex, int brake, int handling, int acceleration);
	~Car();

	void update(Xbox360Controller & controller, double dt);
	void render(sf::RenderWindow & window);

	void moveCar(Xbox360Controller & controller);
	void slowCar(bool slow);
	void updateStat(std::string stat);
	int returnDecel();
	int returnHandle();
	int returnAcel();

	sf::Vector2f m_position;
	float m_rotation;
	sf::Sprite m_carSprite;

	int m_upgradeLevels[3];

private:

	sf::Texture m_carTex;
	sf::RenderTexture renTex;

	Xbox360Controller * m_controller;

	int m_currentCheckpoint;
	int m_lap;

	sf::Vector2f m_velocity;
	float m_speed;

	float m_handling;
	float m_deceleration;
	float m_acceleration;

	const double MAX_FORWARD_SPEED = 15;
	const double MAX_REVERSE_SPEED = -10;
	const double DEG_TO_RAD = 3.14159 / 180.0f;
	const float CHECKPOINT_WIDTH = 10.0f;
	const float CHECKPOINT_HEIGHT = 180.0f;

	/// <summary>
	/// coefficient of friction from this site.
	/// http://hyperphysics.phy-astr.gsu.edu/hbase/Mechanics/frictire.html
	/// </summary>
	const float DECCELERATION_CAUSED_BY_FRICTION = (0.7 * 9.81) / 1000;
	
};
#endif // !CAR_H
