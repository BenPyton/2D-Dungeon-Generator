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
		sf::CircleShape circle(5, 12);

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

			circle.setPosition(m_parentLink[0].position - sf::Vector2f(circle.getRadius(), circle.getRadius()));
			circle.setFillColor(sf::Color::Yellow);

			target.draw(circle, states);
		}
		if (m_enableNeighbors)
		{
			target.draw(m_neighborsLink, states);
		}
		if (m_enableLinks)
		{
			target.draw(m_links, states);

			sf::Vector2f center = 0.5f * (m_pGrid->gridToScreen(sf::Vector2i(m_pRoom->getX(), m_pRoom->getY())) + m_pGrid->gridToScreen(sf::Vector2i(m_pRoom->getX() + m_pRoom->getWidth(), m_pRoom->getY() + m_pRoom->getHeight())));
			circle.setPosition(center - sf::Vector2f(circle.getRadius(), circle.getRadius()));
			circle.setFillColor(sf::Color::Green);
			target.draw(circle);
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

	m_neighborsLink.setPrimitiveType(sf::PrimitiveType::Lines);
	m_links.setPrimitiveType(sf::PrimitiveType::Lines);

	m_enableId = false;
	m_enableParent = false;
	m_enableNeighbors = false;
	m_enableLinks = false;
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


		m_neighborsLink.clear();
		for (size_t i = 0; i < m_pRoom->getNeighborCount(); i++)
		{
			m_neighborsLink.append(sf::Vertex(0.5f * (m_pGrid->gridToScreen(sf::Vector2i(m_pRoom->getX(), m_pRoom->getY())) + m_pGrid->gridToScreen(sf::Vector2i(m_pRoom->getX() + m_pRoom->getWidth(), m_pRoom->getY() + m_pRoom->getHeight()))), sf::Color::Cyan));
			m_neighborsLink.append(sf::Vertex(0.5f * (m_pGrid->gridToScreen(sf::Vector2i(m_pRoom->getNeighbor(i)->getX(), m_pRoom->getNeighbor(i)->getY())) + m_pGrid->gridToScreen(sf::Vector2i(m_pRoom->getNeighbor(i)->getX() + m_pRoom->getNeighbor(i)->getWidth(), m_pRoom->getNeighbor(i)->getY() + m_pRoom->getNeighbor(i)->getHeight()))), sf::Color::Cyan));
		}

		m_links.clear();
		for (size_t i = 0; i < m_pRoom->getLinkCount(); i++)
		{
			m_links.append(sf::Vertex(0.5f * (m_pGrid->gridToScreen(sf::Vector2i(m_pRoom->getX(), m_pRoom->getY())) + m_pGrid->gridToScreen(sf::Vector2i(m_pRoom->getX() + m_pRoom->getWidth(), m_pRoom->getY() + m_pRoom->getHeight()))), sf::Color::Green));
			m_links.append(sf::Vertex(0.5f * (m_pGrid->gridToScreen(sf::Vector2i(m_pRoom->getLink(i)->getX(), m_pRoom->getLink(i)->getY())) + m_pGrid->gridToScreen(sf::Vector2i(m_pRoom->getLink(i)->getX() + m_pRoom->getLink(i)->getWidth(), m_pRoom->getLink(i)->getY() + m_pRoom->getLink(i)->getHeight()))), sf::Color::Green));
		}
	}
}
