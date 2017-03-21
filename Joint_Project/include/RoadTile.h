#ifndef ROADTILE_H
#define ROADTILE_H

#include <iostream>
#include "SFML\Graphics.hpp"
#include "ResourceManager.h"

class RoadTile
{
public:
	RoadTile();
	RoadTile(const std::string &image, const sf::Vector2f &pos, const double &rotation, const double &scale, int num, const std::string &path);
	~RoadTile();

	void update(double dt);
	void render(sf::RenderWindow & window);

	bool culling(sf::Vector2f & centreScreen, sf::RenderWindow & window);

	sf::Vector2f m_position;

	void whichTile(sf::Vector2f carPos); // Function to find out which tile the car is on
	bool checkOffRoad(sf::Vector2f carPos, bool whichMap);

	bool carIsOn = false;

private:

	sf::Texture m_roadTex;
	sf::Sprite m_roadSprite;

	float m_rotation;

	const double DEG_TO_RAD = 3.14159 / 180.0f;
	sf::Image * m_collisonImage;
	int m_roadNumber;
};
#endif // !ROADTILE_H
