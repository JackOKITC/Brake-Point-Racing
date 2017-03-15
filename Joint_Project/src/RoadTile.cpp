#include "RoadTile.h"

RoadTile::RoadTile()
{
}

RoadTile::RoadTile(const std::string & image, const sf::Vector2f &pos, const double &rotation, const double &scale)
{
	std::string temp = image;
	m_roadTex = ResourceManager::instance().m_holder[temp];

	m_roadSprite.setTexture(m_roadTex);

	m_position = pos;
	m_rotation = rotation;

	m_roadSprite.setPosition(m_position);
	m_roadSprite.setOrigin(m_roadTex.getSize().x /2, m_roadTex.getSize().y / 2);
	m_roadSprite.scale(scale, scale);
	m_roadSprite.setRotation(m_rotation);

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

bool RoadTile::culling(sf::Vector2f & centreScreen, sf::RenderWindow & window)												/*centreScreen.x > m_position.x &&
																															centreScreen.x < m_position.x + m_roadTex.getSize().x / 2 &&
																															centreScreen.y > m_position.y &&
																															centreScreen.y < m_position.y + m_roadTex.getSize().y / 2*/
																															/*m_position.x < centreScreen.x + halfWidth &&
																																m_position.x > centreScreen.x &&
																															m_position.y < centreScreen.y + halfHeight &&
																																m_position.y > centreScreen.y*/
{

	double halfHeight = window.getSize().y / 2;
	double halfWidth = window.getSize().x / 2;

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