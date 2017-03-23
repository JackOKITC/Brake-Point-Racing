#ifndef CAR_H
#define CAR_H

/// <summary>
/// Author: Peter Daly, John O'Grady, D.J. O'Leary
/// Version: 1.0
/// Created: 08/03/2017
/// </summary>

#include "Xbox360Controller.h"
#include <iostream>
#include "Checkpoint.h"

class Car
{
public:
	Car();	// Default constructor for a car with no arguments.
	/// <summary>
	/// Construct that 4 arguments, them being:
	/// carTex is the passed texture for the car,
	/// brake is passed to be used in equations that give each car different game feel.
	/// handling is passed to be used in equations that give each car different game feel.
	/// acceleration is passed to be used in equations that give each car different game feel.
	/// </summary>
	/// <param name="carTex"></param>
	/// <param name="brake"></param>
	/// <param name="handling"></param>
	/// <param name="acceleration"></param>
	Car(sf::Texture &carTex, int brake, int handling, int acceleration);
	~Car();	// De-constructor for the car.

	/// <summary>
	/// Contains 2 arguments, them being:
	/// controller which is used to allow the player car to steer,
	/// dt which is used in determining how much time has passed since the previous update.
	/// 
	/// This is also where any other method that needs to be called frequently is called.
	/// </summary>
	/// <param name="controller"></param>
	/// <param name="dt"></param>
	void update(Xbox360Controller & controller, double dt);

	void render(sf::RenderWindow & window);	// Outputs sprites to the window that it takes as a argument.

	void moveCar(Xbox360Controller & controller);	// Converts controller input to onscreen movement of the player car.
	void slowCar(bool slow);	// Reduces the speed of the player car if it is no longer on the road.
	void updateStat(std::string stat);	// Upgrades the various stats of the player car.
	int returnDecel();	// Returns the value stored in m_deceleration.
	int returnHandle();	// Returns the value stored in m_handling.
	int returnAcel();	// Returns the value stored in m_acceleration.

	sf::Vector2f m_position;	// The stored position of the player car.
	float m_rotation;	// The stored rotation of the player car.
	sf::Sprite m_carSprite;	// The sprite use to represent the player in the game world.

	int m_upgradeLevels[3];	// Stores the value of each upgrade for the selected player car.

private:

	sf::Texture m_carTex;	// Stores the texture for the player car.

	Xbox360Controller * m_controller;	// pointer to the controller object in the game class.

	int m_currentCheckpoint;	// The number of the checkpoint the player currently is heading to .
	int m_lap;	// The lap the player is on.

	sf::Vector2f m_velocity;	// Velocity vector of the player car.
	float m_speed;	// Stores the speed at which the player car is moving.

	float m_handling;	// Stores the value of the currently selected cars handling.
	float m_deceleration;	// Stores the value of the currently selected cars braking.
	float m_acceleration;	// Stores the value of the currently selected cars acceleration.

	const double MAX_FORWARD_SPEED = 15;	// Stores the top speed at which the player car can move forwards.
	const double MAX_REVERSE_SPEED = -10;	// Stores the top speed at which the player car can move backwards.
	const double DEG_TO_RAD = 3.14159 / 180.0f;	// Formula for converting degrees to radians.
	const float CHECKPOINT_WIDTH = 10.0f;	// Stores the width of each player checkpoint.
	const float CHECKPOINT_HEIGHT = 180.0f;	// Stores the height of each player checkpoint.

	/// <summary>
	/// coefficient of friction from this site.
	/// http://hyperphysics.phy-astr.gsu.edu/hbase/Mechanics/frictire.html
	/// </summary>
	const float DECCELERATION_CAUSED_BY_FRICTION = (0.7 * 9.81) / 1000;	// Stores the value of the decelercation caused by friction.
};
#endif // !CAR_H
