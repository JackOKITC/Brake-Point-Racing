#ifndef PLAY_H
#define PLAY_H

#include "GameState.h"
#include "Xbox360Controller.h"
#include <iostream>
#include "ResourceManager.h"
#include "Ai.h"
#include "Car.h"
#include "Player.h"
#include "Node.h"
#include "Checkpoint.h"
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
	void checkCheckpoint();

private:
	GameState *m_state;
	Xbox360Controller * m_controller;

	static const int MAX_AI = 1;
	Ai * aiCars[MAX_AI];
	Player *m_player;
	int m_currentCar;


	std::vector<std::unique_ptr<RoadTile>> m_roadTiles1;
	std::vector<std::unique_ptr<RoadTile>> m_roadTiles2;
	std::vector<std::unique_ptr<Node>> m_nodes1;
	std::vector<std::unique_ptr<Node>> m_nodes2;
	std::vector<std::unique_ptr<Checkpoint>> m_checkpoints1;
	std::vector<std::unique_ptr<Checkpoint>> m_checkpoints2;
	std::vector<sf::RectangleShape> m_checkpointRectangles1;
	std::vector<sf::RectangleShape> m_checkpointRectangles2;

	bool m_callOnce = true;
	bool m_slowDown = false;

	sf::View m_followPlayer; //private member in class
	bool m_whichMap;

	const int MAX_LAPS = 1;
	int m_lap;

	int m_currentCheckpoint;
	const float CHECKPOINT_WIDTH = 10;
	const float CHECKPOINT_HEIGHT = 120;

	bool m_gameOver = false;
};
#endif // !PLAY_H
