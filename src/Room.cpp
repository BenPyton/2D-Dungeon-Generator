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

Room::Room(int x, int y, int w, int h)
	: m_x(x), m_y(y), m_w(w), m_h(h)
{
}

Room::~Room()
{
}

bool Room::isIn(int x, int y)
{
	return x >= m_x && x < m_x + m_w
		&& y >= m_y && y < m_y + m_h;
}
