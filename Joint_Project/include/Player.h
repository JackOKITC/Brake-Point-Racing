#ifndef PLAYER_H
#define PLAYER_H

#include "LevelLoader.h"
#include "Xbox360Controller.h"
#include "SFML/Graphics.hpp"
#include "Car.h"
#include "ResourceManager.h"

class Player
{
public:
	Player();
	Player(LevelData &level);
	~Player();

	void update(double &dt, Xbox360Controller *controller);
	void render(sf::RenderWindow &window);

	Car *m_playerCar[3];
	sf::Texture m_temp;

	int m_currentCar;

private:
};

#endif //!PLAYER_H