#include "Widget.h"

#pragma region WidgetRegion

Widget::Widget()
{
}

Widget::~Widget()
{
}

void Widget::update()
{
}

void Widget::render(sf::RenderWindow & window)
{
}

void Widget::getFocus()
{
	hasFocus = true;
}

void Widget::loseFocus()
{
	hasFocus = false;
}

#pragma endregion

#pragma region ButtonRegion

Button::Button()
{

}

Button::Button(std::string *text, sf::Vector2f *position, sf::Font *font) :
	
	m_position(*position),	// Sets m_position to the de-referenced value of the position argument.
	m_text(*text, *font, 20)	// Sets m_text to the de-referenced value of the text argument as well as the de-referenced value of the font argument and then sets the size of the text to 28.
{
	m_buttonRectangle.setOutlineColor(sf::Color::Red);
	m_buttonRectangle.setOutlineThickness(5.0f);
	m_buttonRectangle.setPosition(m_position);
	m_buttonRectangle.setFillColor(m_seaBlue);
	m_buttonRectangle.setSize(sf::Vector2f(150, 50));
	m_buttonRectangle.setOrigin(sf::Vector2f(75, 25));

	m_textRectangle = m_text.getLocalBounds();	// Gets the dimensions of the rectangle that contains the text.
	m_text.setOrigin(m_textRectangle.width / 2.0f, m_textRectangle.height / 2.0f);	// Centres the origin of the text.
	m_text.setPosition(m_position.x, m_position.y - 5);	// Sets the position of the text with its centre now being its origin.
	m_text.setColor(m_white);	// Sets the colour of the text to black.
	m_hasFocus = false;
}

Button::~Button()
{	
}

void Button::update()
{
}

void Button::getFocus()
{
	m_buttonRectangle.setFillColor(sf::Color::Red);
	m_buttonRectangle.setOutlineColor(m_white);
	m_text.setColor(m_gold);	// Sets the colour of the text to red.
	m_hasFocus = true;	// Sets the variable m_hasFocus to true.
}

void Button::loseFocus()
{
	m_buttonRectangle.setFillColor(m_grey);
	m_buttonRectangle.setOutlineColor(m_white);
	m_text.setColor(m_paleBanana);	// Sets the colour of the text to black.
	m_hasFocus = false;	// Sets the variable m_hasFocus to false.
}

void Button::scaleButtons(float xScale, float yScale)
{
	
}

void Button::moveRight()
{
	
}

void Button::moveLeft()
{

}


void Button::render(sf::RenderWindow & window)
{
	window.draw(m_buttonRectangle);	// Draws the button rectangle to the screen.
	window.draw(m_text);	// Draws the text on top of the sprite.
}

#pragma endregion

#pragma region RadioButtonRegion

RadioButton::RadioButton()
{
}

RadioButton::RadioButton(sf::Texture * texture, sf::Vector2f * position) :
	m_position(*position),	// Sets m_position to the de-referenced value of the position argument.
	m_texture(*texture)	// Sets m_texture to the de-referenced value of the texture argument.
{

	m_sprite.setTexture(*texture);	// Sets the texture of the sprite to be that of the de-referenced texture.

	m_spriteRectangle = m_sprite.getLocalBounds();	// Gets the dimensions of the rectangle that contains the text.
	m_sprite.setOrigin(m_spriteRectangle.left + m_spriteRectangle.width / 2.0f, m_spriteRectangle.top + m_spriteRectangle.height / 2.0f);	// Centres the origin of the text.
	m_sprite.setPosition(m_position);	// Sets the position of the sprite to m_position with its centre as its origin.
}

RadioButton::~RadioButton()
{
}

void RadioButton::update()
{
}

void RadioButton::render(sf::RenderWindow & window)
{
	window.draw(m_sprite);	// Draws the sprite to the screen.
}

void RadioButton::getFocus()
{
	m_hasFocus = true;	// Gives focus to the RadioButton.
}

void RadioButton::loseFocus()
{
	m_hasFocus = false;	// Takes focus from the RadioButton.
}

void RadioButton::moveRight()
{
	m_sprite.setPosition(m_sprite.getPosition().x + 1, m_sprite.getPosition().y);	// Moves the sprite by positive one along the x-axis, while leaving the y-axis the same.
}

void RadioButton::moveLeft()
{
	m_sprite.setPosition(m_sprite.getPosition().x - 1, m_sprite.getPosition().y);	// Moves the sprite by negative one along the x-axis, while leaving the y-axis the same.
}

