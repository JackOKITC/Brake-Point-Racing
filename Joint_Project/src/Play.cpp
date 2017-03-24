#include "Play.h"

Play::Play()	
{
}

Play::Play(sf::Font & font, GameState *gameState, bool whichMap, Player *player, LevelData *level) :
	m_whichMap(whichMap),
	m_font(font)
{
	m_state = gameState;	// initialises the m_state to the passed gamestate
	m_level = *level;	// initialises the level objecet
	m_player = player;	// initialises the player object
	
	m_time = 0.0;	// Initialises time as 0

	generateNode();
	generateRoad();
	generateCheckpoint();

	m_currentCheckpoint = 0;	// Initialises the current checkpoint the player must head to 0.
	m_lap = 0;	// Initialises the lap the player is on to 0.
	m_followPlayer.setSize(450, 300); // In constructor

	// initialises an array of labels, being passed their relevant variables
	m_labels[0] = new Label(&m_strings[1], &m_font, &sf::Vector2f(0, 0), 15, sf::Color(0, 255, 0));
	m_labels[1] = new Label(&m_strings[0], &m_font, &sf::Vector2f(0, 0), 15, sf::Color(0, 255, 0));

	m_racePosition = 0;	// Initialises the players finishing position.

	m_startlineTexture = ResourceManager::instance().m_holder["Startline"];	// Gets the texture for the startling.
	m_startlineSprite.setTexture(m_startlineTexture);	// Sets the texture.
	m_startlineSprite.setOrigin(m_startlineSprite.getGlobalBounds().width / 2, m_startlineSprite.getGlobalBounds().height / 2);	// Sets the origin of the startline to be its centre point.
}

Play::~Play()
{
}

