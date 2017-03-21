#ifndef PLAYER_H
#define PLAYER_H

#include "Game.h"
#include "ResourceManager.h"

class Player
{
public:
	Player();
	~Player();

	void update(sf::Time &dt, Xbox360Controller *controller);
	void render(sf::RenderWindow &window);

	Car *m_playerCar[3];

private:

};

#endif //!PLAYER_H