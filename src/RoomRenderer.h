/*
* @author PELLETIER Benoit
*
* @file RoomRenderer.h
*
* @date 12/10/2018
*
* @brief Class to render a room in SFML
*
*/

#ifndef _ROOMRENDERER_H
#define _ROOMRENDERER_H

#include <iostream>
#include "Room.h"
#include "Grid.h"
#include <SFML/Graphics.hpp>

using namespace std;

class RoomRenderer : public sf::Drawable
{
private:
	Room* m_pRoom;
	Grid* m_pGrid;
	sf::RectangleShape m_rect;

protected:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;


public:
	RoomRenderer(Grid* grid = nullptr, Room* room = nullptr);
	~RoomRenderer();

	void update();

	void setRoom(Room* room);
	void setGrid(Grid* grid);
	void setColor(sf::Color color);

};

#endif // _ROOMRENDERER_H