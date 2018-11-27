/*
* @author PELLETIER Benoit
*
* @file Dungeon.cpp
*
* @date 15/10/2018
*
* @brief Define and generate dungeons
*
*/

#include "DG/Dungeon.h"
#include <chrono>
#include <cassert>

#define min(x, y) (x < y) ? x : y

Dungeon::Dungeon(uint64_t width, uint64_t height)
	: m_params(DungeonParams::basic), m_array(nullptr)
{
	m_params.width = width;
	m_params.height = height;
	_SetArraySize(m_params.width, m_params.height);
}

Dungeon::Dungeon(const DungeonParams & params)
	: m_params(params), m_array(nullptr)
{
	_SetArraySize(m_params.width, m_params.height);
}

Dungeon::~Dungeon()
{
	_ClearRoomList();
	_ClearArray();
}

Room * Dungeon::getRoomAt(uint64_t x, uint64_t y)
{
	Room* room = nullptr;
	for (vector<Room*>::iterator it = m_roomList.begin(); it != m_roomList.end(); ++it)
	{
		if ((*it)->isIn(x, y))
		{
			room = *it;
			break;
		}
	}

	return room;
}

void Dungeon::_SetArraySize(uint64_t _width, uint64_t _height)
{
	_ClearArray();

	m_array = (short**)malloc(_height * sizeof(short*));
	for (int i = 0; i < _height; i++)
	{
		m_array[i] = (short*)malloc(_width * sizeof(short));
		memset(m_array[i], 0, _width * sizeof(short));
	}
}

void Dungeon::generate()
{
	//_GenerateRooms(iteration);
	if (m_params.randomSeed)
	{
		m_seed = chrono::high_resolution_clock::now().time_since_epoch().count();
	}
	else
	{
		m_seed = m_params.seed;
	}
	printf("Seed: %u\n", m_seed);
	srand(m_seed);

	_ClearRoomList();
	// create root room
	m_roomList.push_back(new Room(0, 0, m_params.width, m_params.height));
	_SplitRoomRecursive(64, m_roomList[0], _RandRange(0, 2) == 1 ? true : false);

	// list neighbors of each room
	for (vector<Room*>::iterator it = m_roomList.begin(); it != m_roomList.end(); ++it)
	{
		_ListNeighbors(*it);
	}

	_FillArray();
}

short Dungeon::getValue(uint64_t x, uint64_t y)
{
	assert(nullptr != m_array && x < m_params.width && y < m_params.height);
	return m_array[y][x];
}

void Dungeon::setValue(uint64_t x, uint64_t y, short value)
{
	assert(nullptr != m_array && x < m_params.width && y < m_params.height);
	m_array[y][x] = value;
}

void Dungeon::setParams(const DungeonParams & params)
{
	_SetArraySize(params.width, params.height);
	m_params = params;
}

int Dungeon::_RandRange(int min, int max)
{
	if (min == max)
		return min;
	if (min > max)
	{
		int tmp = min;
		min = max;
		max = tmp;
	}
	return rand() % (max - min) + min;
}

void Dungeon::_ClearRoomList()
{
	for (vector<Room*>::iterator it = m_roomList.begin(); it != m_roomList.end(); ++it)
	{
		delete *it;
	}
	m_roomList.clear();
}

void Dungeon::_ClearArray()
{
	if (nullptr != m_array)
	{
		for (uint64_t i = 0; i < m_params.height; i++)
		{
			delete[] m_array[i];
		}
		delete[] m_array;
		m_array = nullptr;
	}
}

