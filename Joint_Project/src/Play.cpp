#include "Play.h"

Play::Play()
{
}

Play::Play(GameState *gameState)
{
	m_state = gameState;	

	int currentLevel = 1;
	if (!LevelLoader::load(currentLevel, m_level))
	{
		std::cout << "Level not loaded" << std::endl;
	}
	

	ResourceManager::instance().loadData(m_level);
	generateRoad();
	generateNode();

	car = new Car(false, m_nodes);

	for (int i = 0; i < MAX_AI; i++)
	{
		aiCars[i] = new Car(true, m_nodes);
	}

	m_followPlayer.setCenter(car->m_position);
	m_followPlayer.setSize(450, 300); //in constructor

}

Play::~Play()
{
}

void Play::update(Xbox360Controller & controller, double dt)
{
	car->update(controller, dt);

	for (int i = 0; i < MAX_AI; i++)
	{
		aiCars[i]->update(controller, dt);
	}
	
	for (std::unique_ptr<RoadTile> &roadTile : m_roadTiles)
	{
		roadTile->whichTile(car->m_position);
		if (roadTile->carIsOn)
		{
			roadTile->checkOffRoad(car->m_position);
		}
	}
}

void Play::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::White);
	for (std::unique_ptr<RoadTile> &roadTile : m_roadTiles)
	{
		if (roadTile->culling(car->m_position, window))
		{
			roadTile->render(window);
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
	for (RoadData const &road : m_level.m_roads)
	{
		std::unique_ptr<RoadTile> roadTile(new RoadTile(road.m_fileID, road.m_position, road.m_rotation, road.m_scale, i, road.m_fileName));
		m_roadTiles.push_back(std::move(roadTile));
		i++;
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