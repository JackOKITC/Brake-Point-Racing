#ifndef AI_H
#define AI_H

#include <SFML\Graphics.hpp>
#include <iostream>

class Ai
{
	Ai();
	~Ai();

	void update(double dt);
	void render(sf::RenderWindow & window);

	void Seek(int nodeNumber);

	sf::Vector2f m_position;

private:

	int m_nodeNumber;

	sf::Texture m_carTex;
	sf::Sprite m_carSprite;

	sf::Vector2f m_velocity;
	float m_rotation;
	float m_speed = 0.0f;

	const double DEG_TO_RAD = 3.14159 / 180.0f;
};

#endif // !AI_H