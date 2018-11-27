# 2D Dungeon Generator

```diff
- WARNING: This project is under development, some features may not work yet.
```

<b>Author :</b> PELLETIER Benoit

### Description :
2D Dungeon Generator with BSP (Binary Space Partitionning) algorithm. <br>
Use Visual Studio 2015 or newer with this project. <br>
Please install one or both of VC++15 SFML from [here](https://www.sfml-dev.org/download/sfml/2.5.1/index-fr.php) at:
- 32 bits: "$(SolutionDir)/../SFML-2.5.1"
- 64 bits: "$(SolutionDir)/../SFML-2.5.1-x64"

If you have issues with compilation, check the version of windows' SDK in project properties. <br>

### Use :
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
