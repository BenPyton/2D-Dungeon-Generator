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

const DungeonParams DungeonParams::zero(
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
	);

const DungeonParams DungeonParams::basic(
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
	);

DungeonParams::DungeonParams(uint64_t _width, uint64_t _height, uint64_t _roomMinWidth, uint64_t _roomMinHeight, uint64_t _roomMaxWidth, uint64_t _roomMaxHeight, uint8_t _iteration, uint8_t _maxChest, uint8_t _maxChestPerRoom, uint8_t _maxEnemy, uint8_t _maxEnemyPerRoom)
	: width(_width), height(_height), roomMinWidth(_roomMinWidth), roomMinHeight(_roomMinHeight), roomMaxWidth(_roomMaxWidth), roomMaxHeight(_roomMaxHeight), iteration(_iteration), maxChest(_maxChest), maxChestPerRoom(_maxChestPerRoom), maxEnemy(_maxEnemy), maxEnemyPerRoom(_maxEnemyPerRoom)
{
}

DungeonParams Lib_DungeonParams_constructor(uint64_t _width, uint64_t _height, uint64_t _roomMinWidth, uint64_t _roomMinHeight, uint64_t _roomMaxWidth, uint64_t _roomMaxHeight, uint8_t _iteration, uint8_t _maxChest, uint8_t _maxChestPerRoom, uint8_t _maxEnemy, uint8_t _maxEnemyPerRoom)
{
	return DungeonParams(_width, _height, _roomMinWidth, _roomMinHeight, _roomMaxWidth, _roomMaxHeight, _iteration, _maxChest, _maxChestPerRoom, _maxEnemy, _maxEnemyPerRoom);
}
