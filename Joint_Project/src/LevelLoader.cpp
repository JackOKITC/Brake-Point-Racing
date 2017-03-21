#include "LevelLoader.h"

void operator >> (const YAML::Node& roadNode, Road1Data& road)
{
	road.m_fileName = roadNode["file"].as<std::string>();
	road.m_fileID = roadNode["ID"].as<std::string>();
	road.m_position.x = roadNode["position"]["x"].as<float>();
	road.m_position.y= roadNode["position"]["y"].as<float>();
	road.m_rotation = roadNode["rotation"].as<double>();
	road.m_scale = roadNode["scale"].as<double>();
}

void operator >> (const YAML::Node& roadNode, Road2Data& road)
{
	road.m_fileName = roadNode["file"].as<std::string>();
	road.m_fileID = roadNode["ID"].as<std::string>();
	road.m_position.x = roadNode["position"]["x"].as<float>();
	road.m_position.y = roadNode["position"]["y"].as<float>();
	road.m_rotation = roadNode["rotation"].as<double>();
	road.m_scale = roadNode["scale"].as<double>();
}

void operator >> (const YAML::Node& audioNode, AudioData& audio)
{
	audio.m_fileName = audioNode["file"].as<std::string>();
	audio.m_fileID = audioNode["ID"].as<std::string>();
}

void operator >> (const YAML::Node& bgNode, BackgroundData& bg)
{
	bg.m_fileName = bgNode["file"].as<std::string>();
	bg.m_fileID = bgNode["ID"].as<std::string>();
}

void operator >> (const YAML::Node& carNode, CarData& car)
{
	car.m_fileName = carNode["file"].as<std::string>();
	car.m_fileID = carNode["ID"].as<std::string>();
}

void operator >> (const YAML::Node& upgradeNode, UpgradeData& upgrade)
{
	upgrade.m_fileName = upgradeNode["file"].as<std::string>();
	upgrade.m_fileID = upgradeNode["ID"].as<std::string>();
}

void operator >> (const YAML::Node& nodeNode, Node1Data& node)
{
	node.m_number = nodeNode["number"].as<int>();
	node.m_position.x = nodeNode["position"]["x"].as<float>();
	node.m_position.y = nodeNode["position"]["y"].as<float>();
}

void operator >> (const YAML::Node& nodeNode, Node2Data& node)
{
	node.m_number = nodeNode["number"].as<int>();
	node.m_position.x = nodeNode["position"]["x"].as<float>();
	node.m_position.y = nodeNode["position"]["y"].as<float>();
}

void operator >> (const YAML::Node& checkpointNode, Checkpoint1Data& checkpoint)
{
	checkpoint.m_number = checkpointNode["number"].as<int>();
	checkpoint.m_position.x = checkpointNode["position"]["x"].as<float>();
	checkpoint.m_position.y = checkpointNode["position"]["y"].as<float>();
	checkpoint.m_rotation = checkpointNode["rotation"].as<double>();
}

void operator >> (const YAML::Node& checkpointNode, Checkpoint2Data& checkpoint)
{
	checkpoint.m_number = checkpointNode["number"].as<int>();
	checkpoint.m_position.x = checkpointNode["position"]["x"].as<float>();
	checkpoint.m_position.y = checkpointNode["position"]["y"].as<float>();
	checkpoint.m_rotation = checkpointNode["rotation"].as<double>();
}

void operator >> (const YAML::Node& levelNode, LevelData& level)
{
	// load in the data from the yaml file to the level load system
	const YAML::Node& roadsNode1 = levelNode["tile1"].as<YAML::Node>();
	for (unsigned i = 0; i < roadsNode1.size(); i++)
	{
		Road1Data road;
		roadsNode1[i] >> road;
		level.m_roads1.push_back(road);
	}

	const YAML::Node& roadsNode2 = levelNode["tile2"].as<YAML::Node>();
	for (unsigned i = 0; i < roadsNode2.size(); i++)
	{
		Road2Data road;
		roadsNode2[i] >> road;
		level.m_roads2.push_back(road);
	}

	const YAML::Node& bgNode = levelNode["background"].as<YAML::Node>();
	for (unsigned i = 0; i < bgNode.size(); i++)
	{
		BackgroundData bg;
		bgNode[i] >> bg;
		level.m_bg.push_back(bg);
	}

	const YAML::Node& carNode = levelNode["car"].as<YAML::Node>();
	for (unsigned i = 0; i < carNode.size(); i++)
	{
		CarData car;
		carNode[i] >> car;
		level.m_car.push_back(car);
	}

	const YAML::Node& upgradeNode = levelNode["upgrade"].as<YAML::Node>();
	for (unsigned i = 0; i < upgradeNode.size(); i++)
	{
		UpgradeData upgrade;
		upgradeNode[i] >> upgrade;
		level.m_upgrades.push_back(upgrade);
	}

	const YAML::Node& nodesNode1 = levelNode["node1"].as<YAML::Node>();
	for (unsigned i = 0; i < nodesNode1.size(); i++)
	{
		Node1Data node;
		nodesNode1[i] >> node;
		level.m_nodes1.push_back(node);
	}

	const YAML::Node& nodesNode2 = levelNode["node2"].as<YAML::Node>();
	for (unsigned i = 0; i < nodesNode2.size(); i++)
	{
		Node2Data node;
		nodesNode2[i] >> node;
		level.m_nodes2.push_back(node);
	}
	
	const YAML::Node& checkpointNode1 = levelNode["checkpoint1"].as<YAML::Node>();
	for (unsigned i = 0; i < checkpointNode1.size(); i++)
	{
		Checkpoint1Data checkpoint;
		checkpointNode1[i] >> checkpoint;
		level.m_checkpoints1.push_back(checkpoint);
	}

	const YAML::Node& checkpointNode2 = levelNode["checkpoint2"].as<YAML::Node>();
	for (unsigned i = 0; i < checkpointNode2.size(); i++)
	{
		Checkpoint2Data checkpoint;
		checkpointNode2[i] >> checkpoint;
		level.m_checkpoints2.push_back(checkpoint);
	}

	const YAML::Node& audioNode = levelNode["audio"].as<YAML::Node>();
	for (unsigned i = 0; i < audioNode.size(); i++)
	{
		AudioData audio;
		audioNode[i] >> audio;
		level.m_sound.push_back(audio);
	}
}



LevelLoader::LevelLoader()
{
	
}

bool LevelLoader::load(int levelNo, LevelData& level)
{
	
	// load the levels 
	std::stringstream ss;
	ss << "resources/levels/level";
	ss << levelNo;
	ss << ".yaml";

	try 
	{
		YAML::Node base = YAML::LoadFile(ss.str());
		if (base.IsNull())
		{
			std::string message("file:" + ss.str() + "not found");
			throw std::exception(message.c_str());
		}
		base >> level;
	}

	catch (YAML::ParserException& e)
	{
		std::cout << e.what() << "\n";
		return false;
	}

	catch (std::exception& e)
	{
		std::cout << e.what() << "\n";
		return false;
	}

	return true;
}