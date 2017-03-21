#include "Play.h"

Play::Play()	
{
}

Play::Play(GameState *gameState, bool whichMap, Player *player, LevelData *level) :
	m_whichMap(whichMap)

{
	m_state = gameState;
	m_level = *level;
	m_player = player;
	
	int currentLevel = 1;
	if (!LevelLoader::load(currentLevel, m_level))
	{
		std::cout << "Level not loaded" << std::endl;
	}
	
	ResourceManager::instance().loadData(m_level);

	generateNode();
	generateRoad();
	generateCheckpoint();


	m_currentCheckpoint = 0;
	m_lap = 0;
	m_followPlayer.setSize(450, 300); //in constructor
	
	m_labels = new Label(&time, &m_font, &sf::Vector2f(0, 0), 10, sf::Color(0, 255, 0));
	m_timeLabel = new Label(&time, &m_font, &sf::Vector2f(0, 0), 10, sf::Color(0, 255, 0));

}

Play::~Play()
{
}

void Play::update(Xbox360Controller & controller, double dt, bool whichMap)
{


	if (m_callOnce)
	{
		m_currentCar = m_player->m_currentCar;
		if (whichMap)
		{
			for (int i = 0; i < MAX_AI; i++)
			{
				aiCars[i] = new Ai(m_nodes2, m_nodes2.at(0)->m_position);
			}

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
		if (!whichMap)
		{
			for (int i = 0; i < MAX_AI; i++)
			{
				aiCars[i] = new Ai(m_nodes1, m_nodes1.at(0)->m_position);
			}
			

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
		m_callOnce = false;
	}
	m_followPlayer.setCenter(m_player->m_playerCar[m_currentCar]->m_position);
	m_player->update(dt, &controller);
	m_whichMap = whichMap;

	currentTime += TIME_PER_UPDATE;

	if (m_controller->m_currentState.Start)
	{
		*m_state = GameState::MENU_STATE;
	}


	for (int i = 0; i < MAX_AI; i++)
	{
		aiCars[i]->update(dt);
	}

	if (!m_whichMap)
	{
		for (std::unique_ptr<RoadTile> &roadTile : m_roadTiles1)
		{
			roadTile->whichTile(m_player->m_playerCar[m_currentCar]->m_position);
			if (roadTile->carIsOn)
			{
				m_slowDown = roadTile->checkOffRoad(m_player->m_playerCar[m_currentCar]->m_position, m_whichMap);
			}
		}
	}

	if (m_whichMap)
	{
		for (std::unique_ptr<RoadTile> &roadTile : m_roadTiles2)
		{
			roadTile->whichTile(m_player->m_playerCar[m_currentCar]->m_position);
			if (roadTile->carIsOn)
			{
				m_slowDown = roadTile->checkOffRoad(m_player->m_playerCar[m_currentCar]->m_position, m_whichMap);
			}
		}
	}
	m_player->m_playerCar[m_currentCar]->slowCar(m_slowDown);

	for (int i = 0; i < LABEL_COUNT; i++)
	{
		m_labels[i] = new Label(&m_strings[i], &m_font, &sf::Vector2f(m_followPlayer.getCenter() - sf::Vector2f(175, 120 - (i* 10))), 10, sf::Color(0, 255, 0));
	}
}

void Play::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::White);
	if (!m_callOnce)
	{
		if (!m_whichMap)
		{
			for (std::unique_ptr<RoadTile> &roadTile : m_roadTiles1)
			{
				if (roadTile->culling(m_player->m_playerCar[m_currentCar]->m_position, window))
				{
					roadTile->render(window);
				}
			}
			window.draw(m_checkpointRectangles1.at(m_currentCheckpoint));
		}
		else if (m_whichMap)
		{
			for (std::unique_ptr<RoadTile> &roadTile : m_roadTiles2)
			{
				if (roadTile->culling(m_player->m_playerCar[m_currentCar]->m_position, window))
				{
					roadTile->render(window);
				}
			}
			window.draw(m_checkpointRectangles2.at(m_currentCheckpoint));
		}


	m_player->render(window);

	for (int i = 0; i < LABEL_COUNT; i++)
	{
		m_labels[i]->render(window);
	}

	car->render(window);



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
		if (m_player->m_playerCar[m_currentCar]->m_carSprite.getGlobalBounds().intersects(m_checkpointRectangles2.at(m_currentCheckpoint).getGlobalBounds()))
		{
			m_currentCheckpoint++;
			std::cout << m_currentCheckpoint << std::endl;

			if (m_currentCheckpoint >= m_checkpoints2.size() || m_currentCheckpoint > 35)
			{
				m_currentCheckpoint = 0;
				if (m_lap < MAX_LAPS)
				{
					m_lap++;
				}
				if (m_lap == MAX_LAPS)
				{
					*m_state = GameState::END_STATE;
				}
			}
		}
	}
	else if (!m_whichMap)
	{
		if (m_player->m_playerCar[m_currentCar]->m_carSprite.getGlobalBounds().intersects(m_checkpointRectangles1.at(m_currentCheckpoint).getGlobalBounds()))
		{
			m_currentCheckpoint++;
			std::cout << m_currentCheckpoint << std::endl;

		
			if (m_currentCheckpoint >= (m_checkpoints1.size()) || m_currentCheckpoint > 25)
			{
				m_currentCheckpoint = 0;
				if (m_lap < MAX_LAPS)
				{
					m_lap++;
				}
				if (m_lap == MAX_LAPS)
				{
					*m_state = GameState::END_STATE;
				}
			}
		}
	}
}