void Dungeon::_GenerateRooms(int iteration)
{
	bool vertical = true;
	int splitX = 0, splitY = 0;

	_ClearRoomList();

	// create root room
	m_roomList.push_back(new Room(0, 0, m_params.width, m_params.height));

	for (int i = 0; i < iteration; i++)
	{
		int nbRoom = m_roomList.size(); // store it because it change in the for loop
		for (int k = 0; k < nbRoom; k++)
		{
			// Split the room in two rooms
			if (vertical)
			{
				splitX = _RandRange(1, m_roomList[k]->getWidth());
				splitY = 0;
			}
			else
			{
				splitX = 0;
				splitY = _RandRange(1, m_roomList[k]->getHeight());
			}


			// create new room to subdivide the current room
			Room* newRoom = new Room;
			newRoom->setX(m_roomList[k]->getX() + splitX);
			newRoom->setY(m_roomList[k]->getY() + splitY);
			newRoom->setWidth(m_roomList[k]->getWidth() - splitX);
			newRoom->setHeight(m_roomList[k]->getHeight() - splitY);
			newRoom->setParent(m_roomList[k]);

			// adjust size of the current room
			if (vertical)
			{
				m_roomList[k]->setWidth(splitX);
			}
			else
			{
				m_roomList[k]->setHeight(splitY);
			}

			// None of the two rooms are too small
			if (newRoom->getWidth() >= m_params.roomMinWidth && newRoom->getHeight() > m_params.roomMinHeight
				&& m_roomList[k]->getWidth() > m_params.roomMinWidth && m_roomList[k]->getHeight() > m_params.roomMinHeight)
			{
				// Add new room in the list
				newRoom->setId(m_roomList.size());
				m_roomList.push_back(newRoom);
			}
			else // One of them is too small
			{
				// reset room size and DON'T add the new room
				m_roomList[k]->setWidth(splitX + newRoom->getWidth());
				m_roomList[k]->setHeight(splitY + newRoom->getHeight());

				// free memory
				delete newRoom;
			}
		}
		vertical = !vertical; // toggle vertical split
	}

	// list neighbors of each room
	for (vector<Room*>::iterator it = m_roomList.begin(); it != m_roomList.end(); ++it)
	{
		_ListNeighbors(*it);
	}
}

void Dungeon::_SplitRoomRecursive(int _iteration, Room* _r, bool _vertical)
{
	if (_iteration > 0)
	{
		int splitX = -1, splitY = -1;

		// Split the room in two rooms
		/*if (_vertical)
		{
			splitX = _RandRange(1, _r->getWidth());
			splitY = 0;
		}
		else
		{
			splitX = 0;
			splitY = _RandRange(1, _r->getHeight());
		}*/

		int vertical = -1;
		if (_r->getWidth() > m_params.roomMaxWidth && _r->getHeight() > m_params.roomMaxHeight)
		{ // Max width AND max height are exceeded
			vertical = _RandRange(0, 2);
		}
		else if (_r->getWidth() > m_params.roomMaxWidth)
		{ // Only width is exceeded
			vertical = 1;
		}
		else if (_r->getHeight() > m_params.roomMaxHeight)
		{ // Only height is exceeded
			vertical = 0;
		}
		// None of them are exceeded so we don't split anymore

		if (vertical == 1)
		{
			splitX = _RandRange(1, _r->getWidth()); 
			splitY = 0;
		}
		else if (vertical == 0)
		{
			splitX = 0;
			splitY = _RandRange(1, _r->getHeight());
		}

		if (splitX != -1 && splitY != -1)
		{
			// create new room to subdivide the current room
			Room* newRoom = new Room;
			newRoom->setX(_r->getX() + splitX);
			newRoom->setY(_r->getY() + splitY);
			newRoom->setWidth(_r->getWidth() - splitX);
			newRoom->setHeight(_r->getHeight() - splitY);
			newRoom->setParent(_r);

			// adjust size of the current room
			if (_vertical)
			{
				_r->setWidth(splitX);
			}
			else
			{
				_r->setHeight(splitY);
			}

			// None of the two rooms are too small
			if (newRoom->getWidth() >= m_params.roomMinWidth && newRoom->getHeight() > m_params.roomMinHeight
				&& _r->getWidth() > m_params.roomMinWidth && _r->getHeight() > m_params.roomMinHeight)
			{
				// Add new room in the list
				newRoom->setId(m_roomList.size());
				m_roomList.push_back(newRoom);

				_SplitRoomRecursive(_iteration-1, _r, false);
				_SplitRoomRecursive(_iteration-1, newRoom, false);
			}
			else // One of them is too small
			{
				// reset room size and DON'T add the new room
				_r->setWidth(splitX + newRoom->getWidth());
				_r->setHeight(splitY + newRoom->getHeight());

				// free memory
				delete newRoom;

				_SplitRoomRecursive(_iteration-1, _r, !_vertical);
			}
		}
	}
}

