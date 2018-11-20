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

#include "DG/Room.h"
#include <cassert>

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

void Room::addLink(Room * room)
{
	bool isLinked = false;
	// search for an existing link with this room
	for (vector<Room*>::iterator it = m_links.begin(); it != m_links.end(); ++it)
	{
		if (*it == room)
		{
			isLinked = true;
		}
	}

	// add linked if not yet
	if (!isLinked)
	{
		m_links.push_back(room);
	}
}

Room * Room::getLink(int index)
{
	assert(index >= 0 && index < m_links.size());
	return m_links[index];
}

bool Room::isIn(int x, int y)
{
	return x >= m_x && x < m_x + m_w
		&& y >= m_y && y < m_y + m_h;
}



#ifdef _UNITY

Room* Lib_Room_constructor(int _x, int _y, int _w, int _h)
{
	return new Room(_x, _y, _w, _h);
}

Room* Lib_Room_copyConstructor(Room* _other)
{
	return new Room(*_other);
}

void Lib_Room_destructor(Room* _this)
{
	delete _this;
}


void Lib_Room_setId(Room* _this, uint64_t _id)
{
	_this->setId(_id);
}

void Lib_Room_setX(Room* _this, int _x)
{
	_this->setX(_x);
}

void Lib_Room_setY(Room* _this, int _y)
{
	_this->setY(_y);
}

void Lib_Room_setPosition(Room* _this, int _x, int _y)
{
	_this->setPosition(_x, _y);
}

void Lib_Room_setWidth(Room* _this, int _w)
{
	_this->setWidth(_w);
}

void Lib_Room_setHeight(Room* _this, int _h)
{
	_this->setHeight(_h);
}

void Lib_Room_setSize(Room* _this, int _w, int _h)
{
	_this->setSize(_w, _h);
}

void Lib_Room_setParent(Room* _this, Room* _parent)
{
	_this->setParent(_parent);
}


uint64_t Lib_Room_getId(Room* _this)
{
	return _this->getId();
}

int Lib_Room_getX(Room* _this)
{
	return _this->getX();
}

int Lib_Room_getY(Room* _this)
{
	return _this->getY();
}

int Lib_Room_getWidth(Room* _this)
{
	return _this->getWidth();
}

int Lib_Room_getHeight(Room* _this)
{
	return _this->getHeight();
}

Room* Lib_Room_getParent(Room* _this)
{
	return _this->getParent();
}


void Lib_Room_addNeighbor(Room* _this, Room* _room)
{
	_this->addNeighbor(_room);
}

Room* Lib_Room_getNeighbor(Room* _this, int _index)
{
	return _this->getNeighbor(_index);
}

size_t Lib_Room_getNeighborCount(Room* _this)
{
	return _this->getNeighborCount();
}


void Lib_Room_addLink(Room* _this, Room* _room)
{
	_this->addLink(_room);
}

Room* Lib_Room_getLink(Room* _this, int _index)
{
	return _this->getLink(_index);
}

size_t Lib_Room_getLinkCount(Room* _this)
{
	return _this->getLinkCount();
}


bool Lib_Room_isIn(Room* _this, int _x, int _y)
{
	return _this->isIn(_x, _y);
}


#endif