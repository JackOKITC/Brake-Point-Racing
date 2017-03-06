#ifndef OPTIONS_H
#define OPTIONS_H

#include <SFML\Graphics.hpp>

class Options
{
public:
	Options();
	~Options();

	void update();
	void render(sf::RenderWindow & window);

	bool changeGameState();

private:
	bool m_changeState;
};
#endif // !OPTIONS_H
