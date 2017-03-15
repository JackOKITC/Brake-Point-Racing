#include "Play.h"

Play::Play()
{
}

Play::Play(GameState *gameState)
{
	m_state = gameState;

	if (!m_backgroundTex.loadFromFile(".//resources//images//car_parts//all.png"))
	{
		std::cout << "Problem loading Texture for splash screen";
	}
	m_backgroundSprite.setTexture(m_backgroundTex);

	int currentLevel = 1;
	if (!LevelLoader::load(currentLevel, m_level))
	{
		std::cout << "Level not loaded" << std::endl;
	}
	

	ResourceManager::instance().loadData(m_level);
	generateRoad();
	generateNode();

	car = new Car();

	for (int i = 0; i < MAX_AI; i++)
	{
		aiCars[i] = new Ai(m_nodes);
	}

	m_followPlayer.setCenter(car->m_position);
	m_followPlayer.setSize(900, 600); //in constructor

}

Play::~Play()
{
}

void Play::update(Xbox360Controller & controller, double dt)
{
	car->update(controller, dt);

	for (int i = 0; i < MAX_AI; i++)
	{
		aiCars[i]->update(dt);
	}
	
}

void Play::render(sf::RenderWindow & window)
{
	window.clear(sf::Color(1, 165, 18));

		for (std::unique_ptr<RoadTile> &roadTile : m_roadTiles)
		{
			if (roadTile->culling(car->m_position))
			{
				roadTile->render(window);
			}
		}

	car->render(window);

	//for (int i = 0; i < MAX_AI; i++)
	//{
	//	aiCars[i]->render(window);
	//}

	m_followPlayer.setCenter(car->m_position);
	window.setView(m_followPlayer);
}

void Play::generateRoad()
{
	for (RoadData const &road : m_level.m_roads)
	{
		std::unique_ptr<RoadTile> roadTile(new RoadTile(road.m_fileID, road.m_position, road.m_rotation, road.m_scale));
		m_roadTiles.push_back(std::move(roadTile));
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