#include "Node.h"

Node::Node()
{

}

Node::Node(const int & number, const sf::Vector2f & pos)
{
	m_nodeNumber = number;
	m_position = pos;
}

Node::~Node()
{

}