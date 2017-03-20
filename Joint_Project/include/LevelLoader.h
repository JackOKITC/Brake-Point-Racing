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
	std::string m_fileID;
	sf::Vector2f m_position;
	double m_rotation;
	double m_scale;
};

struct BackgroundData
{
	std::string m_fileName;
	std::string m_fileID;
};

struct CarData
{
	std::string m_fileName;
	std::string m_fileID;
};

struct NodeData
{
	int m_number;
	sf::Vector2f m_position;
};

struct CheckpointData
{
	int m_number;
	sf::Vector2f m_position;
};

struct AudioData
{
	std::string m_fileName;
	std::string m_fileID;
};

struct LevelData
{
	std::vector<CarData> m_car;
	std::vector<RoadData> m_roads;
	std::vector<BackgroundData> m_bg;
	std::vector<NodeData> m_nodes;
	std::vector<CheckpointData> m_checkpoints;
	std::vector<AudioData> m_sound;
};

class LevelLoader
{
public:
	LevelLoader();

	static bool load(int levelNo, LevelData& level);
};
#endif // !LEVELLOADER_H

