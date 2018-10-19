/*
* @author PELLETIER Benoit
*
* @file Grid.cpp
*
* @date 09/10/2018
*
* @brief Define and draw a grid in SFML
*
*/

#include "stdafx.h"
#include "Grid.h"

void Grid::_UpdateVertices()
{
	m_vertices.clear();
	// create vertical lines
	for (sf::Uint32 i = 0; i <= m_width; i++)
	{
		m_vertices.append(sf::Vertex(sf::Vector2f(
			m_position.x + i * m_cellWidth,
			m_position.y), m_color));
		m_vertices.append(sf::Vertex(sf::Vector2f(
			m_position.x + i * m_cellWidth,
			m_position.y + m_height * m_cellHeight), m_color));
	}

	// create horizontal lines
	for (sf::Uint32 i = 0; i <= m_height; i++)
	{
		m_vertices.append(sf::Vertex(sf::Vector2f(
			m_position.x,
			m_position.y + i * m_cellHeight), m_color));
		m_vertices.append(sf::Vertex(sf::Vector2f(
			m_position.x + m_width * m_cellWidth,
			m_position.y + i * m_cellHeight), m_color));
	}
}

void Grid::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_vertices, states);
}

Grid::Grid(sf::Uint32 width, sf::Uint32 height, sf::Uint32 cellWidth, sf::Uint32 cellHeight, sf::Color color)
	: m_width(width), m_height(height), m_cellWidth(cellWidth), m_cellHeight(cellHeight), m_color(color)
{
	m_vertices.setPrimitiveType(sf::PrimitiveType::Lines);
	_UpdateVertices();
}

Grid::~Grid()
{
}

void Grid::setSize(sf::Uint32 width, sf::Uint32 height)
{
	m_width = width;
	m_height = height;
	_UpdateVertices();
}

void Grid::setWidth(sf::Uint32 width)
{
	m_width = width;
	_UpdateVertices();
}

void Grid::setHeight(sf::Uint32 height)
{
	m_height = height;
	_UpdateVertices();
}

void Grid::setCellSize(sf::Uint32 width, sf::Uint32 height)
{
	m_cellWidth = width;
	m_cellHeight = height;
	_UpdateVertices();
}

void Grid::setCellWidth(sf::Uint32 width)
{
	m_cellWidth = width;
	_UpdateVertices();
}

void Grid::setCellHeight(sf::Uint32 height)
{
	m_cellHeight = height;
	_UpdateVertices();
}

void Grid::setPosition(sf::Vector2f position)
{
	m_position = position;
	_UpdateVertices();
}

void Grid::setColor(sf::Color color)
{
	for (size_t i = 0; i < m_vertices.getVertexCount(); i++)
	{
		m_vertices[i].color = color;
	}
}

sf::Uint32 Grid::getWidth() const
{
	return m_width;
}

sf::Uint32 Grid::getHeight() const
{
	return m_height;
}

sf::Uint32 Grid::getCellWidth() const
{
	return m_cellWidth;
}

sf::Uint32 Grid::getCellHeight() const
{
	return m_cellHeight;
}

sf::Vector2f Grid::getPosition() const
{
	return m_position;
}

sf::Color Grid::getColor() const
{
	return m_color;
}

sf::Vector2i Grid::screenToGrid(sf::Vector2f point)
{
	// get rid of the offset
	point -= m_position;
	// divide and round values
	return sf::Vector2i(
		floor(point.x / m_cellWidth),
		floor(point.y / m_cellHeight)
	);
}

sf::Vector2f Grid::gridToScreen(sf::Vector2i cell)
{
	return m_position + sf::Vector2f(cell.x * (sf::Int32)m_cellWidth, cell.y * (sf::Int32)m_cellHeight);
}

bool Grid::isIn(sf::Vector2i cellPos)
{
	return cellPos.x >= 0 && cellPos.x < m_width
		&& cellPos.y >= 0 && cellPos.y < m_height;
}

