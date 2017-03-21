#ifndef PLAY_H
#define PLAY_H

#include "GameState.h"
#include "Xbox360Controller.h"
#include <iostream>
#include "Car.h"
#include "ResourceManager.h"
#include "Ai.h"
#include "Node.h"
#include "Checkpoint.h"
#include "LevelLoader.h"
#include "RoadTile.h"
#include <vector>

class Play
{
public:
	Play();
	Play(GameState *gameState, bool whichMap);
	~Play();
	LevelData m_level;

	void update(Xbox360Controller & controller, double dt, bool whichMap);
	void render(sf::RenderWindow & window);

	void generateRoad();
	void generateNode();
	void generateCheckpoint();

private:
	GameState *m_state;
	Xbox360Controller * m_controller;
	Car * car;

	static const int MAX_AI = 1;
	Ai * aiCars[MAX_AI];

	std::vector<std::unique_ptr<RoadTile>> m_roadTiles1;
	std::vector<std::unique_ptr<RoadTile>> m_roadTiles2;
	std::vector<std::unique_ptr<Node>> m_nodes1;
	std::vector<std::unique_ptr<Node>> m_nodes2;
	std::vector<std::unique_ptr<Checkpoint>> m_checkpoints1;
	std::vector<std::unique_ptr<Checkpoint>> m_checkpoints2;

	bool m_callOnce = true;
	bool m_slowDown = false;

	sf::View m_followPlayer; //private member in class
	bool m_whichMap;
};
#endif // !PLAY_H
