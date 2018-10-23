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
#include "Exports.h"
#include "Room.h"
#include "DungeonParams.h"

using namespace std;

enum LIBDUNGEON_API TileType
{
	Empty = 0,
	Wall,
	In,
	Out,
	Door,
	LockedDoor,
	key,
	Chest,
	Enemy
};

class LIBDUNGEON_API Dungeon
{
private:
	vector<Room*> m_roomList;
	//uint64_t m_width, m_height;

	DungeonParams m_params;

	short **m_array;

public:
	Dungeon(uint64_t width, uint64_t height);
	Dungeon(const DungeonParams& params = DungeonParams::basic);
	~Dungeon();

	inline size_t getRoomCount() { return m_roomList.size(); }
	inline Room* getRoom(int index) { return m_roomList[index]; }
	Room* getRoomAt(uint64_t x, uint64_t y);

	/*void setSize(uint64_t width, uint64_t height);
	inline uint64_t getWidth() { return m_width; }
	inline uint64_t getHeight() { return m_height; }*/

	void generate(int iteration);


	short getValue(uint64_t x, uint64_t y);
	void setValue(uint64_t x, uint64_t y, short value);

	inline DungeonParams getParams() { return m_params; }
	void setParams(const DungeonParams& params);

private:
	int _RandRange(int min, int max);

	void _ClearRoomList();
	void _ClearArray();

	void _GenerateRooms(int iteration);
	void _FillArray();

	void _ResetArray();

	void _ListNeighbors(Room* r);

	bool _GetEmptyCell(Room* r, int& x, int& y);

	void _SetArraySize();
};

#endif // _DUNGEON_H