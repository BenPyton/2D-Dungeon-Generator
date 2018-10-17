/*
* @author PELLETIER Benoit
*
* @file Room.cpp
*
* @date 11/10/2018
*
* @brief Define a dungeon room
*
*/

#include "stdafx.h"
#include "Room.h"
#include <assert.h>

Room::Room(int x, int y, int w, int h)
	: m_x(x), m_y(y), m_w(w), m_h(h)
{
	m_id = 0;
	m_pParent = nullptr;
}

Room::Room(const Room & _r)
{
	m_id = _r.m_id;
	m_x = _r.m_x;
	m_y = _r.m_y;
	m_w = _r.m_w;
	m_h = _r.m_h;
	m_pParent = _r.m_pParent;
}

Room::~Room()
{
}

Room * Room::getNeighbor(int index)
{
	assert(index >= 0 && index < m_neighbors.size());
	return m_neighbors[index];
}

bool Room::isIn(int x, int y)
{
	return x >= m_x && x < m_x + m_w
		&& y >= m_y && y < m_y + m_h;
}
