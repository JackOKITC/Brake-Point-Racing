#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include <SFML/System/Vector2.hpp>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "yaml-cpp\yaml.h"

struct RoadData
{
	std::string m_fileName;
	sf::Vector2f m_position;
	double m_rotation;
	double m_scale;
};

struct LevelData
{
	std::vector<RoadData> m_roads;
};

struct NodeData
{
	int m_number;
	sf::Vector2f m_position;
};

class LevelLoader
{
public:
	LevelLoader();

	static bool load(int levelNo, LevelData& level);
};
#endif // !LEVELLOADER_H