void Play::update(Xbox360Controller & controller, double dt, bool whichMap)
{

	m_controller = &controller;

	m_whichMap = whichMap;

	if (m_callOnce)	// Initailizes variables that needed to wait for player input.
	{
		if (whichMap)	// Icy Wasteland
		{
			// Sets the initial position of the ai.
			for (int i = 0; i < MAX_AI; i++)
			{
				aiCars[i] = new Ai(m_nodes2, sf::Vector2f(m_nodes2.at(0)->m_position.x - (20 * i), m_nodes2.at(0)->m_position.y + (20 * i)));
			}

			// Sets the initial position of the player.
			for (int i = 0; i < 3; i++)
			{
				m_player->m_playerCar[i]->m_position = sf::Vector2f(m_nodes2.at(0)->m_position.x + 10, m_nodes2.at(0)->m_position.y);
				m_player->m_playerCar[i]->m_rotation = 0.0f;
			}

			// Initialises the startline so that is looks right in the game world.
			m_startlineSprite.setPosition(m_checkpoints2.at(0)->m_position.x, m_checkpoints2.at(0)->m_position.y + 17);
			m_startlineSprite.setRotation(0);
			m_startlineSprite.setScale(0.1,0.19);

			// Initialises each checkpoint as a rectangle so it can be represented in the game world.
			for (int i = 0; i < m_checkpoints2.size(); i++)
			{
				sf::RectangleShape rectangle;
				m_checkpointRectangles2.push_back(std::move(rectangle));
				m_checkpointRectangles2.at(i).setOrigin(CHECKPOINT_WIDTH / 2, CHECKPOINT_HEIGHT / 2);
				m_checkpointRectangles2.at(i).setPosition(m_checkpoints2.at(i)->m_position.x, m_checkpoints2.at(i)->m_position.y);
				m_checkpointRectangles2.at(i).setRotation(m_checkpoints2.at(i)->m_rotation);
				m_checkpointRectangles2.at(i).setSize(sf::Vector2f(CHECKPOINT_WIDTH, CHECKPOINT_HEIGHT));
				m_checkpointRectangles2.at(i).setFillColor(sf::Color(255, 0, 0, 126));
			}
		}
		if (!whichMap)	// Grassy Plains
		{
			// Sets the initial position of the ai.
			for (int i = 0; i < MAX_AI; i++)
			{
				aiCars[i] = new Ai(m_nodes1, sf::Vector2f(m_nodes1.at(0)->m_position.x + (30 * i), m_nodes1.at(0)->m_position.y - (100 * i)));
			}

			// Sets the initial position of the player.
			for (int i = 0; i < 3; i++)
			{
				m_player->m_playerCar[i]->m_position = m_nodes1.at(0)->m_position;
				m_player->m_playerCar[i]->m_rotation = 45.0f;
			}

			// Initialises the startline so that is looks right in the game world.
			m_startlineSprite.setPosition(m_checkpoints1.at(0)->m_position);
			m_startlineSprite.setRotation(m_checkpoints1.at(0)->m_rotation);
			m_startlineSprite.setScale(0.1, 0.13);

			// Initialises each checkpoint as a rectangle so it can be represented in the game world.
			for (int i = 0; i < m_checkpoints1.size(); i++)
			{
				sf::RectangleShape rectangle;
				m_checkpointRectangles1.push_back(std::move(rectangle));
				m_checkpointRectangles1.at(i).setOrigin(CHECKPOINT_WIDTH / 2, CHECKPOINT_HEIGHT / 2);
				m_checkpointRectangles1.at(i).setPosition(m_checkpoints1.at(i)->m_position.x, m_checkpoints1.at(i)->m_position.y);
				m_checkpointRectangles1.at(i).setRotation(m_checkpoints1.at(i)->m_rotation);
				m_checkpointRectangles1.at(i).setSize(sf::Vector2f(CHECKPOINT_WIDTH, CHECKPOINT_HEIGHT));
				m_checkpointRectangles1.at(i).setFillColor(sf::Color(255, 0, 0, 126));
			}
		}
		
		// Resets inital values in case of it not being the players first race.
		for (int i = 0; i < MAX_AI; i++)
		{
			aiCars[i]->setFinishTime(40000);
		}
		m_currentTime = sf::Time::Zero;
		m_currentCheckpoint = 0;
		m_callOnce = false;
	}

	m_currentCar = m_player->m_currentCar;	// Sets what car the player is in.
	m_followPlayer.setCenter(m_player->m_playerCar[m_currentCar]->m_position);	// Sets the camera to the players position.
	checkCheckpoint();	// Checks what checkpoint the player is heading to.

	m_player->update(dt, &controller);
	m_whichMap = whichMap;

	m_currentTime += TIME_PER_UPDATE;	//updates the m_currenttime variable via the TIME_PER_UPDATE variable

	if (m_controller->m_currentState.Start)	// Allows the player to leave the race by pushing the start button.
	{
		m_callOnce = true;
		*m_state = GameState::MENU_STATE;
	}

	// Checks each ai if it is heading towards another car sprite.
	for (int i = 0; i < MAX_AI; i++)
	{
		aiCars[i]->update(dt, m_player->m_playerCar[m_currentCar]->m_carSprite);

		for (int j = 0; j < MAX_AI; j++)
		{
			if (j != i)
			{
				aiCars[i]->update(dt, aiCars[j]->m_carSprite); 
			}
		}
	}

	if (!m_whichMap)	// Grassy Plains
	{
		// Checks if the player is on the road.
		for (std::unique_ptr<RoadTile> &roadTile : m_roadTiles1)
		{
			roadTile->whichTile(m_player->m_playerCar[m_currentCar]->m_position);
			if (roadTile->carIsOn)
			{
				m_slowDown = roadTile->checkOffRoad(m_player->m_playerCar[m_currentCar]->m_position, m_whichMap);
			}
		}
	}

	if (m_whichMap)	// Icy Wasteland.
	{
		// Checks if the player is on the road.
		for (std::unique_ptr<RoadTile> &roadTile : m_roadTiles2)
		{
			roadTile->whichTile(m_player->m_playerCar[m_currentCar]->m_position);
			if (roadTile->carIsOn)
			{
				m_slowDown = roadTile->checkOffRoad(m_player->m_playerCar[m_currentCar]->m_position, m_whichMap);
			}
		}
	}
	m_player->m_playerCar[m_currentCar]->slowCar(m_slowDown);	// Slows down the player car if it is off road.
	
	m_time = m_currentTime.asSeconds();	// Updates the game time.
	
	// Stringstream variable and string variable for time
	std::stringstream ss;
	ss << "Time: " << m_time;

	// Stringstream variable and string variable for position
	std::stringstream ssPos;
	ssPos << "Checkpoint: " << m_currentCheckpoint;

	// Updating label position based on viewport
	m_labels[0]->updatePosition(m_followPlayer.getCenter().x - 165, m_followPlayer.getCenter().y - 140);
	m_labels[1]->updatePosition(m_followPlayer.getCenter().x + 130, m_followPlayer.getCenter().y - 140);

	// Updating the labels text based on time and position
	m_labels[1]->updateText(ss);
	m_labels[0]->updateText(ssPos);
}

void Play::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::White);
	if (!m_callOnce)	// Only called once the level has initialized.
	{
		if (!m_whichMap)	// Grassy Plains.
		{
			for (std::unique_ptr<RoadTile> &roadTile : m_roadTiles1)
			{
				// Checks what roadTiles are visible and only draws those.
				if (roadTile->culling(m_player->m_playerCar[m_currentCar]->m_position, window))
				{
					roadTile->render(window);
				}
			}

			// Renders the checkpoint the player is heading for.
			window.draw(m_checkpointRectangles1.at(m_currentCheckpoint));
		}
		else if (m_whichMap)	// Icy Wasteland.
		{
			for (std::unique_ptr<RoadTile> &roadTile : m_roadTiles2)
			{
				// Checks what roadTiles are visible and only draws those.
				if (roadTile->culling(m_player->m_playerCar[m_currentCar]->m_position, window))
				{
					roadTile->render(window);
				}
			}
			
			// Renders the checkpoint the player is heading for.
			window.draw(m_checkpointRectangles2.at(m_currentCheckpoint));
		}

		// Renders the startline.
		window.draw(m_startlineSprite);

		// Renders the player car.
		m_player->render(window);
	
		// Rendering the labels
		m_labels[0]->render(window);
		m_labels[1]->render(window);

		// Renders all the ai cars
		for (int i = 0; i < MAX_AI; i++)
		{
			aiCars[i]->render(window);
		}

		m_followPlayer.setCenter(m_player->m_playerCar[m_currentCar]->m_position);
		window.setView(m_followPlayer);
	}
}

