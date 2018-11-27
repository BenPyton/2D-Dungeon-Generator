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
		uint64_t seed;
		bool randomSeed;

		static const DungeonParams basic;
		static const DungeonParams zero;

		DungeonParams(
			uint64_t _width,
			uint64_t _height,
			uint64_t _roomMinWidth,
			uint64_t _roomMinHeight,
			uint64_t _roomMaxWidth,
			uint64_t _roomMaxHeight,
			uint8_t _iteration,
			uint8_t _maxChest,
			uint8_t _maxChestPerRoom,
			uint8_t _maxEnemy,
			uint8_t _maxEnemyPerRoom,
			uint64_t _seed,
			bool _randomSeed
		);
	};


	// Functions to wrap in a Room.cs for Unity
#ifdef _UNITY
	LIBDUNGEON_API DungeonParams Lib_DungeonParams_constructor(
		uint64_t _width,
		uint64_t _height,
		uint64_t _roomMinWidth,
		uint64_t _roomMinHeight,
		uint64_t _roomMaxWidth,
		uint64_t _roomMaxHeight,
		uint8_t _iteration,
		uint8_t _maxChest,
		uint8_t _maxChestPerRoom,
		uint8_t _maxEnemy,
		uint8_t _maxEnemyPerRoom,
		uint64_t _seed,
		bool _randomSeed
	);
#endif
}

#endif // _DUNGEONPARAMS_H