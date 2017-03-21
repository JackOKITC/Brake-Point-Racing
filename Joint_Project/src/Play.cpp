#include "Play.h"

Play::Play()
{
}

Play::Play(GameState *gameState, bool whichMap) :
	m_whichMap(whichMap)
{
	m_state = gameState;	

	int currentLevel = 1;
	if (!LevelLoader::load(currentLevel, m_level))
	{
		std::cout << "Level not loaded" << std::endl;
	}

	ResourceManager::instance().loadData(m_level);
	generateNode();
	generateRoad();
	
	car = new Car();

	for (int i = 0; i < MAX_AI; i++)
	{
		aiCars[i] = new Ai(m_nodes1, sf::Vector2f(0,0));
	}

	m_followPlayer.setSize(450, 300); //in constructor

}

Play::~Play()
{
}

void Play::update(Xbox360Controller & controller, double dt, bool whichMap)
{

	if (m_callOnce)
	{
		if (whichMap)
		{
			for (int i = 0; i < MAX_AI; i++)
			{
				aiCars[i] = new Ai(m_nodes2, sf::Vector2f(250, 250));
			}
			car = new Car(sf::Vector2f(250, 250));
		}
		if (!whichMap)
		{
			for (int i = 0; i < MAX_AI; i++)
			{
				aiCars[i] = new Ai(m_nodes1, sf::Vector2f(250, 250));
			}
			car = new Car(sf::Vector2f(250, 250));
		}
		m_callOnce = false;
	}
	m_followPlayer.setCenter(car->m_position);
	car->update(controller, dt);
	m_whichMap = whichMap;


	for (int i = 0; i < MAX_AI; i++)
	{
		aiCars[i]->update(dt);
	}
	if (!m_whichMap)
	{
		for (std::unique_ptr<RoadTile> &roadTile : m_roadTiles1)
		{
			roadTile->whichTile(car->m_position);
			if (roadTile->carIsOn)
			{
				m_slowDown = roadTile->checkOffRoad(car->m_position, m_whichMap);
			}
		}
	}

	if (m_whichMap)
	{

		for (std::unique_ptr<RoadTile> &roadTile : m_roadTiles2)
		{
			roadTile->whichTile(car->m_position);
			if (roadTile->carIsOn)
			{
				m_slowDown = roadTile->checkOffRoad(car->m_position, m_whichMap);
			}
		}
	}

	car->slowCar(m_slowDown);
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
				if (roadTile->culling(car->m_position, window))
				{
					roadTile->render(window);
				}
			}
		}

		if (m_whichMap)
		{
			for (std::unique_ptr<RoadTile> &roadTile : m_roadTiles2)
			{
				if (roadTile->culling(car->m_position, window))
				{
					roadTile->render(window);
				}
			}
		}

		car->render(window);

		for (int i = 0; i < MAX_AI; i++)
		{
			aiCars[i]->render(window);
		}

		m_followPlayer.setCenter(car->m_position);
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

