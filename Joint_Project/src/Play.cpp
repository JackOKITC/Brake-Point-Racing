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
	generateCheckpoint();

	car = new Car(false, m_nodes, m_checkpoints);

	for (int i = 0; i < MAX_AI; i++)
	{
		aiCars[i] = new Car(true, m_nodes, m_checkpoints);
	}

	m_followPlayer.setCenter(car->m_position);
	m_followPlayer.setSize(450, 300); //in constructor

}

Play::~Play()
{
}

void Play::update(Xbox360Controller & controller, double dt, bool whichMap)
{
	car->update(controller, dt);
	m_whichMap = whichMap;


	for (int i = 0; i < MAX_AI; i++)
	{
		aiCars[i]->update(controller, dt);
	}
	if (!m_whichMap)
	{
		for (std::unique_ptr<RoadTile> &roadTile : m_roadTiles1)
		{
			roadTile->whichTile(car->m_position);
			if (roadTile->carIsOn)
			{
				roadTile->checkOffRoad(car->m_position);
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
				roadTile->checkOffRoad(car->m_position);
			}
		}
	}
}

void Play::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::White);
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
	for (NodeData const &node : m_level.m_nodes)
	{
		std::unique_ptr<Node> node(new Node(node.m_number, node.m_position));
		m_nodes.push_back(std::move(node));
	}
}

void Play::generateCheckpoint()
{
	for (CheckpointData const &checkpoint : m_level.m_checkpoints)
	{
		std::unique_ptr<Checkpoint> checkpoint(new Checkpoint(checkpoint.m_number, checkpoint.m_position));
		m_checkpoints.push_back(std::move(checkpoint));
	}
}