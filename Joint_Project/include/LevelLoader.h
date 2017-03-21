#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include <SFML/System/Vector2.hpp>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "yaml-cpp\yaml.h"

struct Road1Data
{
	std::string m_fileName;
	std::string m_fileID;
	sf::Vector2f m_position;
	double m_rotation;
	double m_scale;
};

struct Road2Data
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

struct UpgradeData
{
	std::string m_fileName;
	std::string m_fileID;
};

struct CarData
{
	std::string m_fileName;
	std::string m_fileID;
};

struct Node1Data
{
	int m_number;
	sf::Vector2f m_position;
};

struct Node2Data
{
	int m_number;
	sf::Vector2f m_position;
};

struct Checkpoint1Data
{
	int m_number;
	sf::Vector2f m_position;
	double m_rotation;
};

struct Checkpoint2Data
{
	int m_number;
	sf::Vector2f m_position;
	double m_rotation;
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
	std::vector<Road1Data> m_roads1;
	std::vector<Road2Data> m_roads2;
	std::vector<BackgroundData> m_bg;
<<<<<<< HEAD
	std::vector<Node1Data> m_nodes1;
	std::vector<Node2Data> m_nodes2;
	std::vector<Checkpoint1Data> m_checkpoints1;
	std::vector<Checkpoint2Data> m_checkpoints2;
=======
	std::vector<NodeData> m_nodes;
	std::vector<CheckpointData> m_checkpoints;
>>>>>>> cf1e810e1d5d0f95e85ee06315d9782f7c49ebfe
	std::vector<AudioData> m_sound;
	std::vector<UpgradeData> m_upgrades;
};

class LevelLoader
{
public:
	LevelLoader();

	static bool load(int levelNo, LevelData& level);
};
#endif // !LEVELLOADER_H

