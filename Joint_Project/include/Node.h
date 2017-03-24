#ifndef NODE_H
#define NODE_H

/// <summary>
/// Author: D.J. O'Leary
/// Version: 1.0
/// Created: 13/03/2017
/// </summary>

#include "SFML\Graphics.hpp"
#include <iostream>

class Node
{
public:
	Node();	// Default constructor for a node with no arguments.
	/// <summary>
	/// Constructor that takes 2 arguments, them being:
	/// number which is the number that the node is on the list of nodes,
	/// pos is the position of the node in the game world.
	/// </summary>
	/// <param name="number"></param>
	/// <param name="pos"></param>
	Node(const int &number, const sf::Vector2f &pos);
	~Node();	// De-constructor for the node object.

	sf::Vector2f m_position;	// Stores the position of the node.
private:
	int m_nodeNumber;	// Stores the number of the node.
 };
#endif // !NODE_H