#include <Garage.h>

Garage::Garage(sf::Font font, GameState * gameState) :
	m_font(font)
{
	m_gameState = gameState;

	m_backgroundTex = ResourceManager::instance().m_holder["MenuBG"];
	m_backgroundSprite.setTexture(m_backgroundTex);
	m_backgroundSprite.setOrigin(m_backgroundTex.getSize().x / 2, m_backgroundTex.getSize().y / 2);
	m_backgroundSprite.setPosition(450, 300);
	m_backgroundSprite.setScale(.1 , .1);
	
	for (int i = 0; i < 4; i ++)
	{
		m_upgradeText[i] = ResourceManager::instance().m_holder["Upgrade" + std::to_string(i)];
		m_uprgradeSpr[i].setTexture(m_upgradeText[i]);
		m_uprgradeSpr[i].setOrigin(m_upgradeText[i].getSize().x / 2, m_upgradeText[i].getSize().y / 2);
		m_uprgradeSpr[i].setPosition(180 + (i * 180), 500);
		m_uprgradeSpr[i].setScale(.1, .1);

		m_upgradeBars[i] = new Bar(sf::Vector2f(180 + (i * 180), 550), 25);
	}

	for (int i = 0; i < 3; i++)
	{
		m_carOptions[i] = ResourceManager::instance().m_holder["BusTex"];
		m_cars[i].setTexture(m_carOptions[i]);
		m_cars[i].setColor(sf::Color(255 - (i * 75), 255 - (i * 75), 255 - (i * 75), 255));
		m_cars[i].setPosition(180, 100 + (i * 100));
	}
}

Garage::~Garage()
{
}

void Garage::update(Xbox360Controller & controller, sf::Time dt)
{
	//checkButtonSelected(controller.m_currentState, controller);
	//selectedButton(controller.m_currentState, controller);
}

void Garage::render(sf::RenderWindow &window)
{
	window.draw(m_backgroundSprite);
	for (int i = 0; i < 3; i++)
	{
		window.draw(m_cars[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		window.draw(m_uprgradeSpr[i]);
		m_upgradeBars[i]->render(window);
	}
}


// Function to check which button is selected
void Garage::checkSelection(GamePadState m_state, Xbox360Controller m_controller)
{

}

// Function to check if the selected button has been pressed
void Garage::checkButton(GamePadState m_gamePadState, Xbox360Controller m_controller)
{
}
