#ifndef CHECKPOINT_H
#define CHECKPOINT_H

/// <summary>
/// Author: D.J. O'Leary
/// Version: 1.0
/// Created: 21/03/2017
/// </summary>

#include "SFML\Graphics.hpp"
#include <iostream>

class Checkpoint
{
public:
	Checkpoint();

	Checkpoint(const int &number, const sf::Vector2f &pos, const double &rotation);
	~Checkpoint();

	sf::Vector2f m_position;
	double m_rotation;

private:
	int m_checkpointNumber;
};
#endif // !CHECKPOINT_H