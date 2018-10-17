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
#include "DungeonRenderer.h"

#define FRAMERATE 60

using namespace std;



int main()
{
	sf::RenderWindow window(sf::VideoMode(900, 740), "2D Dungeon Generator");
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

	// Button Generate
	Button button(size.x - 160, 10, 150, 30);
	button.setText("Generate", font, 16);
	button.mapStyle(UI_NORMAL, lightGrey, sf::Color::Transparent, lightGrey);
	button.mapStyle(UI_HOVERED, lightGrey, sf::Color(50, 50, 50), lightGrey);
	button.mapStyle(UI_CLICKED, sf::Color::Black, lightGrey, lightGrey);
	button.setOutlineThickness(1.0f);

	// Button Show parents
	Toggle btn_showParents(size.x - 160, 50, 150, 30);
	btn_showParents.setText("Show Parents", font, 16);
	btn_showParents.mapStyle(UI_NORMAL, lightGrey, sf::Color::Transparent, lightGrey);
	btn_showParents.mapStyle(UI_HOVERED, lightGrey, sf::Color(50, 50, 50), lightGrey);
	btn_showParents.mapStyle(UI_CLICKED, sf::Color::Black, lightGrey, lightGrey);
	btn_showParents.setOutlineThickness(1.0f);

	// Button Show neighbors
	Toggle btn_showNeighbors(size.x - 160, 90, 150, 30);
	btn_showNeighbors.setText("Show Neighbors", font, 16);
	btn_showNeighbors.mapStyle(UI_NORMAL, lightGrey, sf::Color::Transparent, lightGrey);
	btn_showNeighbors.mapStyle(UI_HOVERED, lightGrey, sf::Color(50, 50, 50), lightGrey);
	btn_showNeighbors.mapStyle(UI_CLICKED, sf::Color::Black, lightGrey, lightGrey);
	btn_showNeighbors.setOutlineThickness(1.0f);


	// Button Show values
	Toggle btn_showLinks(size.x - 160, 130, 150, 30);
	btn_showLinks.setText("Show Links", font, 16);
	btn_showLinks.mapStyle(UI_NORMAL, lightGrey, sf::Color::Transparent, lightGrey);
	btn_showLinks.mapStyle(UI_HOVERED, lightGrey, sf::Color(50, 50, 50), lightGrey);
	btn_showLinks.mapStyle(UI_CLICKED, sf::Color::Black, lightGrey, lightGrey);
	btn_showLinks.setOutlineThickness(1.0f);

	// Button Show values
	Toggle btn_showValues(size.x - 160, 170, 150, 30);
	btn_showValues.setText("Show Values", font, 16);
	btn_showValues.mapStyle(UI_NORMAL, lightGrey, sf::Color::Transparent, lightGrey);
	btn_showValues.mapStyle(UI_HOVERED, lightGrey, sf::Color(50, 50, 50), lightGrey);
	btn_showValues.mapStyle(UI_CLICKED, sf::Color::Black, lightGrey, lightGrey);
	btn_showValues.setOutlineThickness(1.0f);

	Grid grid(64, 64, 10, 10, darkGrey);
	grid.setPosition(sf::Vector2f(50, 50));

	sf::RectangleShape rect(sf::Vector2f(grid.getCellWidth(), grid.getCellHeight()));
	rect.setFillColor(lightGrey);

	Dungeon dungeon(grid.getWidth(), grid.getHeight());

	// render dungeon in SFML
	DungeonRenderer renderer(&dungeon, &grid);
	renderer.setFont(font);

	// ///////////////////////////// APPLICATION LOOP
	while (window.isOpen())
	{
		Time::LockFramerate(FRAMERATE);
		Input::Update(window);

		button.update(); // buttons must be updated before using them
		btn_showParents.update();
		btn_showNeighbors.update();
		btn_showValues.update();
		btn_showLinks.update();

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
			renderer.generate();
		}

		if (btn_showParents.click())
		{
			renderer.displayParents(btn_showParents.getChecked());
		}

		if (btn_showNeighbors.click())
		{
			renderer.displayNeighbors(btn_showNeighbors.getChecked());
		}

		if (btn_showValues.click())
		{
			renderer.displayValues(btn_showValues.getChecked());
		}

		if (btn_showLinks.click())
		{
			renderer.displayLinks(btn_showLinks.getChecked());
		}

		if (Input::GetMouseButtonDown(sf::Mouse::Left))
		{
			sf::Vector2f mousePos = Input::GetMousePosition();
			//cout << "Mouse position: (" << mousePos.x << "," << mousePos.y << ")" << endl;
		}

		sf::Vector2i cell = grid.screenToGrid(Input::GetMousePosition());
		rect.setPosition((grid.isIn(cell)) ? grid.gridToScreen(cell) : sf::Vector2f(-1000, -1000));

		// ///////////////////////// RENDERER UPDATES
		renderer.update();

		// ///////////////////////// START DRAW
		window.clear();

		window.draw(fpsText);
		window.draw(button);
		window.draw(btn_showNeighbors);
		window.draw(btn_showValues);
		window.draw(btn_showParents);
		window.draw(btn_showLinks);

		window.draw(grid);

		window.draw(rect);

		window.draw(renderer);

		// ///////////////////////// END DRAW
		window.display();
	}

	return 0;
}