void Play::generateRoad()
{
	int i = 0;
	for (Road1Data const &road : m_level.m_roads1)
	{
		std::unique_ptr<RoadTile> roadTile(new RoadTile(road.m_fileID, road.m_position, road.m_rotation, road.m_scale, i, road.m_fileName));
		m_roadTiles1.push_back(std::move(roadTile));
		i++;
	}


	int e = 0;
	for (Road2Data const &road : m_level.m_roads2)
	{
		std::unique_ptr<RoadTile> roadTile(new RoadTile(road.m_fileID, road.m_position, road.m_rotation, road.m_scale, e, road.m_fileName));
		m_roadTiles2.push_back(std::move(roadTile));
		e++;
	}
	
}

void Play::generateNode()
{
	for (Node1Data const &node : m_level.m_nodes1)
	{
		std::unique_ptr<Node> node(new Node(node.m_number, node.m_position));
		m_nodes1.push_back(std::move(node));
	}

	for (Node2Data const &node : m_level.m_nodes2)
	{
		std::unique_ptr<Node> node(new Node(node.m_number, node.m_position));
		m_nodes2.push_back(std::move(node));
	}
}

void Play::generateCheckpoint()
{
	for (Checkpoint1Data const &checkpoint : m_level.m_checkpoints1)
	{
		std::unique_ptr<Checkpoint> checkpoint(new Checkpoint(checkpoint.m_number, checkpoint.m_position, checkpoint.m_rotation));
		m_checkpoints1.push_back(std::move(checkpoint));
	}

	for (Checkpoint2Data const &checkpoint : m_level.m_checkpoints2)
	{
		std::unique_ptr<Checkpoint> checkpoint(new Checkpoint(checkpoint.m_number, checkpoint.m_position, checkpoint.m_rotation));
		m_checkpoints2.push_back(std::move(checkpoint));
	}
}

void Play::checkCheckpoint()
{
	if (m_whichMap)
	{
		// Checks if the player sprite intersects the bounding rectangle of the current checkpoints rectangle.
		if (m_player->m_playerCar[m_currentCar]->m_carSprite.getGlobalBounds().intersects(m_checkpointRectangles2.at(m_currentCheckpoint).getGlobalBounds()))
		{
			m_currentCheckpoint++;

			if (m_currentCheckpoint >= m_checkpoints2.size())
			{
				m_currentCheckpoint = 0;
				if (m_lap < MAX_LAPS)
				{
					m_lap++;
				}
				if (m_lap == MAX_LAPS)
				{
					// Resets the race conditions.
					m_playerTime = m_time;
					m_callOnce = true;
					finishingPos();
				}
			}
		}

		// Checks if the ai cars have finished the race.
		for (int i = 0; i < MAX_AI; i++)
		{
			if (aiCars[i]->m_currentNode >= m_nodes2.size() - 1)
			{
				aiCars[i]->setFinishTime(m_time);
			}
		}
	}
	
	else if (!m_whichMap)	// 
	{
		// Checks if the player sprite intersects the bounding rectangle of the current checkpoints rectangle.
		if (m_player->m_playerCar[m_currentCar]->m_carSprite.getGlobalBounds().intersects(m_checkpointRectangles1.at(m_currentCheckpoint).getGlobalBounds()))
		{
			m_currentCheckpoint++;
		
			if (m_currentCheckpoint >= (m_checkpoints1.size()))
			{
				m_currentCheckpoint = 0;
				if (m_lap < MAX_LAPS)
				{
					m_lap++;
				}
				if (m_lap == MAX_LAPS)
				{
					// Resets the race conditions.
					m_playerTime = m_time;
					m_callOnce = true;
					finishingPos();
				}
			}
		}

		// Checks if the ai cars have finished the race
		for (int i = 0; i < MAX_AI; i++)
		{

			if (aiCars[i]->m_currentNode >= m_nodes1.size() - 1)
			{	
				aiCars[i]->setFinishTime(m_time);
			}
		}
	}
}

void Play::finishingPos()
{
	if (m_time < aiCars[0]->m_finishTime && m_time < aiCars[1]->m_finishTime)	// If the player time is less than both ai than the player has won.
	{
		m_racePosition = 1;
		m_player->m_currency += 2;

	}
	else if (m_time > aiCars[0]->m_finishTime && m_time > aiCars[1]->m_finishTime)	// If the player time is more than both ai than the player has lost.
	{
		m_racePosition = 3;
	}
	else	// The player has come second.
	{
		m_racePosition = 2;
		m_player->m_currency += 1;
	}

	*m_state = GameState::END_STATE;	// Change to EndScreen.cpp.
}