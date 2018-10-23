/*
* @author PELLETIER Benoit
*
* @file DungeonParams.h
*
* @date 23/10/2018
*
* @brief Define all params of a dungeon generation
*
*/

#ifndef _DUNGEONPARAMS_H
#define _DUNGEONPARAMS_H

#include <iostream>

using namespace std;

struct DungeonParams
{
	uint64_t width;
	uint64_t height;
	uint64_t roomMinWidth;
	uint64_t roomMinHeight;
	uint64_t roomMaxWidth;
	uint64_t roomMaxHeight;
	uint8_t iteration;

	static DungeonParams zero;
	static DungeonParams basic;
};

#endif // _DUNGEONPARAMS_H