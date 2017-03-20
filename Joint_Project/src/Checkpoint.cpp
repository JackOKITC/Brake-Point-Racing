#include "Checkpoint.h"

Checkpoint::Checkpoint()
{

}

Checkpoint::Checkpoint(const int & number, const sf::Vector2f & pos)
{
	m_checkpointNumber = number;
	m_position = pos;
}

Checkpoint::~Checkpoint()
{

}