#include "Checkpoint.h"

Checkpoint::Checkpoint()
{

}

<<<<<<< HEAD
Checkpoint::Checkpoint(const int & number, const sf::Vector2f & pos, const double & rotation)
{
	m_checkpointNumber = number;
	m_position = pos;
	m_rotation = rotation;
=======
Checkpoint::Checkpoint(const int & number, const sf::Vector2f & pos)
{
	m_checkpointNumber = number;
	m_position = pos;
>>>>>>> cf1e810e1d5d0f95e85ee06315d9782f7c49ebfe
}

Checkpoint::~Checkpoint()
{

}