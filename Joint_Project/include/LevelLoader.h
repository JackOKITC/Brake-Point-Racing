#ifndef LEVELLOADER_H
#define LEVELLOADER_H

/// <summary>
/// Author: Peter Daly, John O'Grady, Jack O'Kelly, D.J. O'Leary
/// Version: 1.0
/// Created: 09/03/2017
/// </summary>

#include <SFML/System/Vector2.hpp>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "yaml-cpp\yaml.h"

struct Road1Data
{
	std::string m_fileName;		// The name of the file in the yaml file.
	std::string m_fileID;		// The name the file can be called by.
	sf::Vector2f m_position;	// Its position in the game world.
	double m_rotation;			// Its rotation in the game world.
	double m_scale;				// Its scale in the game world.
};

struct Road2Data
{
	std::string m_fileName;		// The name of the file in the yaml file.
	std::string m_fileID;		// The name the file can be called by.
	sf::Vector2f m_position;	// Its position in the game world.
	double m_rotation;			// Its rotation in the game world.
	double m_scale;				// Its scale in the game world.
};

struct BackgroundData
{
	std::string m_fileName;		// The name of the file in the yaml file.
	std::string m_fileID;		// The name the file can be called by.
};

struct StartlineData
{
	std::string m_fileName;		// The name of the file in the yaml file.
	std::string m_fileID;		// The name the file can be called by.
};

struct UpgradeData
{
	std::string m_fileName;		// The name of the file in the yaml file.
	std::string m_fileID;		// The name the file can be called by.
};

struct CarData
{
	std::string m_fileName;		// The name of the file in the yaml file.
	std::string m_fileID;		// The name the file can be called by.
	int m_brake;				// The brake value of the car.
	int m_handling;				// The handling value of the car.
	int m_acceleration;			// The acceleration value of the car.
};

struct Node1Data
{
	int m_number;				// The number of the node in the yaml file.
	sf::Vector2f m_position;	// Its position in the game world.
};

struct Node2Data
{
	int m_number;				// The number of the node in the yaml file.
	sf::Vector2f m_position;	// Its position in the game world.
};

struct Checkpoint1Data
{
	int m_number;				// The number of the node in the yaml file.
	sf::Vector2f m_position;	// Its position in the game world.
	double m_rotation;			// Its rotation in the game world.
};

struct Checkpoint2Data
{
	int m_number;				// The number of the node in the yaml file.
	sf::Vector2f m_position;	// Its position in the game world.
	double m_rotation;			// Its rotation in the game world.
};

// Stores the music data so it can be loaded in via YAML
struct AudioData
{
	std::string m_fileName;		// The name of the file in the yaml file.
	std::string m_fileID;		// The name the file can be called by.
};

// Stores all the yaml objects in the LevelData struct
struct LevelData
{
	std::vector<CarData> m_car;
	std::vector<Road1Data> m_roads1;
	std::vector<Road2Data> m_roads2;
	std::vector<BackgroundData> m_bg;
	std::vector<Node1Data> m_nodes1;
	std::vector<Node2Data> m_nodes2;
	std::vector<Checkpoint1Data> m_checkpoints1;
	std::vector<Checkpoint2Data> m_checkpoints2;
	std::vector<AudioData> m_sound;
	std::vector<StartlineData> m_start;
	std::vector<UpgradeData> m_upgrades;
};

class LevelLoader
{
public:
	LevelLoader();

	static bool load(int levelNo, LevelData& level);
};
#endif // !LEVELLOADER_H

