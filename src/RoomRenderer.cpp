/*
* @author PELLETIER Benoit
*
* @file RoomRenderer.cpp
*
* @date 12/10/2018
*
* @brief Class to render a room in SFML
*
*/

#include "stdafx.h"
#include "RoomRenderer.h"
#include <sstream>

void RoomRenderer::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (nullptr != m_pGrid && nullptr != m_pRoom)
	{
		target.draw(m_rect, states);
		if (m_enableId)
		{
			target.draw(m_idText);
		}
		if (m_enableParent)
		{
			if (nullptr != m_pRoom->getParent())
			{
				target.draw(m_parentLink, states);
			}

			sf::CircleShape circle(5, 12);
			circle.setPosition(m_parentLink[0].position - sf::Vector2f(circle.getRadius(), circle.getRadius()));
			circle.setFillColor(sf::Color::Yellow);

			target.draw(circle, states);
		}
	}

}

RoomRenderer::RoomRenderer(Grid* grid, Room* room)
{
	m_pGrid = grid;
	m_pRoom = room;
	m_rect.setFillColor(sf::Color::Transparent);
	m_rect.setOutlineColor(sf::Color::White);
	m_rect.setOutlineThickness(1.0f);
	m_rect.setPosition(sf::Vector2f(0, 0));
	m_idText.setFillColor(sf::Color::White);
	m_idText.setCharacterSize(16);
	m_idText.setPosition(sf::Vector2f(0, 0));

	m_parentLink.append(sf::Vertex(sf::Vector2f(0, 0), sf::Color::Yellow));
	m_parentLink.append(sf::Vertex(sf::Vector2f(0, 0), sf::Color::Yellow));
	m_parentLink.setPrimitiveType(sf::PrimitiveType::Lines);

	m_enableId = false;
	m_enableParent = false;
}

RoomRenderer::~RoomRenderer()
{
}

void RoomRenderer::update()
{
	if (nullptr != m_pGrid && nullptr != m_pRoom)
	{
		m_rect.setPosition(m_pGrid->gridToScreen(sf::Vector2i(m_pRoom->getX(), m_pRoom->getY())));
		m_rect.setSize(m_pGrid->gridToScreen(sf::Vector2i(m_pRoom->getWidth(), m_pRoom->getHeight())) - m_pGrid->getPosition());
		m_idText.setPosition(m_rect.getPosition() + sf::Vector2f(5, 0));

		stringstream ss("");
		ss << m_pRoom->getId();
		m_idText.setString(ss.str());

		m_parentLink[0].position = 0.5f * (m_pGrid->gridToScreen(sf::Vector2i(m_pRoom->getX(), m_pRoom->getY())) + m_pGrid->gridToScreen(sf::Vector2i(m_pRoom->getX() + m_pRoom->getWidth(), m_pRoom->getY() + m_pRoom->getHeight())));
		if (nullptr != m_pRoom->getParent())
		{
			m_parentLink[1].position = 0.5f * (m_pGrid->gridToScreen(sf::Vector2i(m_pRoom->getParent()->getX(), m_pRoom->getParent()->getY())) + m_pGrid->gridToScreen(sf::Vector2i(m_pRoom->getParent()->getX() + m_pRoom->getParent()->getWidth(), m_pRoom->getParent()->getY() + m_pRoom->getParent()->getHeight())));
		}
	}
}
