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
	if (m_displayValues)
	{
		for (size_t i = 0; i < m_cellList.size(); i++)
		{
			target.draw(m_cellList[i]);
		}
	}

	for (size_t i = 0; i < m_rendererList.size(); i++)
	{
		target.draw(m_rendererList[i]);
	}
}

DungeonRenderer::DungeonRenderer(Dungeon* dungeon, Grid* grid)
	: m_pDungeon(dungeon), m_pGrid(grid), 
	m_displayParents(false), m_displayValues(false), 
	m_displayNeighbors(false), m_displayLinks(false)
{

}

DungeonRenderer::~DungeonRenderer()
{
}

void DungeonRenderer::displayParents(bool enable)
{
	for (size_t i = 0; i < m_rendererList.size(); i++)
	{
		m_rendererList[i].displayParent(enable);
	}
	m_displayParents = enable;
}

void DungeonRenderer::displayNeighbors(bool enable)
{
	for (size_t i = 0; i < m_rendererList.size(); i++)
	{
		m_rendererList[i].displayNeighbors(enable);
	}
	m_displayNeighbors = enable;
}

void DungeonRenderer::displayLinks(bool enable)
{
	for (size_t i = 0; i < m_rendererList.size(); i++)
	{
		m_rendererList[i].displayLinks(enable);
	}
	m_displayLinks = enable;
}

void DungeonRenderer::update()
{
	if (nullptr != m_pDungeon && nullptr != m_pGrid)
	{
		sf::Vector2i cell = m_pGrid->screenToGrid(Input::GetMousePosition());
		for (size_t i = 0; i < m_rendererList.size(); i++)
		{
			m_rendererList[i].setColor(m_pDungeon->getRoom(i)->isIn(cell.x, cell.y) ? sf::Color::Red : sf::Color::White);
			m_rendererList[i].update();
		}
	}
}

void DungeonRenderer::generate()
{
	// create corresponding renderer
	m_rendererList.clear();
	for (size_t i = 0; i < m_pDungeon->getRoomCount(); i++)
	{
		m_rendererList.push_back(RoomRenderer(m_pGrid, m_pDungeon->getRoom(i)));
		m_rendererList[i].setFont(*m_pFont);
		m_rendererList[i].displayId(true);
		m_rendererList[i].displayParent(m_displayParents);
		m_rendererList[i].displayNeighbors(m_displayNeighbors);
		m_rendererList[i].displayLinks(m_displayLinks);
	}

	sf::Color grey(100, 100, 100);
	sf::Color orange(255, 180, 0);
	sf::Color brown(180, 100, 0);

	// create corresponding cell rectangle
	m_cellList.clear();
	DungeonParams params = m_pDungeon->getParams();
	for (uint64_t i = 0; i < params.width; i++)
	{
		for (uint64_t j = 0; j < params.height; j++)
		{
			if (m_pDungeon->getValue(i, j) != TileType::Empty)
			{
				sf::RectangleShape rect(sf::Vector2f(m_pGrid->getCellWidth(), m_pGrid->getCellHeight()));
				rect.setPosition(m_pGrid->gridToScreen(sf::Vector2i(i, j)));

				switch (m_pDungeon->getValue(i, j))
				{
				case TileType::Wall:
					rect.setFillColor(grey);
					break;
				case TileType::In:
					rect.setFillColor(sf::Color::Green);
					break;
				case TileType::Out:
					rect.setFillColor(sf::Color::Yellow);
					break;
				case TileType::Door:
					rect.setFillColor(sf::Color::Blue);
					break;
				case TileType::LockedDoor:
					rect.setFillColor(orange);
					break;
				case TileType::Enemy:
					rect.setFillColor(sf::Color::Red);
					break;
				case TileType::Chest:
					rect.setFillColor(brown);
					break;
				default:
					rect.setFillColor(sf::Color::Magenta);
				}


				m_cellList.push_back(rect);
			}
		}
	}
}