void Dungeon::_FillArray()
{
	if (nullptr != m_array)
	{
		_ResetArray();

		// make walls
		for (vector<Room*>::iterator it = m_roomList.begin(); it != m_roomList.end(); ++it)
		{
			Room* room = *it;

			for (int i = 0; i < room->getHeight(); i++)
			{
				m_array[room->getY() + i][room->getX()] = TileType::Wall;
			}

			for (int i = 0; i < room->getWidth(); i++)
			{
				m_array[room->getY()][room->getX() + i] = TileType::Wall;
			}

			for (int i = 0; i < m_params.height; i++)
			{
				m_array[i][m_params.width - 1] = TileType::Wall;
			}

			for (int i = 0; i < m_params.width; i++)
			{
				m_array[m_params.height - 1][i] = TileType::Wall;
			}
		}


		// Place doors
		for (vector<Room*>::iterator it = m_roomList.begin(); it != m_roomList.end(); ++it)
		{
			Room* room = *it;
			bool vertical = false;
			bool horizontal = false;
			int n = 0;

			if (room->getX() != 0 || room->getY() != 0)
			{
				int nbDoor = 1; // _RandRange(1, 3);
				for (int k = 0; k < nbDoor; k++)
				{
					if (room->getX() == 0) // only horizontal wall
					{
						vertical = false;
						horizontal = true;
					}
					else if (room->getY() == 0) // only vertical wall
					{
						vertical = true;
						horizontal = false;
					}
					else // choose randomly vertical or horizontal wall
					{
						vertical = _RandRange(0, 2) == 0;
						horizontal = !vertical || _RandRange(0, 2) == 0;
					}


					if (vertical) 
					{
						do {
							n = room->getY() + _RandRange(1, (room->getY() + room->getHeight() == m_params.height) ? room->getHeight() - 1 : room->getHeight());
						} while (m_array[n][room->getX() - 1] != TileType::Empty);
						m_array[n][room->getX()] = TileType::Door;
						Room* other = getRoomAt(room->getX() - 1, n);
						room->addLink(other);
						other->addLink(room);
					}
					if(horizontal)
					{
						do {
							n = room->getX() + _RandRange(1, (room->getX() + room->getWidth() == m_params.width) ? room->getWidth() - 1 : room->getWidth());
						} while (m_array[room->getY() - 1][n] != TileType::Empty);
						m_array[room->getY()][n] = TileType::Door;
						Room* other = getRoomAt(n, room->getY() - 1);
						room->addLink(other);
						other->addLink(room);
					}
				}
			}
		}

		// Random coordinates
		int randX = 0, randY = 0;
		
		// Add an in 
		Room* inputRoom = m_roomList[_RandRange(0, m_roomList.size())];
		if (_GetEmptyCell(randX, randY, inputRoom))
		{
			m_array[randY][randX] = TileType::In;
		}

		// Add an out
		Room* outRoom = m_roomList[_RandRange(0, m_roomList.size())];
		if (_GetEmptyCell(randX, randY, outRoom))
		{
			m_array[randY][randX] = TileType::Out;
		}

		// Add chests
		//if (m_params.maxChest > 0)
		//{
		//	int nbChestLeft = m_params.maxChest - 1;
		//	for (vector<Room*>::iterator it = m_roomList.begin(); it != m_roomList.end(); ++it)
		//	{
		//		Room* room = *it;

		//		if (room != inputRoom && room != outRoom)
		//		{
		//			int placeChest = _RandRange(0, 2); // 50% chance to place chest in the room
		//			int n = _RandRange(0, min(nbChestLeft, m_params.maxChestPerRoom)) + 1; // can place up to max chests in the room
		//			if (placeChest == 0)
		//			{
		//				for (int i = 0; i < n; i++)
		//				{
		//					if (_GetEmptyCell(room, randX, randY))
		//					{
		//						m_array[randY][randX] = TileType::Chest;
		//						nbChestLeft--;
		//					}
		//				}
		//			}
		//		}
		//	}
		//}

		// Add chests
		for (int i = 0; i < m_params.maxChest; i++)
		{
			if (_GetEmptyCell(randX, randY))
			{
				m_array[randY][randX] = TileType::Chest;
			}
		}

		// Add enemies
		for (int i = 0; i < m_params.maxEnemy; i++)
		{
			if (_GetEmptyCell(randX, randY))
			{
				m_array[randY][randX] = TileType::Enemy;
			}
		}

		// Add Enemies
		//if (m_params.maxEnemy > 0)
		//{
		//	int nbEnemyLeft = m_params.maxEnemy - 1;
		//	for (vector<Room*>::iterator it = m_roomList.begin(); it != m_roomList.end(); ++it)
		//	{
		//		Room* room = *it;

		//		if (room != inputRoom && room != outRoom)
		//		{
		//			int placeChest = _RandRange(0, 2); // 50% chance to place enemies in the room
		//			int n = _RandRange(0, min(nbEnemyLeft, m_params.maxEnemyPerRoom)) + 1; // can place up to max enemies in the room
		//			if (placeChest == 0)
		//			{
		//				for (int i = 0; i < n; i++)
		//				{
		//					if (_GetEmptyCell(randX, randY, room))
		//					{
		//						m_array[randY][randX] = TileType::Enemy;
		//						nbEnemyLeft--;
		//					}
		//				}
		//			}
		//		}
		//	}
		//}
	}
}

