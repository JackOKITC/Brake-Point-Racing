#ifndef PLAY_H
#define PLAY_H

#include "GameState.h"

class Play
{
public:
	Play(GameState *gameState);
	~Play();

	void update();
	void render();

private:
	GameState *m_state;
};
#endif // !PLAY_H
