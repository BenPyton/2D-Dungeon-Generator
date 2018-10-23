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
	0, // iteration
	0, // maxChest
	0, // maxChestPerRoom
	0, // maxEnemy
	0  // maxEnemyPerRoom
};

DungeonParams DungeonParams::basic = {
	64, // width
	64, // height
	3, // roomMinWidth
	3, // roomMinHeight
	0, // roomMaxWidth
	0, // roomMaxHeight
	5, // iteration
	5, // maxChest
	2, // maxChestPerRoom
	20,// maxEnemy
	5  // maxEnemyPerRoom
};

