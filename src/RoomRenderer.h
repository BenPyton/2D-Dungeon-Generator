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

	uint64_t m_id;

	bool m_enableId;

protected:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;


public:
	RoomRenderer(Grid* grid = nullptr, Room* room = nullptr);
	~RoomRenderer();

	void update();

	void setRoom(Room* room);
	void setGrid(Grid* grid);
	void setColor(sf::Color color);
	inline void setId(uint64_t id) { m_id = id; }
	inline void setFont(sf::Font &font) { m_idText.setFont(font); }

	inline Room* getRoom() { return m_pRoom; }
	inline Grid* getGrid() { return m_pGrid; }
	inline sf::Color getColor() { return m_rect.getOutlineColor(); }
	inline uint64_t getId() { return m_id; }
	inline const sf::Font* getFont() { return m_idText.getFont(); }
};

#endif // _ROOMRENDERER_H