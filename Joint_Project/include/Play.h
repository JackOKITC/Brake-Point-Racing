
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
#include "Widget.h"
#include <vector>
#include "Widget.h"
#include "SFML\Graphics.hpp"

class Play
{
	const sf::Time TIME_PER_UPDATE = sf::microseconds(1000);
public:
	Play();
	Play(sf::Font & font, GameState *gameState, bool whichMap, Player *player, LevelData *level);
	~Play();

	void update(Xbox360Controller & controller, double dt, bool whichMap);
	void render(sf::RenderWindow & window);

	void generateRoad();
	void generateNode();
	void generateCheckpoint();

	void checkCheckpoint();
	void finishingPos();

	int m_position;

private:
	LevelData m_level;
	GameState *m_state;
	Xbox360Controller * m_controller;

	static const int MAX_AI = 2;
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

	// 
	sf::Texture m_startlineTexture;
	sf::Sprite m_startlineSprite;

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

	sf::Font m_font;

	sf::Time currentTime;

	int m_time = 0;
	int m_pos;

	std::string m_strings[2] = { "Time: " + m_time, "Position: " + m_pos };
	Label *m_labels[2];
	const int LABEL_COUNT = 2;

	int m_playerTime = 0;

};
#endif // !PLAY_H
