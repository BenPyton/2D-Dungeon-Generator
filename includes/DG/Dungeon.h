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
	Key,
	Chest,
	Enemy
};

class LIBDUNGEON_API Dungeon
{
private:
	vector<Room*> m_roomList;

	DungeonParams m_params;

	short **m_array = nullptr;

	uint64_t m_seed;

public:
	Dungeon(uint64_t width, uint64_t height);
	Dungeon(const DungeonParams& params = DungeonParams::basic);
	~Dungeon();

	inline size_t getRoomCount() { return m_roomList.size(); }
	inline Room* getRoom(int index) { return m_roomList[index]; }
	Room* getRoomAt(uint64_t x, uint64_t y);

	void generate();

	short getValue(uint64_t x, uint64_t y);
	void setValue(uint64_t x, uint64_t y, short value);

	inline DungeonParams getParams() { return m_params; }
	void setParams(const DungeonParams& params);

private:
	int _RandRange(int min, int max);

	void _ClearRoomList();
	void _ClearArray();

	void _GenerateRooms(int iteration);
	void _SplitRoomRecursive(int _iteration, Room* _r, bool _vertical);
	void _FillArray();
	void _ResetArray();
	void _ListNeighbors(Room* r);
	bool _GetEmptyCell(int& x, int& y, Room* r = nullptr);
	void _SetArraySize(uint64_t _width, uint64_t _height);
	void _LockDoors(Room* r);
};

// Functions to wrap in a Room.cs for Unity
#ifdef _UNITY
extern "C"
{
	LIBDUNGEON_API Dungeon* Lib_Dungeon_constructor(uint64_t _width, uint64_t _height);
	LIBDUNGEON_API Dungeon* Lib_Dungeon_paramsConstructor(const DungeonParams& _params);
	LIBDUNGEON_API void Lib_Dungeon_destructor(Dungeon* _this);

	LIBDUNGEON_API size_t Lib_Dungeon_getRoomCount(Dungeon* _this);
	LIBDUNGEON_API Room* Lib_Dungeon_getRoom(Dungeon* _this, int _index);
	LIBDUNGEON_API Room* Lib_Dungeon_getRoomAt(Dungeon* _this, uint64_t _x, uint64_t _y);

	LIBDUNGEON_API void Lib_Dungeon_generate(Dungeon* _this);

	LIBDUNGEON_API short Lib_Dungeon_getValue(Dungeon* _this, uint64_t x, uint64_t _y);
	LIBDUNGEON_API void Lib_Dungeon_setValue(Dungeon* _this, uint64_t _x, uint64_t _y, short _value);

	LIBDUNGEON_API DungeonParams Lib_Dungeon_getParams(Dungeon* _this);
	LIBDUNGEON_API void Lib_Dungeon_setParams(Dungeon* _this, const DungeonParams& _params);
}
#endif // _UNITY
#endif // _DUNGEON_H