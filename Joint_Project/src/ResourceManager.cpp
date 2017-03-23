#include "ResourceManager.h"


ResourceManager ResourceManager::m_instance;

ResourceManager::ResourceManager()
{

}

void ResourceManager::loadData(LevelData &level)
{
	// a try-catch for error handling when trying to acquire the data for each object from yaml
	try
	{
		for (Road1Data data : level.m_roads1)
		{
			m_holder.acquire(data.m_fileID, thor::Resources::fromFile<sf::Texture>(data.m_fileName));
		}

		for (Road2Data data : level.m_roads2)
		{
			m_holder.acquire(data.m_fileID, thor::Resources::fromFile<sf::Texture>(data.m_fileName));
		}

		for (BackgroundData data : level.m_bg)
		{
			m_holder.acquire(data.m_fileID, thor::Resources::fromFile<sf::Texture>(data.m_fileName));
		}
		
		for (CarData data : level.m_car)
		{
			m_holder.acquire(data.m_fileID, thor::Resources::fromFile<sf::Texture>(data.m_fileName));
		}
		
		for (AudioData data : level.m_sound)
		{
			m_soundHolder.acquire(data.m_fileID, thor::Resources::fromFile<sf::SoundBuffer>(data.m_fileName));
		}

		for (UpgradeData data : level.m_upgrades)
		{
			m_holder.acquire(data.m_fileID, thor::Resources::fromFile<sf::Texture>(data.m_fileName));
		}

		for (StartlineData data : level.m_start)
		{
			m_holder.acquire(data.m_fileID, thor::Resources::fromFile<sf::Texture>(data.m_fileName));
		}

	}

	catch (thor::ResourceLoadingException& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}

