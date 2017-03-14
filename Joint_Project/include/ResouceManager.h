#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <Thor\Resources.hpp>
#include <iostream>
#include "LevelLoader.h"
#include <SFML\Graphics.hpp>

class ResourceManager
{
public:
	static ResourceManager& instance() { return m_instance; }
	void loadData(LevelData &level);
	thor::ResourceHolder<sf::Texture, std::string> m_holder;

private: 
	ResourceManager();
	static ResourceManager m_instance;
};


#endif // !RESOURCEMANAGER_H

