/*
* @author PELLETIER Benoit
*
* @file Toggle.h
*
* @date 07/10/2018
*
* @brief Define a toggle (checkbox) in SFML
*
*/

#ifndef _TOGGLE_H
#define _TOGGLE_H

#include <iostream>
#include "Button.h"

using namespace std;

class Toggle : public Button
{
private:

	bool m_checked;

public:
	Toggle(int x, int y, int width, int height);
	~Toggle();

	void setChecked(bool checked);
	bool getChecked() const;
	virtual void update() override;

};

#endif // _TOGGLE_H