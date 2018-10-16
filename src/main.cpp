#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "Core.h" // custom classes and functions (like Input, Button, etc.)
#include "Grid.h"
#include "Room.h"
#include "RoomRenderer.h"
#include "Dungeon.h"

#define FRAMERATE 60

using namespace std;



int main()
{
	sf::RenderWindow window(sf::VideoMode(740, 740), "2D Dungeon Generator");
	sf::Vector2u size = window.getSize();

	// Load font
	sf::Font font;
	if (!font.loadFromFile("data/font/consola.ttf"))
	{
		printf("Error when loading font");
	}

	sf::Color lightGrey(200, 200, 200);
	sf::Color darkGrey(60, 60, 60);

	sf::Text fpsText("FPS: ??", font, 16);
	fpsText.setPosition(10, 10);
	fpsText.setColor(lightGrey);

	// Button Example
	Button button(size.x - 161, 10, 151, 30);
	button.setText("Generate", font, 16);
	button.mapStyle(UI_NORMAL, lightGrey, sf::Color::Transparent, lightGrey);
	button.mapStyle(UI_HOVERED, lightGrey, sf::Color(50, 50, 50), lightGrey);
	button.mapStyle(UI_CLICKED, sf::Color::Black, lightGrey, lightGrey);
	button.setOutlineThickness(1.0f);

	Grid grid(32, 32, 20, 20, darkGrey);
	grid.setPosition(sf::Vector2f(50, 50));

	sf::RectangleShape rect(sf::Vector2f(grid.getCellWidth(), grid.getCellHeight()));
	rect.setFillColor(lightGrey);

	Dungeon dungeon;
	dungeon.setGrid(&grid);

	// render dungeon rooms in SFML
	vector<RoomRenderer> rendererList;


	// ///////////////////////////// APPLICATION LOOP
	while (window.isOpen())
	{
		Time::LockFramerate(FRAMERATE);
		Input::Update(window);

		button.update(); // buttons must be updated before using them

		// ///////////////////////// GAME LOGIC
		if (Input::GetKeyDown(sf::Keyboard::Escape))
		{
			window.close();
		}

		fpsText.setString("FPS: " + floatToStr(Time::GetFps(), 0));

		if (button.click() || Input::GetKeyDown(sf::Keyboard::G))
		{
			cout << "Click !" << endl; 

			dungeon.generate(5);

			// create corresponding renderer
			rendererList.clear();
			for (int i = 0; i < dungeon.getRoomCount(); i++)
			{
				rendererList.push_back(RoomRenderer(&grid, dungeon.getRoomAt(i)));
				rendererList[i].setFont(font);
				rendererList[i].displayId(true);
				rendererList[i].displayParent(true);
			}
		}

		if (Input::GetMouseButtonDown(sf::Mouse::Left))
		{
			sf::Vector2f mousePos = Input::GetMousePosition();
			//cout << "Mouse position: (" << mousePos.x << "," << mousePos.y << ")" << endl;
		}

		sf::Vector2i cell = grid.screenToGrid(Input::GetMousePosition());
		rect.setPosition((grid.isIn(cell)) ? grid.gridToScreen(cell) : sf::Vector2f(-1000, -1000));

		// ///////////////////////// RENDERER UPDATES

		for (int i = 0; i < rendererList.size(); i++)
		{
			rendererList[i].setColor(dungeon.getRoomAt(i)->isIn(cell.x, cell.y) ? sf::Color::Red : sf::Color::White);
			rendererList[i].update();
		}

		// ///////////////////////// START DRAW
		window.clear();

		window.draw(fpsText);
		window.draw(button);

		window.draw(grid);

		window.draw(rect);

		//window.draw(dungeon);

		for (int i = 0; i < rendererList.size(); i++)
		{
			window.draw(rendererList[i]);
		}

		// ///////////////////////// END DRAW
		window.display();
	}

	return 0;
}
