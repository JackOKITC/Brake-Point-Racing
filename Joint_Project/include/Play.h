#ifndef PLAY_H
#define PLAY_H

class Play
{
public:
	Play();
	~Play();

	void update();
	void render();

	bool changeGameState();

private:
	bool m_changeState;
};
#endif // !PLAY_H
