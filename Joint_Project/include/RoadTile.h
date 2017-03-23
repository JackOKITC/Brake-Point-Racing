#ifndef ROADTILE_H
#define ROADTILE_H

/// <summary>
/// Author: John o'Grady
/// Version: 1.0
/// Created: 15/03/2017
/// </summary>

#include <iostream>
#include "SFML\Graphics.hpp"
#include "ResourceManager.h"

class RoadTile
{
public:
	RoadTile();	// Default constructor for a RoadTile with no arguments.
	/// <summary>
	/// Constructor with 6 arguments, them being:
	/// image is a string that holds the name of the RoadTile,
	/// pos is the position of the RoadTile in the game world,
	/// rotation is the position of the RoadTile in the game world,
	/// scale is the scale of the RoadTile in the game world,
	/// num is the number of the RoadTile,
	/// path is a string that leads back to the file in its folder.
	/// </summary>
	/// <param name="image"></param>
	/// <param name="pos"></param>
	/// <param name="rotation"></param>
	/// <param name="scale"></param>
	/// <param name="num"></param>
	/// <param name="path"></param>
	RoadTile(const std::string &image, const sf::Vector2f &pos, const double &rotation, const double &scale, int num, const std::string &path);
	~RoadTile();	// De-constructor for a RoadTile.

	void update(double dt);	// Method that loops frequently.
	void render(sf::RenderWindow & window);	// Draws everything to the game window.

	bool culling(sf::Vector2f & centreScreen, sf::RenderWindow & window);	// Checks if each RoadTile is visible, if the RoadTile is visible it will allow it to be drawn.

	sf::Vector2f m_position;	// Stores the positon of the RoadTile in the game world.

	void whichTile(sf::Vector2f carPos);	// Function to find out which tile the car is on.
	bool checkOffRoad(sf::Vector2f carPos, bool whichMap);	// Checks if the player is off of the part of each tile which is considered the road.

	bool carIsOn = false;	// Is true if the car is on the road.

private:

	sf::Texture m_roadTex;	// Stores the texture of the RoadTile.
	sf::Sprite m_roadSprite;	// Represents the RoadTile in the game world.

	float m_rotation;	// Stores the rotation of the RoadTile in the game world.

	const double DEG_TO_RAD = 3.14159 / 180.0f;	// Formula for converting degrees to radians.
	sf::Image * m_collisonImage;	// Image used to determine whether the player is on the road.
	int m_roadNumber;	// Stores the value of what number the RoadTile is.
};
#endif // !ROADTILE_H
