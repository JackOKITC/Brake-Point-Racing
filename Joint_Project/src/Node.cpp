#include "Node.h"

Node::Node()
{

}

Node::Node(const int & number, const sf::Vector2f & pos)
{
	m_nodeNumber = number;	// initialises the node number
	m_position = pos;	// initialises the node position
}

Node::~Node()
{

}