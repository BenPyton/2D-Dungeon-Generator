# 2D Dungeon Generator

<b>Author :</b> PELLETIER Benoît

<img src="images/screen_sfml_view.jpg?raw=true" width="400"></img>
<img src="images/screen_unity_plugin.jpg?raw=true" width="440"></img>

### Description :
2D Dungeon Generator is a C++ library I made for a school project. <br>
The generation use BSP (Binary Space Partitionning) algorithm. 
The placement of enemies and chests are totally random, and key placement use bidirectional BFS (Breadth First Search) path finding algorithm.<br>
A SFML view project is provided to have a visual and a simple interface of the generator, allowing to play with it.<br>
A Unity plugin is present in the Unity sample allowing to generate dungeon also in Unity.

### Features :
- Create easily a dungeon with few lines of code,
- No restriction on dungeon size : It can be a square, or a rectangle from a width of 0 to 64000 !
- You can define number of enemies and chests in the dungeon,
- Rooms can be locked and keys are automatically generated with a valid path from the entrance to allow player to pick them up,
- A Unity plugin wraps the library to allow you tu use it in Unity as easily as the C++ library.

### Installation :
To use the library:
- Link your project to the dll if you want to use the shared library;
- Link to the lib and add the preprocessor LIBDUNGEON_STATIC if you want to use the static library.

To run the source of SFML view, or compile the library source, use Visual Studio 2015 or newer with this project. <br>
Please install one or both of VC++15 SFML from [here](https://www.sfml-dev.org/download/sfml/2.5.1/index-fr.php) at path:
- 32 bits: "$(SolutionDir)/../SFML-2.5.1"
- 64 bits: "$(SolutionDir)/../SFML-2.5.1-x64"

If you have any issues with compilation, first check the version of windows' SDK in project properties. <br>

To use the Unity plugin, copy the folder "Assets/Plugins/DungeonGenerator" from the sample project into your project "Assets/Plugins" folder.
You can use the DungeonGenerator component directly without coding, or code yourself a C# script using the library like in C++. 


### C++ Library Use :
```cpp
#include <DG/LibDungeon.h>

int main()
{
    // Initialization with some parameters
    DungeonParams params = DungeonParams::basic;
    params.width = 32;
    params.height = 32;
    params.roomMinWidth = 3;
    params.roomMinHeight = 3;
    params.roomMaxWidth = 15;
    params.roomMaxHeight = 15;
    Dungeon dungeon(params);


    // Generate the dungeon
    dungeon.generate();
  
    // Display dungeon values
    std::string str = "";
    for(size_t i = 0; i < params.height; i++)
    {
        for(size_t j = 0; j < params.width; j++)
        {
            str += dungeon.getValue(j, i);
        }
        str += "\n";
    }
    std::cout << str << std::endl;
  
    return 0;
}
```
