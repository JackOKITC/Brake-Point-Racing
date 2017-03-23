#include "Checkpoint.h"

Checkpoint::Checkpoint()
{

}


Checkpoint::Checkpoint(const int & number, const sf::Vector2f & pos, const double & rotation)
{
	m_checkpointNumber = number;	// initialising the checkpoint number
	m_position = pos;	// initialsing the position
	m_rotation = rotation;	// initialising the rotation

}

Checkpoint::~Checkpoint()
{

}