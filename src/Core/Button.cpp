/*
* @author PELLETIER Benoit
*
* @file Button.cpp
*
* @date 03/10/2018
*
* @brief Button class with SFML
*
*/

#include "stdafx.h"
#include "Button.h"


Button::Button(int x, int y, int width, int height)
	: AbstractUI(x, y, width, height)
{
	//m_text = sf::Text();
}

//void Button::SetNormalTexture(int x, int y, int w, int h)
//{
//	m_normalRect = sf::IntRect(x, y, w, h);
//}
//
//void Button::SetClickedTexture(int x, int y, int w, int h)
//{
//	m_clickedRect = sf::IntRect(x, y, w, h);
//}

void Button::setText(std::string text, sf::Font &font, int size)
{
	m_text.setFont(font);
	m_text.setString(text);
	m_text.setCharacterSize(size);
	//m_text.setFillColor(sf::Color::Black);
	sf::FloatRect textRect = m_text.getLocalBounds();
	float posX = m_rect.getPosition().x + (int)(m_rect.getSize().x) / 2 - (int)(textRect.width + textRect.left) / 2;
	float posY = m_rect.getPosition().y + (int)(m_rect.getSize().y) / 2 - m_text.getCharacterSize() * 0.6f;
	m_text.setPosition(posX, posY);
}

void Button::update()
{
	AbstractUI::update();
	m_text.setColor(m_styles[m_state].fgCol);
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	AbstractUI::draw(target, states);
	target.draw(m_text);
}