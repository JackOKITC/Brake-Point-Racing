#ifndef PLAY_H
#define PLAY_H

/// <summary>
/// Author: Peter Daly, John O'Grady, Jack O'Kelly, D.J. O'Leary
/// Version: 1.0
/// Created: 08/03/2017
/// </summary>

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
	/// <summary>
	/// Constructor that takes 5 arguments, them being:
	/// font which stores the font that will to draw text to the screen,
	/// gameState is a pointer to the object in game.cpp,
	/// whichMap represents which map the player has chosen,
	/// player pointer to the player object,
	/// level pointer to get access to  data such as RoadTile positions.
	/// </summary>
	/// <param name="font"></param>
	/// <param name="gameState"></param>
	/// <param name="whichMap"></param>
	/// <param name="player"></param>
	/// <param name="level"></param>
	Play(sf::Font & font, GameState *gameState, bool whichMap, Player *player, LevelData *level);
	~Play();	// De-constructor for the play screen.

	/// <summary>
	/// Takes 3 arguments, them being:
	/// controller which represents the controller the player is using,
	/// dt is the time per update,
	/// whichmap is what map the player has chosen.
	/// 
	/// This is also where any other method that needs to be called frequently is called.
	/// </summary>
	/// <param name="controller"></param>
	/// <param name="dt"></param>
	/// <param name="whichMap"></param>
	void update(Xbox360Controller & controller, double dt, bool whichMap);
	void render(sf::RenderWindow & window);	// Displays everything to the screen.

	void generateRoad();	// Generates the road tiles that will be used.
	void generateNode();	// Generates the ai nodes that will be used.
	void generateCheckpoint();	// Generates the player checkpoints that will be used.

	void checkCheckpoint();	// Checks if the player has reached the next checkpoint.
	void finishingPos();	// Checks what position the player has finished in.

	int m_racePosition;	// The players position in the race.

private:
	LevelData m_level;	// Which level the game is on.
	GameState *m_state;	// Pointer to the gameState in game.cpp.
	Xbox360Controller * m_controller;	// Pointer to the controller in game.cpp.

	static const int MAX_AI = 2;	// The number of ai opponents.
	Ai * aiCars[MAX_AI];	// Array of ai opponents, Its size is equal to MAX_AI.

	Player *m_player;	// Pointer to the player object.
	int m_currentCar;	// The current car that is selected.

	std::vector<std::unique_ptr<RoadTile>> m_roadTiles1;	// Vector of RoadTiles that represent the grassy plains map.
	std::vector<std::unique_ptr<RoadTile>> m_roadTiles2;	// Vector of RoadTiles that represent the icy wasteland map.

	std::vector<std::unique_ptr<Node>> m_nodes1;	// Vector of Nodes that represent the nodes on the grassy plains map.
	std::vector<std::unique_ptr<Node>> m_nodes2;	// Vector of Nodes that represent the nodes on the icy wasteland map.

	std::vector<std::unique_ptr<Checkpoint>> m_checkpoints1;	// Vector of Checkpoints that represent the checkpoints on the grassy plains map.
	std::vector<std::unique_ptr<Checkpoint>> m_checkpoints2;	// Vector of Checkpoints that represent the checkpoints on the icy wasteland map.
	std::vector<sf::RectangleShape> m_checkpointRectangles1;	// Vector of RectangleShapes that represent the visible checkpoints on the grassy plains map.
	std::vector<sf::RectangleShape> m_checkpointRectangles2;	// Vector of RectangleShapes that represent the visible checkpoints on the icy wasteland map.

	sf::Texture m_startlineTexture;	// Stores the texture that represents the startline.
	sf::Sprite m_startlineSprite;	// The object that represents the startline in the game world.

	bool m_callOnce = true;	// Allows for objects to be initialized in the update loop.
	bool m_slowDown = false;	// Represents whether or not the player needs to be slowed down due to being off road.

	sf::View m_followPlayer; //private member in class
	bool m_whichMap;	// Represents which map the player has chosen. false == grassy plains and true == icy wasteland 


	const int MAX_LAPS = 1;	// The maximum number of laps the player and ai must complete to finish the race.
	int m_lap;	// The current lap the player is on.

	int m_currentCheckpoint;	// The current checkpoint the player must reach.
	const float CHECKPOINT_WIDTH = 10;	// The width of the checkpoint rectangle.
	const float CHECKPOINT_HEIGHT = 120;	// The height of the checkpoint rectangle.

	bool m_gameOver = false;	// Represents whether the game has ended.

	sf::Font m_font;	// Stores a font

	sf::Time m_currentTime;	// Stores the current time

	int m_time = 0;	// Initialising the time variable that will be added to a string
	int m_pos;	// Stores the player's position

	// Label Array variables
	std::string m_strings[2] = { "Time: " + m_time, "Position: " + m_pos };
	Label *m_labels[2];
	const int LABEL_COUNT = 2;

	int m_playerTime = 0;
};
#endif // !PLAY_H
