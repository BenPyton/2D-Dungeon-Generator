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
#include "RoomRenderer.h"
#include "Grid.h"

using namespace std;

class Dungeon : public sf::Drawable
{
private:
	vector<Room> m_roomList;
	vector<RoomRenderer> m_rendererList;

	Grid* m_pGrid;

protected:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
	Dungeon();
	~Dungeon();

	inline void setGrid(Grid* grid) { m_pGrid = grid; }
	inline Grid* getGrid() { return m_pGrid; }

	void generate(int iteration);

	void update();
};

#endif // _DUNGEON_H