#pragma endregion

#pragma region SliderRegion


Slider::Slider()
{

}

Slider::Slider(sf::Vector2f * position, int numOfSegments) :
	m_position(*position),	// Sets m_position to the de-referenced value of position.
	m_numOfSegments(numOfSegments - 1)	// One is taken from numOfSegments to allow for using zero based numbering.
{
	m_rectangleSize = sf::Vector2f(350.f, 15.0f);	// Values used in both rectangle slider components.

	m_sliderBackground.setPosition(m_position);	// Sets the pos]ition of the slider background using the top left corner as the origin.
	m_slider.setPosition(m_position);	// Sets the position of the slider using the top left corner as the origin.

	m_sliderBackground.setFillColor(m_deepGrey);	// Sets the colour of the slider background to blue.
	m_slider.setFillColor(m_gold);	// Sets the colour of the slider to black.

	m_sliderBackground.setSize(m_rectangleSize);	// Sets the size of the slider background to the values in m_rectangleSize.
	m_slider.setSize(m_rectangleSize);	// Sets the size of the slider background to the values in m_rectangleSize.

	m_currentSegment = 0;	// sets m_currentSegment to the maximum possible value.
	m_slider.setSize(sf::Vector2f((m_sliderBackground.getSize().x / m_numOfSegments) * m_currentSegment, m_slider.getSize().y));
}

Slider::~Slider()
{
}

void Slider::update()
{
}

void Slider::render(sf::RenderWindow & window)
{
	window.draw(m_sliderBackground);	// Draws the slider background on the screen.
	window.draw(m_slider);	// Draws the slider on top of the slider background.
}

void Slider::getFocus()
{
	m_slider.setFillColor(sf::Color(m_gold));	// Sets the colour of the slider to sea blue.
	m_sliderBackground.setFillColor(sf::Color(m_deepGrey));
	m_hasFocus = true;	// Gives the slider focus.
}

void Slider::loseFocus()
{
	m_slider.setFillColor(sf::Color(0, 0, 0));	// Sets the colour of the slider to black.
	m_sliderBackground.setFillColor(sf::Color(m_grey));
	m_hasFocus = false;	// takes focus from the slider
}

void Slider::moveRight()
{
	m_sliderBackground.setPosition(m_slider.getPosition().x + 1, m_slider.getPosition().y);	// Moves the slider background by positive one along the x-axis, the y-axis remains unchanged.
	m_slider.setPosition(m_slider.getPosition().x + 1, m_slider.getPosition().y);	// Moves the slider by positive one along the x-axis, the y-axis remains unchanged.
}

void Slider::moveLeft()
{
	m_sliderBackground.setPosition(m_sliderBackground.getPosition().x - 1, m_sliderBackground.getPosition().y);// Moves the slider background by positive one along the x-axis, the y-axis remains unchanged.
	m_slider.setPosition(m_slider.getPosition().x - 1, m_slider.getPosition().y);	// Moves the slider by positive one along the x - axis, the y - axis remains unchanged.
}

int Slider::incrementSlider()
{
	if (m_currentSegment < m_numOfSegments)	// Checks that m_currentSegment is less the value stored in m_numOfSegments.
	{
		m_currentSegment++;	// Increments the value in m_currentSegment.
		m_slider.setSize(sf::Vector2f((m_sliderBackground.getSize().x / m_numOfSegments) * m_currentSegment, m_slider.getSize().y));	// Sets the length of the slider to be that of the total maximum length divided by the total number of segments multiplied by the number of the current segment.
	}

	return m_currentSegment;	// Returns the current segment.
}

int Slider::decrementSlider()
{
	if (m_currentSegment > 0)	// Checks that m_currentSegment is greater that 0.
	{
		m_currentSegment--;	// Decrements the value in m_currentSegment.
		m_slider.setSize(sf::Vector2f((m_sliderBackground.getSize().x / m_numOfSegments) * m_currentSegment, m_slider.getSize().y));	// Sets the length of the slider to be that of the total maximum length divided by the total number of segments multiplied by the number of the current segment.
	}

	return m_currentSegment;	// Returns the current segment.
}

void Slider::setCurrentSegment(int segmentValue)
{
	m_currentSegment = segmentValue;
	m_slider.setSize(sf::Vector2f((m_sliderBackground.getSize().x / m_numOfSegments) * m_currentSegment, m_slider.getSize().y));
}

