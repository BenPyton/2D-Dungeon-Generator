/*
* @author PELLETIER Benoit
*
* @file Utils.h
*
* @date 04/10/2018
*
* @brief Some utility functions
*
*/

#ifndef _UTILS_H
#define _UTILS_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <SFML/Graphics.hpp>


#define MAX_BUFFER_SIZE 1024

using namespace std;

string readFile(string filename);
string floatToStr(float number, int precision);
void drawPixel(sf::RenderWindow &window, sf::Vector2f pixel, sf::Color color);
void drawLine(sf::RenderWindow &window, sf::Vector2f p1, sf::Vector2f p2, sf::Color color);

#endif // _UTILS_H