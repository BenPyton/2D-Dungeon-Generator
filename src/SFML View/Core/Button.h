/*
* @author PELLETIER Benoit
*
* @file Button.h
*
* @date 03/10/2018
*
* @brief Button class with SFML
*
*/

#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED


#include <SFML/Graphics.hpp>
#include "AbstractUI.h"

class Button : public AbstractUI
{
protected:
	sf::Text m_text;

protected:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
	// Constructor
	Button(int x, int y, int width, int height);

	// Accessors
	void setText(std::string text, sf::Font &font, int size);
	/*void SetNormalTexture(int x, int y, int w, int h);
	void SetClickedTexture(int x, int y, int w, int h);*/
	virtual void update() override;
};


#endif // BUTTON_H_INCLUDED