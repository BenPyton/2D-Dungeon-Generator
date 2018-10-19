/*
* @author PELLETIER Benoit
*
* @file Grid.h
*
* @date 09/10/2018
*
* @brief Define and draw a grid in SFML
*
*/

#ifndef _GRID_H
#define _GRID_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>

using namespace std;

class Grid : public sf::Drawable
{
private:
	sf::Uint32 m_width, m_height;
	sf::Uint32 m_cellWidth, m_cellHeight;
	sf::Vector2f m_position;
	sf::VertexArray m_vertices;
	sf::Color m_color;

	void _UpdateVertices();

protected:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
	Grid(sf::Uint32 width, sf::Uint32 height, sf::Uint32 cellWidth, sf::Uint32 cellHeight, sf::Color color = sf::Color::White);
	~Grid();

	void setSize(sf::Uint32 width, sf::Uint32 height);
	void setWidth(sf::Uint32 width);
	void setHeight(sf::Uint32 height);
	void setCellSize(sf::Uint32 width, sf::Uint32 height);
	void setCellWidth(sf::Uint32 width);
	void setCellHeight(sf::Uint32 height);
	void setPosition(sf::Vector2f position);
	void setColor(sf::Color color);
	sf::Uint32 getWidth() const;
	sf::Uint32 getHeight() const;
	sf::Uint32 getCellWidth() const;
	sf::Uint32 getCellHeight() const;
	sf::Vector2f getPosition() const;
	sf::Color getColor() const;

	sf::Vector2i screenToGrid(sf::Vector2f point);
	sf::Vector2f gridToScreen(sf::Vector2i cell);

	bool isIn(sf::Vector2i cellPos);

};

#endif // _GRID_H