#ifndef NODE_H
#define NODE_H

#include "SFML\Graphics.hpp"
#include <iostream>

class Node
{
public:
	Node();
	~Node();

private:
	int m_nodeNumber;
	sf::Vector2f m_position;
 };
#endif // !NODE_H