void Dungeon::_ResetArray()
{
	if (nullptr != m_array)
	{
		for (int i = 0; i < m_params.height; i++)
		{
			memset(m_array[i], 0, m_params.width * sizeof(short));
		}
	}
}

void Dungeon::_ListNeighbors(Room * r)
{
	for (vector<Room*>::iterator it = m_roomList.begin(); it != m_roomList.end(); ++it)
	{
		Room* other = *it;

		// they are closed to each other in X
		if (other->getX() + other->getWidth() == r->getX()
			|| other->getX() == r->getX() + r->getWidth())
		{
			if (!(other->getY() + other->getHeight() <= r->getY() || other->getY() >= r->getY() + r->getHeight()))
			{
				r->addNeighbor(other);
			}
		}

		// they are closed to each other in X
		if (other->getY() + other->getHeight() == r->getY()
			|| other->getY() == r->getY() + r->getHeight())
		{
			if (!(other->getX() + other->getWidth() <= r->getX() || other->getX() >= r->getX() + r->getWidth()))
			{
				r->addNeighbor(other);
			}
		}
	}
}

bool Dungeon::_GetEmptyCell(int & x, int & y, Room * r)
{
	bool success = false;
	int maxTry = 500;

	// check if there is any empty cell in room
	/*for (uint64_t i = 1; i < r->getWidth() && !success; i++)
	{
		for (uint64_t j = 1; j < r->getHeight() && !success; j++)
		{
			if (m_array[j][i] == TileType::Empty)
			{
				success = true;
			}
		}
	}*/
	success = true;

	//cout << "Is empty cell ? " << success;

	if (success)
	{
		//cout << " | Get random cell...";
		if (nullptr != r)
		{
			do {
				x = r->getX() + _RandRange(1, r->getWidth());
				y = r->getY() + _RandRange(1, r->getHeight());
				maxTry--;
			} while (maxTry > 0 && m_array[y][x] != TileType::Empty);
		}
		else
		{
			do {
				x = _RandRange(1, m_params.width);
				y = _RandRange(1, m_params.height);
				maxTry--;
			} while (maxTry > 0 && m_array[y][x] != TileType::Empty);
		}
	}

	//cout << " | Done!" << endl;

	return success;
}



// Functions to wrap in a Room.cs for Unity
#ifdef _UNITY

Dungeon* Lib_Dungeon_constructor(uint64_t _width, uint64_t _height)
{
	return new Dungeon(_width, _height);
}
Dungeon* Lib_Dungeon_paramsConstructor(const DungeonParams& _params)
{
	return new Dungeon(_params);
}
void Lib_Dungeon_destructor(Dungeon* _this)
{
	delete _this;
}

size_t Lib_Dungeon_getRoomCount(Dungeon* _this)
{
	return _this->getRoomCount();
}
Room* Lib_Dungeon_getRoom(Dungeon* _this, int _index)
{
	return _this->getRoom(_index);
}
Room* Lib_Dungeon_getRoomAt(Dungeon* _this, uint64_t _x, uint64_t _y)
{
	return _this->getRoomAt(_x, _y);
}

void Lib_Dungeon_generate(Dungeon* _this)
{
	_this->generate();
}

short Lib_Dungeon_getValue(Dungeon* _this, uint64_t _x, uint64_t _y)
{
	return _this->getValue(_x, _y);
}
void Lib_Dungeon_setValue(Dungeon* _this, uint64_t _x, uint64_t _y, short _value)
{
	_this->setValue(_x, _y, _value);
}

DungeonParams Lib_Dungeon_getParams(Dungeon* _this)
{
	return _this->getParams();
}
void Lib_Dungeon_setParams(Dungeon* _this, const DungeonParams& _params)
{
	_this->setParams(_params);
}

#endif // _DUNGEON_H