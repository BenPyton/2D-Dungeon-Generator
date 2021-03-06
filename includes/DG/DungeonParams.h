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
#include "Exports.h"

using namespace std;

extern "C"
{
	struct LIBDUNGEON_API DungeonParams
	{
		uint64_t width;
		uint64_t height;
		uint64_t roomMinWidth;
		uint64_t roomMinHeight;
		uint64_t roomMaxWidth;
		uint64_t roomMaxHeight;
		uint8_t iteration;
		uint8_t maxChest;
		uint8_t maxChestPerRoom;
		uint8_t maxEnemy;
		uint8_t maxEnemyPerRoom;
		uint8_t nbLockedRoom;
		bool randomSeed;
		uint64_t seed;

		static const DungeonParams basic;
		static const DungeonParams zero;
	};
}

#endif // _DUNGEONPARAMS_H