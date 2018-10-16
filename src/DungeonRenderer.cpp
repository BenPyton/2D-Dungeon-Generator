/*
* @author PELLETIER Benoit
*
* @file DungeonRenderer.cpp
*
* @date 16/10/2018
*
* @brief Render a dungeon with SFML
*
*/

#include "stdafx.h"
#include "DungeonRenderer.h"
#include "Core/Input.h"

void DungeonRenderer::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int i = 0; i < m_cellList.size(); i++)
	{
		target.draw(m_cellList[i]);
	}

	for (int i = 0; i < m_rendererList.size(); i++)
	{
		target.draw(m_rendererList[i]);
	}
}

DungeonRenderer::DungeonRenderer(Dungeon* dungeon, Grid* grid)
	: m_pDungeon(dungeon), m_pGrid(grid)
{
}

DungeonRenderer::~DungeonRenderer()
{
}

void DungeonRenderer::update()
{
	sf::Vector2i cell = m_pGrid->screenToGrid(Input::GetMousePosition());
	for (int i = 0; i < m_rendererList.size(); i++)
	{
		m_rendererList[i].setColor(m_pDungeon->getRoomAt(i)->isIn(cell.x, cell.y) ? sf::Color::Red : sf::Color::White);
		m_rendererList[i].update();
	}
}

void DungeonRenderer::generate()
{
	// create corresponding renderer
	m_rendererList.clear();
	for (int i = 0; i < m_pDungeon->getRoomCount(); i++)
	{
		m_rendererList.push_back(RoomRenderer(m_pGrid, m_pDungeon->getRoomAt(i)));
		m_rendererList[i].setFont(*m_pFont);
		m_rendererList[i].displayId(true);
		m_rendererList[i].displayParent(true);
	}

	// create corresponding cell rectangle
	m_cellList.clear();
	for (int i = 0; i < m_pDungeon->getWidth(); i++)
	{
		for (int j = 0; j < m_pDungeon->getHeight(); j++)
		{
			if (m_pDungeon->getValue(i, j) == 1)
			{
				sf::RectangleShape rect(sf::Vector2f(m_pGrid->getCellWidth(), m_pGrid->getCellHeight()));
				rect.setFillColor(sf::Color::White);
				rect.setPosition(m_pGrid->gridToScreen(sf::Vector2i(i, j)));
				m_cellList.push_back(rect);
			}
		}
	}
}
