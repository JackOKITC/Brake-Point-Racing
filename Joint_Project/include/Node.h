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
	Node();
	Node(const int &number, const sf::Vector2f &pos);
	~Node();

	sf::Vector2f m_position;
private:
	int m_nodeNumber;
 };
#endif // !NODE_H