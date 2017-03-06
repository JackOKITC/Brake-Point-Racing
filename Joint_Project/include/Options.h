#ifndef OPTIONS_H
#define OPTIONS_H

class Options
{
public:
	Options();
	~Options();

	void update();
	void render();

	bool changeGameState();

private:
	bool m_changeState;
};
#endif // !OPTIONS_H
