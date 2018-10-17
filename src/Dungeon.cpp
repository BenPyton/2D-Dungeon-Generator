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
#include <cassert>

Dungeon::Dungeon(uint64_t width, uint64_t height)
	: m_width(width), m_height(height), m_array(nullptr)
{
	setSize(width, height);
}

Dungeon::~Dungeon()
{
	_ClearRoomList();
	_ClearArray();
}

void Dungeon::setSize(uint64_t width, uint64_t height)
{
	_ClearArray();

	m_width = width;
	m_height = height;

	m_array = (short**)malloc(m_height * sizeof(short*));
	for (int i = 0; i < m_height; i++)
	{
		m_array[i] = (short*)malloc(m_width * sizeof(short));
		memset(m_array[i], 0, m_width * sizeof(short));
	}
}

void Dungeon::generate(int iteration)
{
	_GenerateRooms(iteration);
	_FillArray();
}

short Dungeon::getValue(uint64_t x, uint64_t y)
{
	assert(nullptr != m_array && x < m_width && y < m_height);
	return m_array[y][x];
}

void Dungeon::setValue(uint64_t x, uint64_t y, short value)
{
	assert(nullptr != m_array && x < m_width && y < m_height);
	m_array[y][x] = value;
}


void Dungeon::_ClearRoomList()
{
	for (vector<Room*>::iterator it = m_roomList.begin(); it != m_roomList.end(); ++it)
	{
		delete *it;
	}
	m_roomList.clear();
}

void Dungeon::_ClearArray()
{
	if (nullptr != m_array)
	{
		for (uint64_t i = 0; i < m_height; i++)
		{
			delete[] m_array[i];
		}
		delete[] m_array;
		m_array = nullptr;
	}
}

void Dungeon::_GenerateRooms(int iteration)
{
	bool vertical = true;
	int splitX = 0, splitY = 0;

	_ClearRoomList();

	// create root room
	m_roomList.push_back(new Room(0, 0, m_width, m_height));

	for (int i = 0; i < iteration; i++)
	{
		int nbRoom = m_roomList.size(); // store it because it change in the for loop
		for (int k = 0; k < nbRoom; k++)
		{
			// Split the room in two rooms
			if (vertical)
			{
				splitX = Random::Range(1, m_roomList[k]->getWidth());
				splitY = 0;
			}
			else
			{
				splitX = 0;
				splitY = Random::Range(1, m_roomList[k]->getHeight());
			}


			// create new room to subdivide the current room
			Room* newRoom = new Room;
			newRoom->setX(m_roomList[k]->getX() + splitX);
			newRoom->setY(m_roomList[k]->getY() + splitY);
			newRoom->setWidth(m_roomList[k]->getWidth() - splitX);
			newRoom->setHeight(m_roomList[k]->getHeight() - splitY);
			newRoom->setParent(m_roomList[k]);

			// adjust size of the current room
			if (vertical)
			{
				m_roomList[k]->setWidth(splitX);
			}
			else
			{
				m_roomList[k]->setHeight(splitY);
			}

			// None of the two rooms are too small
			if (newRoom->getWidth() > 2 && newRoom->getHeight() > 2
				&& m_roomList[k]->getWidth() > 2 && m_roomList[k]->getHeight() > 2)
			{
				// Add new room in the list
				newRoom->setId(m_roomList.size());
				m_roomList.push_back(newRoom);
			}
			else // One of them is too small
			{
				// reset room size and DON'T add the new room
				m_roomList[k]->setWidth(splitX + newRoom->getWidth());
				m_roomList[k]->setHeight(splitY + newRoom->getHeight());

				// free memory
				delete newRoom;
			}
		}
		vertical = !vertical; // toggle vertical split
	}

	// list neighbors of each room
	for (vector<Room*>::iterator it = m_roomList.begin(); it != m_roomList.end(); ++it)
	{
		_ListNeighbors(*it);
	}
}

void Dungeon::_FillArray()
{
	if (nullptr != m_array)
	{
		_ResetArray();

		// make walls
		for (vector<Room*>::iterator it = m_roomList.begin(); it != m_roomList.end(); ++it)
		{
			Room* room = *it;

			for (int i = 0; i < room->getHeight(); i++)
			{
				m_array[room->getY() + i][room->getX()] = 1;
			}

			for (int i = 0; i < room->getWidth(); i++)
			{
				m_array[room->getY()][room->getX() + i] = 1;
			}

			for (int i = 0; i < m_height; i++)
			{
				m_array[i][m_width - 1] = 1;
			}

			for (int i = 0; i < m_width; i++)
			{
				m_array[m_height - 1][i] = 1;
			}
		}


		// Add an in 
		Room* inputRoom = m_roomList[Random::Range(0, m_roomList.size())];
		int randX = 0, randY = 0;
		do {
			randX = inputRoom->getX() + Random::Range(1, inputRoom->getWidth());
			randY = inputRoom->getY() + Random::Range(1, inputRoom->getHeight());
		} while (m_array[randY][randX] != 0);
		m_array[randY][randX] = 2;

		// add an out
		Room* outRoom = m_roomList[Random::Range(0, m_roomList.size())];
		do {
			randX = outRoom->getX() + Random::Range(1, outRoom->getWidth());
			randY = outRoom->getY() + Random::Range(1, outRoom->getHeight());
		} while (m_array[randY][randX] != 0);
		m_array[randY][randX] = 3;
	}
}

void Dungeon::_ResetArray()
{
	if (nullptr != m_array)
	{
		for (int i = 0; i < m_height; i++)
		{
			memset(m_array[i], 0, m_width * sizeof(short));
		}
	}
}

void Dungeon::_ListNeighbors(Room * r)
{
	for (vector<Room*>::iterator it = m_roomList.begin(); it != m_roomList.end(); ++it)
	{
		Room* other = *it;

		// they are closed to each other in X
		if (other->getX() + other->getWidth() == r->getX()
			|| other->getX() == r->getX() + r->getWidth())
		{
			if (!(other->getY() + other->getHeight() <= r->getY() || other->getY() >= r->getY() + r->getHeight()))
			{
				r->addNeighbor(other);
			}
		}

		// they are closed to each other in X
		if (other->getY() + other->getHeight() == r->getY()
			|| other->getY() == r->getY() + r->getHeight())
		{
			if (!(other->getX() + other->getWidth() <= r->getX() || other->getX() >= r->getX() + r->getWidth()))
			{
				r->addNeighbor(other);
			}
		}
	}
}

