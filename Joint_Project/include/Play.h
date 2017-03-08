#ifndef PLAY_H
#define PLAY_H

#include "GameState.h"

class Play
{
public:
	Play();
	~Play();

	void update();
	void render();

	GameState changeGameState();

private:
	GameState m_changeState;
};
#endif // !PLAY_H
