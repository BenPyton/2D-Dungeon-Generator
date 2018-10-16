/*
* @author PELLETIER Benoit
*
* @file Dungeon.cpp
*
* @date 15/10/2018
*
* @brief Define and generate dungeons
*
*/

#include "stdafx.h"
#include "Dungeon.h"
#include "Core/Random.h"
#include "Core/Input.h"

void Dungeon::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int i = 0; i < m_rendererList.size(); i++)
	{
		target.draw(m_rendererList[i]);
	}
}

Dungeon::Dungeon()
{
}

Dungeon::~Dungeon()
{
}

void Dungeon::generate(int iteration)
{
	if (nullptr == m_pGrid) return;

	bool vertical = true;
	int splitX = 0, splitY = 0;
	m_roomList.clear();

	// create root room
	m_roomList.push_back(Room(0, 0, m_pGrid->getWidth(), m_pGrid->getHeight()));
	m_rendererList.push_back(RoomRenderer(m_pGrid, &m_roomList[0]));
	m_rendererList[0].setColor(sf::Color::White);

	for (int i = 0; i < iteration; i++)
	{
		int nbRoom = m_roomList.size(); // store it because it change in the for loop
		for (int k = 0; k < nbRoom; k++)
		{
			// Split the room in two rooms
			if (vertical)
			{
				splitX = Random::Range(1, m_roomList[k].getWidth());
				splitY = 0;
			}
			else
			{
				splitX = 0;
				splitY = Random::Range(1, m_roomList[k].getHeight());
			}


			// create new room to subdivide the current room
			Room newRoom;
			newRoom.setX(m_roomList[k].getX() + splitX);
			newRoom.setY(m_roomList[k].getY() + splitY);
			newRoom.setWidth(m_roomList[k].getWidth() - splitX);
			newRoom.setHeight(m_roomList[k].getHeight() - splitY);

			// adjust size of the current room
			if (vertical)
			{
				m_roomList[k].setWidth(splitX);
			}
			else
			{
				m_roomList[k].setHeight(splitY);
			}

			// None of the two rooms are too small
			if (newRoom.getWidth() > 2 && newRoom.getHeight() > 2
				&& m_roomList[k].getWidth() > 2 && m_roomList[k].getHeight() > 2)
			{
				// Add new room in the list
				m_roomList.push_back(newRoom);
			}
			else // One of them is too small
			{
				// reset room size and DON'T add the new room
				m_roomList[k].setWidth(splitX + newRoom.getWidth());
				m_roomList[k].setHeight(splitY + newRoom.getHeight());
			}
		}
		vertical = !vertical; // toggle vertical split
	}

	// create corresponding renderer
	m_rendererList.clear();
	for (int i = 0; i < m_roomList.size(); i++)
	{
		m_rendererList.push_back(RoomRenderer(m_pGrid, &(m_roomList[i])));
	}
}

void Dungeon::update()
{
	sf::Vector2i cell = m_pGrid->screenToGrid(Input::GetMousePosition());

	for (int i = 0; i < m_rendererList.size(); i++)
	{
		m_rendererList[i].setColor(m_roomList[i].isIn(cell.x, cell.y) ? sf::Color::Red : sf::Color::White);
		m_rendererList[i].update();
	}
}
