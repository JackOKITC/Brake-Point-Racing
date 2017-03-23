#include "Play.h"

Play::Play()	
{
}

Play::Play(sf::Font & font, GameState *gameState, bool whichMap, Player *player, LevelData *level) :
	m_whichMap(whichMap),
	m_font(font)
{
	m_state = gameState;
	m_level = *level;
	m_player = player;

	m_state = gameState;	
	m_time = 0.0;

	generateNode();
	generateRoad();
	generateCheckpoint();

	m_currentCheckpoint = 0;
	m_lap = 0;
	m_followPlayer.setSize(450, 300); //in constructor

	m_labels[0] = new Label(&m_strings[1], &m_font, &sf::Vector2f(0, 0), 15, sf::Color(0, 255, 0));
	m_labels[1] = new Label(&m_strings[0], &m_font, &sf::Vector2f(0, 0), 15, sf::Color(0, 255, 0));

	/*m_labels = new Label(&time, &m_font, &sf::Vector2f(0, 0), 10, sf::Color(0, 255, 0));
	m_timeLabel = new Label(&time, &m_font, &sf::Vector2f(0, 0), 10, sf::Color(0, 255, 0));*/

}

Play::~Play()
{
}

void Play::update(Xbox360Controller & controller, double dt, bool whichMap)
{

	m_controller = &controller;

	m_whichMap = whichMap;

	if (m_callOnce)
	{
		m_currentCar = m_player->m_currentCar;
		if (whichMap)
		{
			for (int i = 0; i < MAX_AI; i++)
			{
				aiCars[i] = new Ai(m_nodes2, sf::Vector2f(m_nodes2.at(0)->m_position.x - (20 * i), m_nodes2.at(0)->m_position.y + (20 * i)));
			}

			m_player->m_playerCar[m_currentCar]->m_position = sf::Vector2f(m_nodes2.at(0)->m_position.x + 10, m_nodes2.at(0)->m_position.y );
			m_player->m_playerCar[m_currentCar]->m_rotation = 0.0f;

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
				aiCars[i] = new Ai(m_nodes1, sf::Vector2f(m_nodes1.at(0)->m_position.x + (30 * i), m_nodes1.at(0)->m_position.y - (100 * i)));
			}
			
			m_player->m_playerCar[m_currentCar]->m_position = m_nodes1.at(0)->m_position;
			m_player->m_playerCar[m_currentCar]->m_rotation = 45.0f;

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
	checkCheckpoint();
	m_player->update(dt, &controller);
	m_whichMap = whichMap;

	currentTime += TIME_PER_UPDATE;

	if (m_controller->m_currentState.Start)
	{
		*m_state = GameState::MENU_STATE;
	}

	/*currentTime += TIME_PER_UPDATE;

	if (m_controller->m_currentState.Start)
	{
		*m_state = GameState::MENU_STATE;
	}

	currentTime += TIME_PER_UPDATE;

	if (m_controller->m_currentState.Start)
	{
		*m_state = GameState::MENU_STATE;
	}*/


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
	
	m_time = currentTime.asSeconds();
	
	std::stringstream ss;
	ss << "Time: " << m_time;

	std::stringstream ssPos;
	ssPos << "Checkpoint: " << m_currentCheckpoint;

	m_labels[0]->updatePosition(m_followPlayer.getCenter().x - 165, m_followPlayer.getCenter().y - 140);
	m_labels[1]->updatePosition(m_followPlayer.getCenter().x + 130, m_followPlayer.getCenter().y - 140);

	m_labels[1]->updateText(ss);
	m_labels[0]->updateText(ssPos);
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
	
	m_labels[0]->render(window);
	m_labels[1]->render(window);

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

			if (m_currentCheckpoint >= m_checkpoints2.size())
			{
				m_currentCheckpoint = 0;
				if (m_lap < MAX_LAPS)
				{
					m_lap++;
				}
				if (m_lap == MAX_LAPS)
				{
					m_callOnce = true;
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

		
			if (m_currentCheckpoint >= (m_checkpoints1.size()))
			{
				m_currentCheckpoint = 0;
				if (m_lap < MAX_LAPS)
				{
					m_lap++;
				}
				if (m_lap == MAX_LAPS)
				{
					m_callOnce = true;
					*m_state = GameState::END_STATE;
				}
			}
		}
	}
}