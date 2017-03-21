#ifndef CHECKPOINT_H
#define CHECKPOINT_H

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