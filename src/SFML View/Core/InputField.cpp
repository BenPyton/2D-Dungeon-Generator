/*
* @author PELLETIER Benoit
*
* @file InputField.cpp
*
* @date 06/10/2018
*
* @brief An UI input field
*
*/

#include "stdafx.h"
#include "InputField.h"
#include "Time.h"

InputField::InputField(int x, int y, int width, int height)
	: AbstractUI(x, y, width, height)
{
	//m_text = sf::Text();
	m_str = "";
	m_placeholder = "";
	m_maxChar = 0;
	m_timer = 0;
}

InputField::~InputField()
{
}

//void InputField::setText(std::string text, sf::Font & font, int size)
//{
//	m_text.setFont(font);
//	m_text.setString(text);
//	m_text.setCharacterSize(size);
//	m_text.setFillColor(sf::Color::Black);
//	sf::FloatRect textRect = m_text.getLocalBounds();
//	float posX = m_rect.getPosition().x + 10;
//	float posY = m_rect.getPosition().y + 10;
//	m_text.setPosition(posX, posY);
//}

void InputField::setFont(sf::Font & font)
{
	m_text.setFont(font);
}

void InputField::setCharacterSize(int size)
{
	m_text.setCharacterSize(size);

}

void InputField::setMaxLength(int max)
{
	m_maxChar = max;
}

int InputField::getMaxLength()
{
	return m_maxChar;
}

void InputField::setPlaceholder(string placeholder)
{
	m_placeholder = placeholder;
}

string InputField::getPlaceholder()
{
	return m_placeholder.toAnsiString();
}

string InputField::getString()
{
	return m_str.toAnsiString();
}

float InputField::getFloat()
{
	return (float)atof(m_str.toAnsiString().c_str());
}

int InputField::getInt()
{
	return atoi(m_str.toAnsiString().c_str());
}

double InputField::getDouble()
{
	return atof(m_str.toAnsiString().c_str());
}

void InputField::setString(string str)
{
	m_str = str;
	_updateText();
}

void InputField::setFloat(float value)
{
	stringstream ss;
	ss << value;
	m_str = ss.str();
	_updateText();
}

void InputField::setInt(int value)
{
	stringstream ss;
	ss << value;
	m_str = ss.str();
	_updateText();
}

void InputField::setDouble(double value)
{
	stringstream ss;
	ss << value;
	m_str = ss.str();
	_updateText();
}

void InputField::update()
{
	if (m_enabled == false)
	{
		m_state = UIState::UI_DISABLED;
	}
	else if (m_state == UIState::UI_FOCUSED)
	{
		// lost focus
		if ((!hovered(Input::GetMousePosition()) && Input::GetMouseButtonDown(sf::Mouse::Left))
			|| Input::GetKeyDown(sf::Keyboard::Enter))
		{
			m_timer = 0;
			m_state = UIState::UI_NORMAL;
			// display placeholder if entered string is empty
			if (m_str.isEmpty())
			{
				m_text.setString(m_placeholder);
			}
		}
	}
	else
	{
		if (click())
		{
			m_state = UIState::UI_FOCUSED;
		}
		else if(hovered(Input::GetMousePosition()))
		{
			m_state = UIState::UI_HOVERED;
		}
		else
		{
			m_state = UIState::UI_NORMAL;
		}
	}

	m_rect.setFillColor(m_styles[m_state].bgCol);
	m_rect.setOutlineColor(m_styles[m_state].outCol);
	m_text.setColor(m_styles[m_state].fgCol);

	if (m_state == UIState::UI_FOCUSED)
	{
		// Get text entered during the frame
		m_timer += Time::GetDeltaTime();
		sf::String s = Input::GetEnteredText();
		for (int i = 0; i < s.getSize(); i++)
		{
			if (s[i] == 8) // backspace handler
			{
				if (m_str.getSize() > 0) // if empty we don't do anything
				{
					m_str.erase(m_str.getSize() - 1);
				}
			}
			else
			{
				if (m_maxChar <= 0 || (m_maxChar > 0 && m_str.getSize() < m_maxChar))
				{
					m_str += s[i];
				}
			}
		}
	}
	_updateText();
}


void InputField::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	AbstractUI::draw(target, states);
	target.draw(m_text);
}

void InputField::_updateText()
{
	if (((int)(m_timer * 1000) % 1000) > 500)
	{
		m_text.setString(m_str + "|");
	}
	else
	{
		m_text.setString(m_str);
	}

	//sf::FloatRect textRect = m_text.getLocalBounds();
	float posX = m_rect.getPosition().x + 10;
	float posY = m_rect.getPosition().y + m_rect.getSize().y / 2 - m_text.getCharacterSize() * 0.6f;
	m_text.setPosition(posX, posY);
}
