/*
* @author PELLETIER Benoit
*
* @file DungeonParams.cpp
*
* @date 23/10/2018
*
* @brief Define all params of a dungeon generation
*
*/

#include "DG/DungeonParams.h"

DungeonParams DungeonParams::zero = {
	0, // width
	0, // height
	0, // roomMinWidth
	0, // roomMinHeight
	0, // roomMaxWidth
	0, // roomMaxHeight
	0  // iteration
};

DungeonParams DungeonParams::basic = {
	64, // width
	64, // height
	3, // roomMinWidth
	3, // roomMinHeight
	0, // roomMaxWidth
	0, // roomMaxHeight
	5  // iteration
};

