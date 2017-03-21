
#ifndef PLAY_H
#define PLAY_H

#include "GameState.h"
#include "Xbox360Controller.h"
#include <iostream>
#include "Car.h"
#include "ResourceManager.h"
#include "Ai.h"
#include "Node.h"
#include "LevelLoader.h"
#include "RoadTile.h"
#include <vector>
#include "ResourceManager.h"
#include "Widget.h"

class Play
{
public:
	Play();
	Play(sf::Font & font, GameState *gameState, bool whichMap);
	~Play();
	LevelData m_level;

	const int LABEL_COUNT = 2;

	void update(Xbox360Controller & controller, double dt, bool whichMap);
	void render(sf::RenderWindow & window);

	void generateRoad();
	void generateNode();

private:
	GameState *m_state;
	Xbox360Controller * m_controller;
	Car * car;

	static const int MAX_AI = 1;
	Car * aiCars[MAX_AI];

	std::vector<std::unique_ptr<RoadTile>> m_roadTiles1;
	std::vector<std::unique_ptr<RoadTile>> m_roadTiles2;
	std::vector<std::unique_ptr<Node>> m_nodes;
	bool m_callOnce = true;

	sf::View m_followPlayer; //private member in class
	bool m_whichMap;

	int m_time;
	int m_pos;
	sf::Font m_font;
	std::string m_strings[2] = { "Time: " + m_time, "Position: " + m_pos };

	Label *m_labels[2];

	

};
#endif // !PLAY_H
