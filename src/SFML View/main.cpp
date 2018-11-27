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
	Window::SetFramerate(120);

	// Load font
	sf::Font font;
	if (!font.loadFromFile("../../../data/font/consola.ttf"))
	{
		printf("Error when loading font");
	}

	sf::Color lightGrey(200, 200, 200);
	sf::Color darkGrey(60, 60, 60);

	DungeonParams params = DungeonParams::basic;
	params.width = 32;
	params.height = 32;
	params.roomMinWidth = 3;
	params.roomMinHeight = 3;
	params.roomMaxWidth = 15;
	params.roomMaxHeight = 15;
	params.randomSeed = false;
	params.seed = 0;
	Dungeon dungeon(params);

	UIStyle style;
	style.mapStyle(UI_NORMAL, lightGrey, sf::Color::Black, lightGrey, 1.0f);
	style.mapStyle(UI_HOVERED, lightGrey, sf::Color(50, 50, 50), lightGrey, 1.0f);
	style.mapStyle(UI_CLICKED, sf::Color::Black, lightGrey, lightGrey, 1.0f);
	style.setFont(font, 16);

	Label lbl_fps(0, 0, 200, 30, &style);
	lbl_fps.setAnchor(sf::Vector2f(0, 0));
	lbl_fps.setMargins(10, 10, 10, 10);

	int nbGeneration = 0;
	Label lbl_generation(0, 0, 200, 30, &style);
	lbl_generation.setAnchor(sf::Vector2f(0, 1));
	lbl_generation.setMargins(10, 10, 10, 10);
	lbl_generation.setPivot(sf::Vector2f(0, 1));

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

	Label lbl_dungeonSize(0, 0, 0, 20, &style);
	lbl_dungeonSize.setText("Dungeon Size");
	lbl_dungeonSize.setAlignement(ALIGN_RIGHT);

	InputField input_dungeonWidth(0, 0, 70, 30, &style);
	input_dungeonWidth.setPlaceholder("Width");
	input_dungeonWidth.setInt(32);

	InputField input_dungeonHeight(0, 0, 70, 30, &style);
	input_dungeonHeight.setPlaceholder("Height");
	input_dungeonHeight.setInt(32);

	HorizontalLayout hLayout_inputDungeonSize(0, 0, 0, 30);
	hLayout_inputDungeonSize.setSpacing(10);
	hLayout_inputDungeonSize.add(input_dungeonWidth);
	hLayout_inputDungeonSize.add(input_dungeonHeight);

	Label lbl_roomMinSize(0, 0, 0, 20, &style);
	lbl_roomMinSize.setText("Room Min Size");
	lbl_roomMinSize.setAlignement(ALIGN_RIGHT);

	InputField input_roomMinWidth(0, 0, 70, 30, &style);
	input_roomMinWidth.setPlaceholder("min W");
	input_roomMinWidth.setInt(3);

	InputField input_roomMinHeight(0, 0, 70, 30, &style);
	input_roomMinHeight.setPlaceholder("min H");
	input_roomMinHeight.setInt(3);

	HorizontalLayout hLayout_inputRoomMinSize(0, 0, 0, 30);
	hLayout_inputRoomMinSize.setSpacing(10);
	hLayout_inputRoomMinSize.add(input_roomMinWidth);
	hLayout_inputRoomMinSize.add(input_roomMinHeight);

	Label lbl_roomMaxSize(0, 0, 0, 20, &style);
	lbl_roomMaxSize.setText("Room Max Size");
	lbl_roomMaxSize.setAlignement(ALIGN_RIGHT);

	InputField input_roomMaxWidth(0, 0, 70, 30, &style);
	input_roomMaxWidth.setPlaceholder("min W");
	input_roomMaxWidth.setInt(15);

	InputField input_roomMaxHeight(0, 0, 70, 30, &style);
	input_roomMaxHeight.setPlaceholder("min H");
	input_roomMaxHeight.setInt(15);

	HorizontalLayout hLayout_inputRoomMaxSize(0, 0, 0, 30);
	hLayout_inputRoomMaxSize.setSpacing(10);
	hLayout_inputRoomMaxSize.add(input_roomMaxWidth);
	hLayout_inputRoomMaxSize.add(input_roomMaxHeight);


	Label lbl_seed(0, 0, 0, 20, &style);
	lbl_seed.setText("Seed");
	lbl_seed.setAlignement(ALIGN_RIGHT);

	InputField input_seed(0, 0, 70, 30, &style);
	input_seed.setPlaceholder("seed");
	input_seed.setInt(0);

	Toggle toggle_randomSeed(0, 0, 0, 30, &style);
	toggle_randomSeed.setText("Random", font, 16);
	toggle_randomSeed.setChecked(true);

	VerticalLayout vLayout(0, 0, 170, 200);
	vLayout.setAnchorMin(sf::Vector2f(1, 0));
	vLayout.setAnchorMax(sf::Vector2f(1, 1));
	vLayout.setPivot(sf::Vector2f(1, 0));
	vLayout.setSpacing(10);
	vLayout.setPaddings(10, 10, 10, 10);
	vLayout.add(lbl_dungeonSize);
	vLayout.add(hLayout_inputDungeonSize);
	vLayout.add(lbl_roomMinSize);
	vLayout.add(hLayout_inputRoomMinSize);
	vLayout.add(lbl_roomMaxSize);
	vLayout.add(hLayout_inputRoomMaxSize);
	vLayout.add(lbl_seed);
	vLayout.add(input_seed);
	vLayout.add(toggle_randomSeed);
	vLayout.add(btn_Generate);
	vLayout.add(btn_showParents);
	vLayout.add(btn_showNeighbors);
	vLayout.add(btn_showLinks);
	vLayout.add(btn_showValues);

	Layout root(0, 0, Window::GetWidth(), Window::GetHeight());
	root.add(vLayout);
	root.add(lbl_fps);
	root.add(lbl_generation);
	Window::SetLayout(root);


	Grid grid(params.width, params.height, 640 / params.width, 640 / params.height, darkGrey);
	grid.setPosition(sf::Vector2f(50, 50));

	sf::RectangleShape rect(sf::Vector2f(grid.getCellWidth(), grid.getCellHeight()));
	rect.setFillColor(lightGrey);

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

		lbl_fps.setText("FPS: " + floatToStr(Time::GetFps(), 0));
		lbl_generation.setText("Nbr generation: " + floatToStr(nbGeneration, 0));

		if (btn_Generate.click() || Input::GetKeyDown(sf::Keyboard::G))
		{
			//cout << "Click !" << endl; 
			nbGeneration++;

			params.width = input_dungeonWidth.getInt();
			params.height = input_dungeonHeight.getInt();
			params.roomMinWidth = input_roomMinWidth.getInt();
			params.roomMaxWidth = input_roomMaxWidth.getInt();
			params.roomMinHeight = input_roomMinHeight.getInt();
			params.roomMaxHeight = input_roomMaxHeight.getInt();
			params.seed = input_seed.getInt();
			params.randomSeed = toggle_randomSeed.getChecked();
			dungeon.setParams(params);
			grid.setSize(params.width, params.height);
			grid.setCellSize(640 / params.width, 640 / params.height);
			dungeon.generate();
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

		Window::Draw();

		Window::Draw(grid);
		Window::Draw(rect);
		Window::Draw(renderer);

		// ///////////////////////// END DRAW
		Window::Display();
	}

	return 0;
}
