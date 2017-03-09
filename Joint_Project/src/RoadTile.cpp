#include "RoadTile.h"

RoadTile::RoadTile()
{
}

RoadTile::RoadTile(const std::string & image, const sf::Vector2f &pos, const double &rotation, const double &scale)
{
	if (!m_roadTex.loadFromFile(".//resources//images//road//road_parts//" + image))
	{
		std::cout << "Problem loading Texture for splash screen";
	}

	m_roadSprite.setTexture(m_roadTex);

	m_position = pos;
	m_rotation = rotation;

	m_roadSprite.setPosition(m_position);
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