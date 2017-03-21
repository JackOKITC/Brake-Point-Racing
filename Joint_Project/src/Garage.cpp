#include <Garage.h>

Garage::Garage(sf::Font font, GameState * gameState) :
	m_font(font)
{
	m_gameState = gameState;

	//m_backgroundTex = ResourceManager::instance().m_holder["MenuBG"];
	//m_backgroundSprite.setTexture(m_backgroundTex);
	//m_backgroundSprite.setOrigin(m_backgroundTex.getSize().x / 2, m_backgroundTex.getSize().y / 2);
	//m_backgroundSprite.setPosition(450, 300);
	//m_backgroundSprite.setScale(.1 , .1);
	m_currentCar = 0;
	m_currentStat = 0;
	m_font = font;


	// generate and place the images of each upgradeable car
	for (int i = 0; i < 3; i++)
	{
		m_carOptions[i] = ResourceManager::instance().m_holder["Bus" + std::to_string(i)];
		m_cars[i].setTexture(m_carOptions[i]);
		m_cars[i].setPosition(50, 100 + (i * 100));
		m_cars[i].setScale(.75,.75);

		m_upgradeText[i] = ResourceManager::instance().m_holder["Upgrade" + std::to_string(i)];
		m_uprgradeSpr[i].setTexture(m_upgradeText[i]);
		m_uprgradeSpr[i].setOrigin(m_upgradeText[i].getSize().x / 2, m_upgradeText[i].getSize().y / 2);
		m_uprgradeSpr[i].setPosition(225 + (i * 225), 500);
		m_uprgradeSpr[i].setScale(.1, .1);
		m_upgradeBars[i] = new Bar(sf::Vector2f(225 + (i * 225), 550), 25);

		m_statValues[i] = new Slider(&sf::Vector2f(450, 150 + (i * 75)), 10);
		m_statLabel[i] = new Label(&m_strings[i], &m_font, &sf::Vector2f(350, 160 + (i * 75)), 15);
		m_statLabel[i]->loseFocus();
	}

	int value1 = 5, value2 = 3, value3 = 6, value4 = 8;

	m_statValues[0]->setCurrentSegment(value1);
	m_statValues[1]->setCurrentSegment(value2);
	m_statValues[2]->setCurrentSegment(value3);
}

Garage::~Garage()
{
}

void Garage::update(Xbox360Controller & controller, sf::Time dt)
{
	checkSelection(controller.m_currentState, controller);
	checkButton(controller.m_currentState, controller);
}

void Garage::render(sf::RenderWindow &window)
{
	window.draw(m_backgroundSprite);
	for (int i = 0; i < 3; i++)
	{
		window.draw(m_cars[i]);
		window.draw(m_uprgradeSpr[i]);
		m_statValues[i]->render(window);
		m_statLabel[i]->render(window);
		m_upgradeBars[i]->render(window);
	}
}


// Function to check which button is selected
void Garage::checkSelection(GamePadState m_state, Xbox360Controller m_controller)
{
	if (m_controller.m_currentState.LeftThumbStick.y > 50 && m_controller.m_previousState.LeftThumbStick.y < 50)
	{
		if (m_statLabel[m_currentStat]->hasFocus())
		{
			m_statLabel[m_currentStat]->loseFocus();
			m_currentStat++;
			if (m_currentStat > 2)
			{
				m_currentStat = 2;
			}
			m_statLabel[m_currentStat]->getFocus();
		}

		else
		{
			m_cars[m_currentCar].setColor(m_dim);
			m_currentCar++;
			if (m_currentCar > 2)
			{
				m_currentCar = 2;
			}
			m_cars[m_currentCar].setColor(sf::Color(255, 255, 255, 255));
		}
	}

	if (m_controller.m_currentState.LeftThumbStick.y < -50 && m_controller.m_previousState.LeftThumbStick.y > -50)
	{
		if (m_statLabel[m_currentStat]->hasFocus())
		{
			m_statLabel[m_currentStat]->loseFocus();
			m_currentStat--;
			if (m_currentStat < 0)
			{
				m_currentStat = 0;
			}
			m_statLabel[m_currentStat]->getFocus();
		}

		else
		{
			m_cars[m_currentCar].setColor(m_dim);
			m_currentCar--;
			if (m_currentCar < 0)
			{
				m_currentCar = 0;
			}
			m_cars[m_currentCar].setColor(sf::Color(255, 255, 255, 255));
		}
	}
}

// Function to check if the selected button has been pressed
void Garage::checkButton(GamePadState m_gamePadState, Xbox360Controller m_controller)
{
	if (m_controller.m_currentState.B && !m_controller.m_previousState.B)
	{
		if (m_statLabel[m_currentStat]->hasFocus())
		{
			m_statLabel[m_currentStat]->loseFocus();
			m_cars[m_currentCar].setColor(sf::Color(255, 255, 255, 255));
			m_currentStat = 0;
		}

		else
		{

			*m_gameState = GameState::MENU_STATE;
		}
	}

	if (m_controller.m_currentState.A && !m_controller.m_previousState.A)
	{
		if (!m_statLabel[m_currentStat]->hasFocus())
		{
			m_statLabel[m_currentStat]->getFocus();
		}

		else
		{
			if (m_upgradeBars[m_currentStat]->returnNode() <= 2)
			{
				m_upgradeBars[m_currentStat]->increment();
				m_statValues[m_currentStat]->incrementSlider();
			}
		}
	}
}
