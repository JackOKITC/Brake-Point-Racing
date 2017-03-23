#include "Player.h"

Player::Player()
{
}

// player contrsuctor taking level data as an arguement so that it can load in textures and variable
// values from the yaml file on initialisation
Player::Player(LevelData &level)
{
	for (int i = 0; i < 3; i++)
	{
		m_temp = ResourceManager::instance().m_holder["Bus" + std::to_string(i)];
		m_playerCar[i] = new Car(m_temp, level.m_car.at(i).m_brake, level.m_car.at(i).m_handling, level.m_car.at(i).m_acceleration);
	}

	m_currency = 10; // currency for the player to buy upgrades

	// sets the current car to be the default
	m_currentCar = 0;
}

Player::~Player()
{
}

// updates the current current car that the player has selected
void Player::update(double & dt, Xbox360Controller * controller)
{
	m_playerCar[m_currentCar]->update(*controller, dt);
}

// renders the current car that the player has selected
void Player::render(sf::RenderWindow & window)
{
	m_playerCar[m_currentCar]->render(window);
}
