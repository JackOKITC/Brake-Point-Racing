#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <Thor\Resources.hpp>
#include <iostream>
#include "LevelLoader.h"
#include <SFML\Graphics.hpp>

class ResourceManager
{
public:
	ResourceManager();
	void loadData(LevelData &level);
	thor::ResourceHolder<sf::Texture, std::string> m_holder;

private: 
	
};

extern ResourceManager g_manager;
#endif // !RESOURCEMANAGER_H

