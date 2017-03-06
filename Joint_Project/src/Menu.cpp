#include "Menu.h"

Menu::Menu(sf::Font & font) :
	m_font(font)
{
	if (!m_backgroundTex.loadFromFile(".//resources//images//UI//Button.png"))
	{
		std::cout << "Problem loading Texture for splash screen";
	}
	m_backgroundSprite.setTexture(m_backgroundTex);

	m_string = "MEMES";

	m_button = new Button(m_backgroundTex, &m_string, &sf::Vector2f(350, 200), &m_font);
}

Menu::~Menu()
{
}

void Menu::update()
{
}

void Menu::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::Cyan);
	m_button->render(window);
}

bool Menu::changeGameState()
{
	if (m_changeState)
	{
		return true;
	}
	else
	{
		return false;
	}
}
