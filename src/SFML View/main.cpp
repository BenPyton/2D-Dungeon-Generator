#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <DG/LibDungeon.h>
#include "Core.h" // custom classes and functions (like Input, Button, etc.)
#include "Grid.h"
#include "RoomRenderer.h"
#include "DungeonRenderer.h"

using namespace std;

int main()
{
	Window::Create(sf::VideoMode(900, 740), "2D Dungeon Generator");

	// Load font
	sf::Font font;
	if (!font.loadFromFile("../../../data/font/consola.ttf"))
	{
		printf("Error when loading font");
	}

	sf::Color lightGrey(200, 200, 200);
	sf::Color darkGrey(60, 60, 60);

	sf::Text fpsText("FPS: ??", font, 16);
	fpsText.setPosition(10, 10);
	fpsText.setFillColor(lightGrey);

	int nbGeneration = 0;
	sf::Text generationText("Nbr Generation: ??", font, 16);
	generationText.setPosition(10, Window::GetHeight() - 26);
	generationText.setFillColor(lightGrey);

	UIStyle style; 
	style.mapStyle(UI_NORMAL, lightGrey, sf::Color::Black, lightGrey, 1.0f);
	style.mapStyle(UI_HOVERED, lightGrey, sf::Color(50, 50, 50), lightGrey, 1.0f);
	style.mapStyle(UI_CLICKED, sf::Color::Black, lightGrey, lightGrey, 1.0f);

	// Button Generate
	Button btn_Generate(0, 0, 0, 30, &style);
	btn_Generate.setText("Generate", font, 16);

	// Button Show parents
	Toggle btn_showParents(0, 0, 0, 30, &style);
	btn_showParents.setText("Show Parents", font, 16);

	// Button Show neighbors
	Toggle btn_showNeighbors(0, 0, 0, 30, &style);
	btn_showNeighbors.setText("Show Neighbors", font, 16);

	// Button Show values
	Toggle btn_showLinks(0, 0, 0, 30, &style);
	btn_showLinks.setText("Show Links", font, 16);

	// Button Show values
	Toggle btn_showValues(0, 0, 0, 30, &style);
	btn_showValues.setText("Show Values", font, 16);


	VerticalLayout vLayout(0, 0, 170, 200);
	vLayout.setAnchorMin(sf::Vector2f(1, 0));
	vLayout.setAnchorMax(sf::Vector2f(1, 1));
	vLayout.setPivot(sf::Vector2f(1, 0));
	vLayout.setSpacing(10);
	vLayout.setPaddings(10, 10, 10, 10);
	vLayout.add(btn_Generate);
	vLayout.add(btn_showParents);
	vLayout.add(btn_showNeighbors);
	vLayout.add(btn_showLinks);
	vLayout.add(btn_showValues);

	Layout root(0, 0, Window::GetWidth(), Window::GetHeight());
	root.add(vLayout);
	Window::SetLayout(root);


	Grid grid(64, 64, 10, 10, darkGrey);
	grid.setPosition(sf::Vector2f(50, 50));

	sf::RectangleShape rect(sf::Vector2f(grid.getCellWidth(), grid.getCellHeight()));
	rect.setFillColor(lightGrey);


	DungeonParams params = DungeonParams::basic;
	params.width = grid.getWidth();
	params.height = grid.getHeight();
	params.roomMinWidth = 5;
	params.roomMinHeight = 5;
	Dungeon dungeon(params);

	// render dungeon in SFML
	DungeonRenderer renderer(&dungeon, &grid);
	renderer.setFont(font);

	// ///////////////////////////// APPLICATION LOOP
	while (Window::IsOpen())
	{
		Window::Update();

		// ///////////////////////// GAME LOGIC
		if (Input::GetKeyDown(sf::Keyboard::Escape))
		{
			Window::Close();
		}

		fpsText.setString("FPS: " + floatToStr(Time::GetFps(), 0));
		generationText.setString("Nbr generation: " + floatToStr(nbGeneration, 0));

		if (btn_Generate.click() || Input::GetKeyDown(sf::Keyboard::G))
		{
			cout << "Click !" << endl; 
			nbGeneration++;

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
		Window::Clear();

		Window::Draw(fpsText);
		Window::Draw();

		Window::Draw(generationText);
		Window::Draw(grid);
		Window::Draw(rect);
		Window::Draw(renderer);

		// ///////////////////////// END DRAW
		Window::Display();
	}

	return 0;
}
