#include "Checkpoint.h"

Checkpoint::Checkpoint()
{

}

Checkpoint::Checkpoint(const int & number, const sf::Vector2f & pos, const double & rotation)
{
	m_checkpointNumber = number;
	m_position = pos;
	m_rotation = rotation;
}

Checkpoint::~Checkpoint()
{

}