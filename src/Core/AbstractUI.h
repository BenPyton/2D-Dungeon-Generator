/*
* @author PELLETIER Benoit
*
* @file AbstractUI.h
*
* @date 06/10/2018
*
* @brief Define a base class for UI elements
*
*/

#ifndef _ABSTRACTUI_H
#define _ABSTRACTUI_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Input.h"

using namespace std;

enum UIState {
	UI_NORMAL, UI_HOVERED, UI_FOCUSED, UI_CLICKED, UI_DISABLED, UI_NB_STATE
};

struct UIStateStyle {
	sf::Color bgCol;
	sf::Color fgCol;
	sf::Color outCol;
};

class AbstractUI : public sf::Drawable
{
protected:
	bool m_enabled;
	sf::RectangleShape m_rect;
	//sf::Text m_text;

	UIState m_state;
	UIStateStyle m_styles[UIState::UI_NB_STATE];

protected:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
	AbstractUI(int x, int y, int width, int height);
	~AbstractUI();

	// Accessors
	//void setText(std::string text, sf::Font &font, int size);
	void setOutlineThickness(float thickness);
	void setPosition(sf::Vector2f position);
	void setSize(sf::Vector2f size);
	void setEnabled(bool enabled);
	float getOutlineThickness();
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	bool getEnabled();

	void mapStyle(UIState state, sf::Color foregroundColor, sf::Color backgroundColor, sf::Color outlineColor);

	bool hovered(sf::Vector2f pos);
	bool click();
	virtual void update();

};

#endif // _ABSTRACTUI_H