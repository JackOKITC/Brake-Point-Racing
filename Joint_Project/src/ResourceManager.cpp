#include "ResouceManager.h"

ResourceManager g_manager;

ResourceManager::ResourceManager()
{

}

void ResourceManager::loadData(LevelData &level)
{
	try
	{
		for (RoadData data : level.m_roads)
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
	}

	catch (thor::ResourceLoadingException& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}