#include "Player.h"

Player::Player()
{
}

Player::Player(LevelData &level)
{
	for (int i = 0; i < 3; i++)
	{
		m_temp = ResourceManager::instance().m_holder["Bus" + std::to_string(i)];
		m_playerCar[i] = new Car(m_temp, level.m_car.at(i).brake, level.m_car.at(i).handling, level.m_car.at(i).acceleration);
	}

	m_currentCar = 0;
}

Player::~Player()
{
}

void Player::update(double & dt, Xbox360Controller * controller)
{
	m_playerCar[m_currentCar]->update(*controller, dt);
}

void Player::render(sf::RenderWindow & window)
{
	m_playerCar[m_currentCar]->render(window);
}
