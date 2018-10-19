/*
* @author PELLETIER Benoit
*
* @file AbstractUI.cpp
*
* @date 06/10/2018
*
* @brief Define a base class for UI elements
*
*/

#include "stdafx.h"
#include "AbstractUI.h"

void AbstractUI::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_rect);
}

AbstractUI::AbstractUI(int x, int y, int width, int height)
{
	//m_rect = sf::RectangleShape(sf::Vector2f((float)width, (float)height));
	m_rect.setSize(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
	m_rect.setPosition(sf::Vector2f((float)x, (float)y));
	//m_text = sf::Text();
	m_state = UIState::UI_NORMAL;
}

AbstractUI::~AbstractUI()
{
}

//void AbstractUI::setText(std::string text, sf::Font & font, int size)
//{
//}

void AbstractUI::setOutlineThickness(float thickness)
{
	m_rect.setOutlineThickness(thickness);
}

void AbstractUI::setPosition(sf::Vector2f position)
{
	m_rect.setPosition(position);
}

void AbstractUI::setSize(sf::Vector2f size)
{
	m_rect.setSize(size);
}

void AbstractUI::setEnabled(bool enabled)
{
	m_enabled = enabled;
}

float AbstractUI::getOutlineThickness()
{
	return m_rect.getOutlineThickness();
}

sf::Vector2f AbstractUI::getPosition()
{
	return m_rect.getPosition();
}

sf::Vector2f AbstractUI::getSize()
{
	return m_rect.getSize();
}

bool AbstractUI::getEnabled()
{
	return m_enabled;
}

void AbstractUI::mapStyle(UIState state, sf::Color textColor, sf::Color backgroundColor, sf::Color outlineColor)
{
	m_styles[state].fgCol = textColor;
	m_styles[state].bgCol = backgroundColor;
	m_styles[state].outCol = outlineColor;
}

bool AbstractUI::hovered(sf::Vector2f pos)
{
	sf::Vector2f rp = m_rect.getPosition();
	sf::Vector2f rs = m_rect.getSize();
	return (pos.x >= rp.x && pos.x <= rp.x + rs.x) && (pos.y >= rp.y && pos.y <= rp.y + rs.y);
}

bool AbstractUI::click()
{
	bool click = false;

	if (Input::GetMouseButtonDown(sf::Mouse::Left))
	{
		if (hovered(Input::GetMousePosition()))
		{
			click = true;
		}
	}
	
	return click;
}

void AbstractUI::update()
{
	if (m_enabled == false)
	{
		m_state = UIState::UI_DISABLED;
	}
	else if (hovered(Input::GetMousePosition()))
	{
		if (Input::GetMouseButton(sf::Mouse::Left))
		{
			m_state = UIState::UI_CLICKED;
		}
		else
		{
			m_state = UIState::UI_HOVERED;
		}
	}
	else
	{
		m_state = UIState::UI_NORMAL;
	}

	m_rect.setFillColor(m_styles[m_state].bgCol);
	m_rect.setOutlineColor(m_styles[m_state].outCol);
	//m_text.setColor(m_styles[m_state].textCol);
}
