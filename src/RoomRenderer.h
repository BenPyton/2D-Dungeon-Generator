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
	sf::Text m_idText;
	sf::VertexArray m_parentLink;
	sf::VertexArray m_neighborsLink;

	bool m_enableId;
	bool m_enableParent;
	bool m_enableNeighbors;

protected:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;


public:
	RoomRenderer(Grid* grid = nullptr, Room* room = nullptr);
	~RoomRenderer();

	void update();

	inline void setRoom(Room* room) { m_pRoom = room; }
	inline void setGrid(Grid* grid) { m_pGrid = grid; }
	inline void setColor(sf::Color color) { m_rect.setOutlineColor(color); m_idText.setFillColor(color); }
	inline void setFont(sf::Font &font) { m_idText.setFont(font); }

	inline Room* getRoom() { return m_pRoom; }
	inline Grid* getGrid() { return m_pGrid; }
	inline sf::Color getColor() { return m_rect.getOutlineColor(); }
	inline const sf::Font* getFont() { return m_idText.getFont(); }

	inline void displayId(bool enable) { m_enableId = enable; }
	inline bool idDisplayed() { return m_enableId; }

	inline void displayParent(bool enable) { m_enableParent = enable; }
	inline bool parentDisplayed() { return m_enableParent; }

	inline void displayNeighbors(bool enable) { m_enableNeighbors = enable; }
	inline bool neighborsDisplayed() { return m_enableNeighbors; }
};

#endif // _ROOMRENDERER_H