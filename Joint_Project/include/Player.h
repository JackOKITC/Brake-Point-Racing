#ifndef PLAYER_H
#define PLAYER_H

/// <summary>
/// Author: John O'Grady
/// Version: 1.0
/// Created: 22/02/2017
/// </summary>

#include "LevelLoader.h"
#include "Xbox360Controller.h"
#include "SFML/Graphics.hpp"
#include "Car.h"
#include "ResourceManager.h"

class Player
{
public:
	Player();
	Player(LevelData &level); // player constructor taking level data as an arguement for resource loading
	~Player();

	void update(double &dt, Xbox360Controller *controller);
	void render(sf::RenderWindow &window);

	Car *m_playerCar[3]; // three independant cars which the player can control, each with independant stats
	sf::Texture m_temp;

	int m_currentCar;
	int m_currency; // currency for the player to purchase upgrades with and increase through races

private:
};

#endif //!PLAYER_H