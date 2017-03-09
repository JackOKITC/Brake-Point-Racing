#ifndef ROADTILE_H
#define ROADTILE_H

#include <iostream>
#include "SFML\Graphics.hpp"

class RoadTile
{
public:
	RoadTile();
	RoadTile(const std::string &image, const sf::Vector2f &pos, const double &rotation, const double &scale);
	~RoadTile();

	void update(double dt);
	void render(sf::RenderWindow & window);

	sf::Vector2f m_position;

private:

	sf::Texture m_roadTex;
	sf::Sprite m_roadSprite;

	float m_rotation;

	const double DEG_TO_RAD = 3.14159 / 180.0f;
};
#endif // !ROADTILE_H
