#ifndef NODE_H
#define NODE_H

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