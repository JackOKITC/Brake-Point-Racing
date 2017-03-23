#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

/// <summary>
/// Author: Peter Daly, Jack O'Kelly
/// Version: 1.0
/// Created: 13/03/2017
/// </summary>

#include <Thor\Resources.hpp>
#include <iostream>
#include "LevelLoader.h"
#include <SFML\Graphics.hpp>
#include "SFML\Audio.hpp"


class ResourceManager
{
public:
	static ResourceManager& instance() { return m_instance; }
	void loadData(LevelData &level);
	thor::ResourceHolder<sf::Texture, std::string> m_holder;	// Resource holder for a texture, to load audio in with thor
	thor::ResourceHolder<sf::SoundBuffer, std::string> m_soundHolder;	// Resource holder for a soundbuffer, to load audio in with thor

private: 
	ResourceManager();
	static ResourceManager m_instance;
};


#endif // !RESOURCEMANAGER_H

