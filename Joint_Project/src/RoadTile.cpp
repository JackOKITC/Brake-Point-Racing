#include "RoadTile.h"

RoadTile::RoadTile()
{
}

RoadTile::RoadTile(const std::string & image, const sf::Vector2f &pos, const double &rotation, const double &scale, int num, const std::string &path)
{
	std::string temp = image;	// initialises temp to image
	m_roadTex = ResourceManager::instance().m_holder[temp];	// initialises the road texture to what is stored in temp
	m_roadNumber = num;	// initialises roadnumber
	m_roadSprite.setTexture(m_roadTex);	// assigns the road texture to the road sprite

	// initialising the position and sprite
	m_position = pos;	
	m_rotation = rotation;
	m_collisonImage = new sf::Image;
	m_roadSprite.setPosition(m_position);
	m_roadSprite.setRotation(m_rotation);
	
	m_collisonImage->loadFromFile(path);	// loads the collision image
}

RoadTile::~RoadTile()
{

}

void RoadTile::update(double dt)
{
	
}

void RoadTile::render(sf::RenderWindow & window)
{
	window.draw(m_roadSprite);	// draws the road sprite
}

bool RoadTile::culling(sf::Vector2f & centreScreen, sf::RenderWindow & window)																																										
{
	// an if statement that returns a bool based on if the sprite is out of the viewport bounds, i.e. culling.
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
	// an if statement which returns a bool to check which tile the car is on
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

bool RoadTile::checkOffRoad(sf::Vector2f carPos, bool whichMap)
{
	sf::Vector2f relativePos = m_roadSprite.getPosition();
	relativePos = carPos - relativePos;

	if(!whichMap)
	{
		if (m_collisonImage->getPixel(relativePos.x, relativePos.y).g > 110 && m_collisonImage->getPixel(relativePos.x, relativePos.y).r < 100)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if(m_collisonImage->getPixel(relativePos.x, relativePos.y).r > 230)
		{
			return true;
		}
		else
		{
			return false;
		}
		
	}
}