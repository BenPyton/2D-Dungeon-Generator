/*
* @author PELLETIER Benoit
*
* @file DungeonRenderer.h
*
* @date 16/10/2018
*
* @brief Render a dungeon with SFML
*
*/

#ifndef _DUNGEONRENDERER_H
#define _DUNGEONRENDERER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <DG/LibDungeon.h>
#include "Grid.h"
#include "RoomRenderer.h"

using namespace std;

class DungeonRenderer : public sf::Drawable
{
private:
	Dungeon* m_pDungeon;
	Grid* m_pGrid;
	vector<RoomRenderer> m_rendererList;
	vector<sf::RectangleShape> m_cellList;
	sf::Font* m_pFont;
	bool m_displayParents;
	bool m_displayNeighbors;
	bool m_displayValues;
	bool m_displayLinks;

protected:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
	DungeonRenderer(Dungeon* dungeon, Grid* grid);
	~DungeonRenderer();

	inline void setDungeon(Dungeon* dungeon) { m_pDungeon = dungeon; }
	inline Dungeon* getDungeon() { return m_pDungeon; }

	inline void setGrid(Grid* grid) { m_pGrid = grid; }
	inline Grid* getGrid() { return m_pGrid; }

	inline void setFont(sf::Font& font) { m_pFont = &font; }

	void displayParents(bool enable);
	void displayNeighbors(bool enable);
	inline void displayValues(bool enable) { m_displayValues = enable; }
	void displayLinks(bool enable);

	void update();

	void generate();
};

#endif // _DUNGEONRENDERER_H