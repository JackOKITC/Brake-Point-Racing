
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
	const sf::Time TIME_PER_UPDATE = sf::microseconds(1000);
public:
	Play();
	Play(sf::Font & font, GameState *gameState, bool whichMap);
	~Play();
	LevelData m_level;

	const int LABEL_COUNT = 1;

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

	sf::Time currentTime;
	double m_time;

	sf::Font m_font;
	std::string time;

	Label *m_labels[1];
};
#endif // !PLAY_H
