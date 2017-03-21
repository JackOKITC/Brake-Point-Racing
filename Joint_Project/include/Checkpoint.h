#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include "SFML\Graphics.hpp"
#include <iostream>

class Checkpoint
{
public:
	Checkpoint();
<<<<<<< HEAD
	Checkpoint(const int &number, const sf::Vector2f &pos, const double &rotation);
	~Checkpoint();

	sf::Vector2f m_position;
	double m_rotation;
=======
	Checkpoint(const int &number, const sf::Vector2f &pos);
	~Checkpoint();

	sf::Vector2f m_position;
>>>>>>> cf1e810e1d5d0f95e85ee06315d9782f7c49ebfe
private:
	int m_checkpointNumber;
};
#endif // !CHECKPOINT_H