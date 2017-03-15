#include "RoadTile.h"

RoadTile::RoadTile()
{
}

RoadTile::RoadTile(const std::string & image, const sf::Vector2f &pos, const double &rotation, const double &scale, int num)
{
	std::string temp = image;
	m_roadTex = ResourceManager::instance().m_holder[temp];
	m_roadNumber = num;
	m_roadSprite.setTexture(m_roadTex);

	m_position = pos;
	m_rotation = rotation;

	m_roadSprite.setPosition(m_position);
	m_roadSprite.setOrigin(m_roadTex.getSize().x /2, m_roadTex.getSize().y / 2);
	m_roadSprite.scale(scale, scale);
	m_roadSprite.setRotation(m_rotation);

	if (carIsOn)
	{
		m_collisonImage.loadFromFile(temp);
	}

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

	if (centreScreen.x > m_position.x - 450 - (m_roadSprite.getLocalBounds().width / 2 * 1.5) &&
		centreScreen.x < m_position.x + (m_roadSprite.getLocalBounds().width / 2 * 1.5) + 450 &&
		centreScreen.y > m_position.y - 300 - (m_roadSprite.getLocalBounds().height / 2 * 1.5) &&
		centreScreen.y < m_position.y + (m_roadSprite.getLocalBounds().height / 2 * 1.5) + 300)
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
	if (carPos.x > m_position.x - (m_roadSprite.getLocalBounds().width / 2) &&
		carPos.x < m_position.x + (m_roadSprite.getLocalBounds().width / 2) &&
		carPos.y > m_position.y - (m_roadSprite.getLocalBounds().height / 2) &&
		carPos.y < m_position.y + (m_roadSprite.getLocalBounds().height / 2))
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


	if (m_collisonImage.getPixel(relativePos.x, relativePos.y).r < 60)
	{
		std::cout << "Slow Down" << std::endl;
	}
	else
	{
		std::cout << "yay" << std::endl;
	}

}