#ifndef PLAY_H
#define PLAY_H

#include "GameState.h"
#include "Xbox360Controller.h"
#include <iostream>
#include "Car.h"
#include "ResouceManager.h"
#include "RoadTile.h"
#include <vector>

class Play
{
public:
	Play();
	Play(GameState *gameState);
	~Play();
	LevelData m_level;

	void update(Xbox360Controller & controller, double dt);
	void render(sf::RenderWindow & window);

	void generateRoad();

private:
	GameState *m_state;

	sf::Texture m_backgroundTex;
	sf::Sprite m_backgroundSprite;
	Xbox360Controller * m_controller;
	Car * car;

	std::vector<std::unique_ptr<RoadTile>> m_roadTiles;

	sf::View m_followPlayer; //private member in class
};
#endif // !PLAY_H
