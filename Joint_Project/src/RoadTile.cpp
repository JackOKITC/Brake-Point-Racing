#include "RoadTile.h"

RoadTile::RoadTile()
{
}

RoadTile::RoadTile(const std::string & image, const sf::Vector2f &pos, const double &rotation, const double &scale, int num, const std::string &path)
{
	std::string temp = image;
	m_roadTex = ResourceManager::instance().m_holder[temp];
	m_roadNumber = num;
	m_roadSprite.setTexture(m_roadTex);

	m_position = pos;
	m_rotation = rotation;
	m_collisonImage = new sf::Image;
	m_roadSprite.setPosition(m_position);
	m_roadSprite.setRotation(m_rotation);
	
	m_collisonImage->loadFromFile(path);
}

RoadTile::~RoadTile()
{

}

void RoadTile::update(double dt)
{
	
}

void RoadTile::render(sf::RenderWindow & window)
{
	window.draw(m_roadSprite);
}

bool RoadTile::culling(sf::Vector2f & centreScreen, sf::RenderWindow & window)																																										
{

	if (centreScreen.x > m_position.x - 225  &&
		centreScreen.x < m_position.x + m_roadSprite.getLocalBounds().width + 225 &&
		centreScreen.y > m_position.y - 150  &&
		centreScreen.y < m_position.y + m_roadSprite.getLocalBounds().height + 150)
	{
		return true;
	}
	else
	{
		return false;
	}
		
}

void RoadTile::whichTile(sf::Vector2f carPos)
{
	if (carPos.x > m_position.x &&
		carPos.x < m_position.x + (m_roadSprite.getLocalBounds().width ) &&
		carPos.y > m_position.y &&
		carPos.y < m_position.y + (m_roadSprite.getLocalBounds().height ))
	{
		carIsOn = true;
	}
	else
		carIsOn = false;
}

void RoadTile::checkOffRoad(sf::Vector2f carPos)
{
	sf::Vector2f relativePos = m_roadSprite.getPosition();
	relativePos = carPos - relativePos;

<<<<<<< HEAD
=======

>>>>>>> cf1e810e1d5d0f95e85ee06315d9782f7c49ebfe
	//if (m_collisonImage->getPixel(relativePos.x, relativePos.y).g > 110)
	//{
	//	std::cout << "Slow Down" << (int)relativePos.x << "," << (int)relativePos.y << std::endl;
	//}
	//else
	//{
	//	std::cout << "yay" << (int)relativePos.x << "," << (int)relativePos.y << std::endl;
	//}
<<<<<<< HEAD
=======

>>>>>>> cf1e810e1d5d0f95e85ee06315d9782f7c49ebfe
}