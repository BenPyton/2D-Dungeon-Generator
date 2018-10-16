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

void RoomRenderer::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (nullptr != m_pGrid && nullptr != m_pRoom)
	{
		target.draw(m_rect, states);
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
		m_idText.setPosition(m_rect.getPosition() + sf::Vector2f(5, 5));
	}
}

void RoomRenderer::setRoom(Room* room)
{
	m_pRoom = room;
}

void RoomRenderer::setGrid(Grid* grid)
{
	m_pGrid = grid;
}

void RoomRenderer::setColor(sf::Color color)
{
	m_rect.setOutlineColor(color);
}
