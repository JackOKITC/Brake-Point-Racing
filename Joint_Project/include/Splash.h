#ifndef SPLASH_H
#define SPLASH_H

class Splash
{
public:
	Splash();
	~Splash();

	void update();
	void render();

	bool changeGameState();

private:
	bool m_changeState;
};
#endif // !SPLASH_H
