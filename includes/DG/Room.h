/*
* @author PELLETIER Benoit
*
* @file Room.h
*
* @date 11/10/2018
*
* @brief Define a dungeon room
*
*/

#ifndef _ROOM_H
#define _ROOM_H

#include <iostream>
#include <vector>
#include "Exports.h"

using namespace std;

class LIBDUNGEON_API Room
{
private:

	uint64_t m_id;
	int m_x, m_y;
	int m_w, m_h;

	Room* m_pParent;

	vector<Room*> m_neighbors;
	vector<Room*> m_links;

	bool m_locked = false;

public:
	Room(int x = 0, int y = 0, int w = 1, int h = 1);
	Room(const Room& _r);
	~Room();

	inline void setId(uint64_t id) { m_id = id; }
	inline void setX(int x) { m_x = x; }
	inline void setY(int y) { m_y = y; }
	inline void setPosition(int x, int y) { m_x = x; m_y = y; }
	inline void setWidth(int w) { m_w = w; }
	inline void setHeight(int h) { m_h = h; }
	inline void setSize(int w, int h) { m_w = w; m_h = h; }
	inline void setParent(Room* parent) { m_pParent = parent; }
	inline void setLocked(bool _locked) { m_locked = _locked; }

	inline uint64_t getId() { return m_id; }
	inline int getX() { return m_x; }
	inline int getY() { return m_y; }
	inline int getWidth() { return m_w; }
	inline int getHeight() { return m_h; }
	inline Room* getParent() { return m_pParent; }
	inline bool isLocked() { return m_locked; }

	inline void addNeighbor(Room* room) { m_neighbors.push_back(room); }
	Room* getNeighbor(int index);
	inline size_t getNeighborCount() { return m_neighbors.size(); }

	void addLink(Room* room);
	Room* getLink(int index);
	inline size_t getLinkCount() { return m_links.size(); }

	bool isIn(int x, int y);

	static bool pathExists(Room* _from, Room* _to);

};

// Functions to wrap in a Room.cs for Unity
#ifdef _UNITY
extern "C"
{
	LIBDUNGEON_API Room* Lib_Room_constructor(int _x, int _y, int _w, int _h);
	LIBDUNGEON_API Room* Lib_Room_copyConstructor(Room* _other);
	LIBDUNGEON_API void Lib_Room_destructor(Room* _this);

	LIBDUNGEON_API void Lib_Room_setId(Room* _this, uint64_t id);
	LIBDUNGEON_API void Lib_Room_setX(Room* _this, int x);
	LIBDUNGEON_API void Lib_Room_setY(Room* _this, int y);
	LIBDUNGEON_API void Lib_Room_setPosition(Room* _this, int x, int y);
	LIBDUNGEON_API void Lib_Room_setWidth(Room* _this, int w);
	LIBDUNGEON_API void Lib_Room_setHeight(Room* _this, int h);
	LIBDUNGEON_API void Lib_Room_setSize(Room* _this, int w, int h);
	LIBDUNGEON_API void Lib_Room_setParent(Room* _this, Room* parent);

	LIBDUNGEON_API uint64_t Lib_Room_getId(Room* _this);
	LIBDUNGEON_API int Lib_Room_getX(Room* _this);
	LIBDUNGEON_API int Lib_Room_getY(Room* _this);
	LIBDUNGEON_API int Lib_Room_getWidth(Room* _this);
	LIBDUNGEON_API int Lib_Room_getHeight(Room* _this);
	LIBDUNGEON_API Room* Lib_Room_getParent(Room* _this);

	LIBDUNGEON_API void Lib_Room_addNeighbor(Room* _this, Room* room);
	LIBDUNGEON_API Room* Lib_Room_getNeighbor(Room* _this, int index);
	LIBDUNGEON_API size_t Lib_Room_getNeighborCount(Room* _this);

	LIBDUNGEON_API void Lib_Room_addLink(Room* _this, Room* room);
	LIBDUNGEON_API Room* Lib_Room_getLink(Room* _this, int index);
	LIBDUNGEON_API size_t Lib_Room_getLinkCount(Room* _this);

	LIBDUNGEON_API bool Lib_Room_isIn(Room* _this, int x, int y);
}
#endif

#endif // _ROOM_H