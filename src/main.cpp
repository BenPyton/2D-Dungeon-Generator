#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Core.h" // custom classes and functions (like Input, Button, etc.)
#include "Grid.h"

#define FRAMERATE 60

using namespace std;


bool isIn(sf::Vector2i rectPos, sf::Vector2i rectSize, sf::Vector2i cellPos)
{
	return cellPos.x >= rectPos.x && cellPos.x < rectPos.x + rectSize.x
		&& cellPos.y >= rectPos.y && cellPos.y < rectPos.y + rectSize.y;
}

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

	sf::Vector2i roomPos;
	sf::Vector2i roomSize;
	sf::RectangleShape roomRect;
	roomRect.setFillColor(sf::Color::Transparent);
	roomRect.setOutlineColor(sf::Color::Green);
	/*roomRect.setPosition(roomPos);
	roomRect.setSize(roomSize);*/
	roomRect.setOutlineThickness(1.0f);

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

		if (button.click())
		{
			cout << "Click !" << endl; 
			roomPos = sf::Vector2i(Random::Range(0, grid.getWidth()), Random::Range(0, grid.getHeight()));
			roomSize = sf::Vector2i(Random::Range(1, grid.getWidth() - roomPos.x), Random::Range(1, grid.getHeight() - roomPos.y));

			roomRect.setPosition(grid.gridToScreen(roomPos));
			roomRect.setSize(grid.gridToScreen(roomSize) - grid.getPosition());
		}

		if (Input::GetMouseButtonDown(sf::Mouse::Left))
		{
			sf::Vector2f mousePos = Input::GetMousePosition();
			cout << "Mouse position: (" << mousePos.x << "," << mousePos.y << ")" << endl;
		}

		sf::Vector2i cell = grid.screenToGrid(Input::GetMousePosition());
		//rect.setPosition(grid.getPosition() + sf::Vector2f(cell.x * (sf::Int32)grid.getCellWidth(), cell.y * (sf::Int32)grid.getCellHeight()));
		rect.setPosition((grid.isIn(cell)) ? grid.gridToScreen(cell) : sf::Vector2f(-1000, -1000));

		rect.setFillColor(isIn(roomPos, roomSize, cell) ? sf::Color::Red : lightGrey);


		// ///////////////////////// START DRAW
		window.clear();

		window.draw(fpsText);
		window.draw(button);

		window.draw(grid);

		window.draw(rect);

		window.draw(roomRect);

		// ///////////////////////// END DRAW
		window.display();
	}

	return 0;
}
