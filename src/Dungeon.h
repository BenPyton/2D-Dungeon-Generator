/*
* @author PELLETIER Benoit
*
* @file Dungeon.h
*
* @date 15/10/2018
*
* @brief Define and generate dungeons
*
*/

#ifndef _DUNGEON_H
#define _DUNGEON_H

#include <iostream>
#include <vector>
#include "Room.h"
#include "Grid.h"

using namespace std;

class Dungeon
{
private:
	vector<Room*> m_roomList;

private:
	void _Clear();

public:
	Dungeon();
	~Dungeon();

	inline size_t getRoomCount() { return m_roomList.size(); }
	inline Room* getRoomAt(int index) { return m_roomList[index]; }

	void generate(uint64_t width, uint64_t height, int iteration);
};

#endif // _DUNGEON_H