#pragma endregion

#pragma region LabelRegion
Label::Label()
{

}

Label::Label(std::string * text, sf::Font * font, sf::Vector2f *position, int size) :
	m_font(*font),	// Sets the value of m_font to that of the de-referenced value stored in the font argument.
	m_position(*position),	// Sets the value of m_position to that of the de-referenced value stored in the position argument.
	m_text(*text, *font, size)	// Sets m_text to use the de-referenced value in the text argument as the string, the de-referenced value in the font argument as the font and uses the text size of 38. 
{
	m_textRectangle = m_text.getLocalBounds();	// Gets the dimensions of the rectangle that contains the text.
	m_text.setOrigin(m_textRectangle.left + m_textRectangle.width / 2.0f, m_textRectangle.top + m_textRectangle.height / 2.0f);	// Centres the origin of the text.
	m_text.setPosition(m_position);	// Sets the position of the text using its centre as the origin.
	m_text.setColor(sf::Color(m_gold));
	m_hasFocus = false;	// Sets the colour of the text to black.
}

Label::~Label()
{

}

void Label::update()
{
}

void Label::getFocus()
{
	m_text.setColor(sf::Color(m_gold));	// Sets the colour of the text to red.
	m_hasFocus = true;	// Gives the text focus, this will be shared with what the label is referencing.
}

void Label::loseFocus()
{
	m_text.setColor(sf::Color(m_lilac));	// Sets the colour of the text to pale yellow.
	m_hasFocus = false;	// Takes focus from the text, this will be shared with what the label is referencing.
}

bool Label::hasFocus()
{
	return m_hasFocus;
}

void Label::moveRight()
{
	//m_text.setPosition(m_text.getPosition().x + 1, m_text.getPosition().y);	// Moves the text by positive one along the x-axis, the y-axis is unchanged.
}

void Label::moveLeft()
{
	//m_text.setPosition(m_text.getPosition().x - 1, m_text.getPosition().y);	// Moves the text by negative one along the x-axis, the y-axis is unchanged.
}

void Label::render(sf::RenderWindow & window)
{
	//window.draw(m_buttonRectangle);	// Draws the button rectangle to the screen.
	window.draw(m_text);	// Draws the text on top of the sprite.
}

#pragma endregion

#pragma region BarRegion
Bar::Bar()
{
}

Bar::Bar(sf::Vector2f position, int size)
{
	m_recBar.setSize(sf::Vector2f(size * 3, size));
	m_recBar.setPosition(position);
	m_recBar.setOrigin(sf::Vector2f((size * 3) / 2, size / 2));
	m_recBar.setFillColor(sf::Color(0,0,0,0));
	m_recBar.setOutlineThickness(1.5f);
	m_recBar.setOutlineColor(m_white);
	m_currentNode = 0;

	for (int i = 0; i < 3; i++)
	{
		m_innerRecs[i].setSize(sf::Vector2f(size-2, size-2));
		m_innerRecs[i].setOrigin(sf::Vector2f(size / 2, size / 2));
		m_innerRecs[i].setPosition(sf::Vector2f((position.x - size) + size * i, position.y));
		m_innerRecs[i].setFillColor(sf::Color(0,0,0,0));
		m_innerRecs[i].setOutlineThickness(2);
		m_innerRecs[i].setOutlineColor(sf::Color(0, 0, 0, 0));
	}
}

Bar::~Bar()
{
}

void Bar::update()
{
}

void Bar::render(sf::RenderWindow & window)
{
	window.draw(m_recBar);
	for (int i = 0; i < 3; i++)
	{
		window.draw(m_innerRecs[i]);
	}
}

void Bar::getFocus()
{
}

void Bar::loseFocus()
{

}

void Bar::moveRight()
{
}

void Bar::moveLeft()
{
}

void Bar::increment()
{
	// increments the current node of the progression bar and sets the next progress segement to a gold colour
	m_innerRecs[m_currentNode].setFillColor(m_gold);
	if (m_currentNode != 3)
	{
		m_currentNode++;
	}
}

void Bar::assignValues(int level)
{
	// sets the number of upgrades in the bar to be at a certain level
	for (int i = 0; i < level; i++)
	{
		m_currentNode = i;
		m_innerRecs[m_currentNode].setFillColor(m_gold);
	}
}

int Bar::returnNode()
{
	return m_currentNode;
}
#pragma endregion