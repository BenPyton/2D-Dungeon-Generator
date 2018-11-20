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
#include "Window.h"
#include "View.h"
#include <cassert>

AbstractUI::AbstractUI(int x, int y, int width, int height, UIStyle* style)
	:m_parent(nullptr), m_viewParent(nullptr), m_enabled(true), m_state(UIState::UI_NORMAL), m_style(style), m_marginLeft(0), m_marginRight(0), m_marginTop(0), m_marginBottom(0)
{
	m_rect = new sf::RectangleShape();
	assert(nullptr != m_rect);
	//m_rect->setSize(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
	m_size = sf::Vector2f(static_cast<float>(width), static_cast<float>(height));
	m_position = sf::Vector2f((float)x, (float)y);
	m_horiStretch = false;
	m_vertStretch = false;
	m_anchorMin = sf::Vector2f(0, 0);
	m_anchorMax = sf::Vector2f(0, 0);
}

AbstractUI::~AbstractUI()
{
	if (nullptr != m_rect)
	{
		delete m_rect;
	}
}

void AbstractUI::setAnchor(sf::Vector2f anchor)
{
	m_anchorMin = anchor;
	m_anchorMax = anchor;
}

void AbstractUI::setAnchorMin(sf::Vector2f anchorMin)
{
	m_anchorMin.x = /*(anchorMin.x > m_anchorMax.x) ? m_anchorMax.x :*/ anchorMin.x;
	m_anchorMin.y = /*(anchorMin.y > m_anchorMax.y) ? m_anchorMax.y :*/ anchorMin.y;
}

void AbstractUI::setAnchorMax(sf::Vector2f anchorMax)
{
	m_anchorMax.y = /*(anchorMax.y < m_anchorMin.y) ? m_anchorMin.y :*/ anchorMax.y;
	m_anchorMax.x = /*(anchorMax.x < m_anchorMin.x) ? m_anchorMin.x :*/ anchorMax.x;
}

void AbstractUI::setPosition(sf::Vector2f position)
{
	m_position = position;
}

void AbstractUI::setSize(sf::Vector2f size)
{
	//m_rect->setSize(size);
	m_size = size;
}

void AbstractUI::setEnabled(bool enabled)
{
	m_enabled = enabled;
}

sf::Vector2f AbstractUI::getAnchorMin()
{
	return m_anchorMin;
}

sf::Vector2f AbstractUI::getAnchorMax()
{
	return m_anchorMax;
}

void AbstractUI::setPivot(sf::Vector2f pivot)
{
	m_pivot = pivot;
}

sf::Vector2f AbstractUI::getPivot()
{
	return m_pivot;
}

sf::Vector2f AbstractUI::getPosition()
{
	return m_position;
}

void AbstractUI::setStretch(bool horizontal, bool vertical)
{
	m_horiStretch = horizontal;
	m_vertStretch = vertical;
}

sf::Vector2f AbstractUI::getSize()
{
	return m_size;
}

sf::Vector2f AbstractUI::getRealPosition()
{
	return m_rect->getPosition();
}

sf::Vector2f AbstractUI::getRealSize()
{
	return m_rect->getSize();
}

bool AbstractUI::getEnabled()
{
	return m_enabled;
}

void AbstractUI::setMargins(float left, float right, float top, float bottom)
{
	m_marginLeft = left;
	m_marginRight = right;
	m_marginTop = top;
	m_marginBottom = bottom;
}

void AbstractUI::getMargins(float & left, float & right, float & top, float & bottom)
{
	left = m_marginLeft;
	right = m_marginRight;
	top = m_marginTop;
	bottom = m_marginBottom;
}

bool AbstractUI::hovered(sf::Vector2f pos)
{
	sf::Vector2f rp = m_rect->getPosition();
	sf::Vector2f rs = m_rect->getSize();
	if (nullptr != m_viewParent)
	{
		if (m_viewParent->hovered(pos))
		{
			/*sf::View tmp = Window::GetView();
			Window::SetView(m_viewParent->getView());
			pos = Window::GetWindow()->mapPixelToCoords((sf::Vector2i)pos);
			Window::SetView(tmp);*/
			pos = m_viewParent->mapScreenPointToView(pos);
		}
	}
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
	_updateState();
	_updateTransform();
	_updateStyle();
}

void AbstractUI::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(*m_rect, states);
}

void AbstractUI::_updateState()
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
}

void AbstractUI::_updateTransform()
{
	if (nullptr != m_parent)
	{
		sf::Vector2f pos(0, 0);
		sf::Vector2f size(0, 0);
		// use position X and width values
		if (m_anchorMin.x == m_anchorMax.x)
		{
			pos.x = m_parent->getRealPosition().x + m_parent->getRealSize().x * m_anchorMin.x + m_position.x - m_pivot.x * m_size.x;
			size.x = m_size.x;
		}
		else // use margins left and right
		{
			pos.x = m_parent->getRealPosition().x + m_parent->getRealSize().x * m_anchorMin.x + m_marginLeft;
			size.x = m_parent->getRealSize().x * (m_anchorMax.x - m_anchorMin.x) - m_marginLeft - m_marginRight;
		}

		// use position Y and height values
		if (m_anchorMin.y == m_anchorMax.y)
		{
			pos.y = m_parent->getRealPosition().y + m_parent->getRealSize().y * m_anchorMin.y + m_position.y - m_pivot.y * m_size.y;
			size.y = m_size.y;
		}
		else // use margins top and bottom
		{
			pos.y = m_parent->getRealPosition().y + m_parent->getRealSize().y * m_anchorMin.y + m_marginTop;
			size.y = m_parent->getRealSize().y * (m_anchorMax.y - m_anchorMin.y) - m_marginTop - m_marginBottom;
		}

		m_rect->setPosition(pos);
		m_rect->setSize(size);
	}
	else
	{
		m_rect->setPosition(m_position);
		m_rect->setSize(m_size);
	}
}

void AbstractUI::_updateStyle()
{
	m_rect->setFillColor((*m_style)[m_state].bgCol);
	m_rect->setOutlineColor((*m_style)[m_state].outCol);
	m_rect->setOutlineThickness((*m_style)[m_state].outThick);
}
