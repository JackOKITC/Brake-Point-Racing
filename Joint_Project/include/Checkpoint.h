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
	Checkpoint();	// Default constructor for a checkpoint with no arguments.
	/// <summary>
	/// Checkpoint that takes 3 arguments, them being:
	/// number which is used to determine where it falls on the list,
	/// pos to determine where it will be place in the game world,
	/// rotation which is used to determine its rotation in the game world.
	/// </summary>
	/// <param name="number"></param>
	/// <param name="pos"></param>
	/// <param name="rotation"></param>
	Checkpoint(const int &number, const sf::Vector2f &pos, const double &rotation);
	~Checkpoint();

	sf::Vector2f m_position;	// Stores the passed value of the checkpoint.
	double m_rotation;	// Stores the passed value of the checkpoint.

private:
	int m_checkpointNumber; // Stores the passed value of the checkpoint.
};
#endif // !CHECKPOINT_H