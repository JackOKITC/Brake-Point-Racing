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

	generateRoad();

	car = new Car();

	followPlayer.setCenter(car->m_position);
	followPlayer.setSize(900, 600); //in constructor
}

Play::~Play()
{
}

void Play::update(Xbox360Controller & controller, double dt)
{
	car->update(controller, dt);
}

void Play::render(sf::RenderWindow & window)
{
	window.clear(sf::Color(1, 165, 18));
	for (RoadData const &road : m_level.m_roads)
	{
		for (std::unique_ptr<RoadTile> &roadTile : m_roadTiles)
		{
			roadTile->render(window);
		}
	}
	car->render(window);

	followPlayer.setCenter(car->m_position);
	window.setView(followPlayer);
}

void Play::generateRoad()
{
	for (RoadData const &road : m_level.m_roads)
	{
		std::unique_ptr<RoadTile> roadTile(new RoadTile(road.m_fileName, road.m_position, road.m_rotation, road.m_scale));
		m_roadTiles.push_back(std::move(roadTile));
	}
}