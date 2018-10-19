/*
* @author PELLETIER Benoit
*
* @file InputField.h
*
* @date 06/10/2018
*
* @brief An UI input field
*
*/

#ifndef _INPUTFIELD_H
#define _INPUTFIELD_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "AbstractUI.h"
#include <sstream>

using namespace std;

class InputField : public AbstractUI
{
private:
	sf::Text m_text;
	sf::String m_str;
	sf::String m_placeholder;
	int m_maxChar;
	float m_timer;

protected:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	void _updateText();

public:
	InputField(int x, int y, int width, int height);
	~InputField();


	// Accessors
	// void setText(std::string text, sf::Font &font, int size);
	void setFont(sf::Font &font);
	void setCharacterSize(int size);
	void setMaxLength(int max);
	int getMaxLength();
	void setPlaceholder(string placeholder);
	string getPlaceholder();

	string getString();
	float getFloat();
	int getInt();
	double getDouble();


	void setString(string str);
	void setFloat(float value);
	void setInt(int value);
	void setDouble(double value);


	virtual void update() override;

};

#endif // _INPUTFIELD_H