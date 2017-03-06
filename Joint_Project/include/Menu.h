#ifndef MENU_H
#define MENU_H

class Menu
{
public:
	Menu();
	~Menu();

	void update();
	void render();

	bool changeGameState();

private:
	bool m_changeState;
};
#endif // !MENU_H
