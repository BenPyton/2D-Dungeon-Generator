using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;
using UnityEngine.Events;

public class DungeonGenerator : MonoBehaviour {
    public static DungeonGenerator instance = null;

    [SerializeField] public Vector2Int dungeonSize = new Vector2Int(16, 16);
    [SerializeField] public Vector2Int roomMinSize = new Vector2Int(3, 3);
    [SerializeField] public Vector2Int roomMaxSize = new Vector2Int(8, 8);
    [SerializeField] public int nbMaxEnemies = 20;
    [SerializeField] public int nbMaxChest = 5;
    [SerializeField] public int nbLockedRoom = 1;
    [SerializeField] public ulong seed = 0;
    [SerializeField] public bool randomSeed = true;

    [SerializeField] GameObject prefabEmpty;
    [SerializeField] GameObject prefabWallSimple;
    [SerializeField] GameObject prefabWallCross;
    [SerializeField] GameObject prefabWallCorner;
    [SerializeField] GameObject prefabWallT;
    [SerializeField] GameObject prefabStairsDown;
    [SerializeField] GameObject prefabStairsUp;
    [SerializeField] GameObject prefabDoor;
    [SerializeField] GameObject prefabChest;
    [SerializeField] GameObject prefabEnemy;
    [SerializeField] GameObject prefabKey;
    [SerializeField] public float tileSize = 5.0f;

    private List<GameObject> tiles = new List<GameObject>();

    public UnityEvent onEndGenerate = new UnityEvent();
    [HideInInspector] public Vector3 entrancePosition = Vector3.zero;
    Dungeon dungeon = new Dungeon(16, 16);

    public DungeonParams Params { get { return dungeon.param; } private set { } }

    private void Awake()
    {
        if(instance == null)
        {
            instance = this;
            DontDestroyOnLoad(gameObject);
        }
        else
        {
            Destroy(gameObject);
        }
    }

    // Use this for initialization
    IEnumerator Start () {

        yield return new WaitForSeconds(0.1f);
        Generate();
	}

    public void Generate()
    {
        DungeonParams param = dungeon.param;
        param.maxChest = (char)nbMaxChest;
        param.maxEnemy = (char)nbMaxEnemies;
        param.width = (ulong)dungeonSize.x;
        param.height = (ulong)dungeonSize.y;
        param.roomMinWidth = (ulong)roomMinSize.x;
        param.roomMinHeight = (ulong)roomMinSize.x;
        param.roomMaxWidth = (ulong)roomMaxSize.x;
        param.roomMaxHeight = (ulong)roomMaxSize.x;
        param.nbLockedRoom = (char)nbLockedRoom;
        param.randomSeed = randomSeed;
        param.seed = seed;

        dungeon.param = param;
        dungeon.Generate();

        if(randomSeed)
        {
            seed = dungeon.param.seed;
        }

        foreach(GameObject tile in tiles)
        {
            Destroy(tile);
        }
        tiles.Clear();
        for (ulong x = 0; x < dungeon.param.width; x++)
        {
            for (ulong y = 0; y < dungeon.param.height; y++)
            {
                CreateTile(dungeon[x, y], x, y);
            }
        }

        onEndGenerate.Invoke();

        Debug.Log("done!");
    }
	
	// Update is called once per frame
	void Update () {
		if(Input.GetKeyDown(KeyCode.G))
        {
            Generate();
        }
    }
    
    void CreateTile(TileType value, ulong x, ulong y)
    {
        GameObject obj = null;
        Color color = Color.white;
        float angle = 0;
        switch (value)
        {
            case TileType.Empty:
            case TileType.Enemy:
            case TileType.Key:
            case TileType.Chest:
                obj = Instantiate(prefabEmpty, transform);
                break;
            case TileType.In:
                obj = Instantiate(prefabStairsDown, transform);
                color = Color.green;
                break;
            case TileType.Out:
                obj = Instantiate(prefabStairsUp, transform);
                color = Color.green;
                break;
            case TileType.Wall:
                int neighbors = CheckNeighbors(x, y, TileType.Wall, TileType.Door, TileType.LockedDoor);
                //color = new Color((neighbors % 4) / 4.0f, (neighbors / 4) / 4.0f, 0);
                color = Color.gray;
                // instantiation
                switch (neighbors)
                {
                    case 0:
                        break;
                    case 1:
                    case 2:
                    case 4:
                    case 5:
                    case 8:
                    case 10:
                        obj = Instantiate(prefabWallSimple);
                        break;
                    case 3:
                    case 6:
                    case 9:
                    case 12:
                        obj = Instantiate(prefabWallCorner);
                        break;
                    case 7:
                    case 11:
                    case 13:
                    case 14:
                        obj = Instantiate(prefabWallT);
                        break;
                    case 15:
                        obj = Instantiate(prefabWallCross);
                        break;
                }

                // rotation
                switch (neighbors)
                {
                    case 0:
                        break;
                    case 1:
                    case 4:
                    case 5:
                    case 12:
                    case 13:
                    case 15:
                        angle = 0;
                        break;
                    case 2:
                    case 6:
                    case 8:
                    case 10:
                    case 14:
                        angle = 90;
                        break;
                    case 3:
                    case 7:
                        angle = 180;
                        break;
                    case 9:
                    case 11:
                        angle = -90;
                        break;
                }
                break;
            case TileType.Door:
                obj = Instantiate(prefabDoor, transform);
                color = Color.blue;
                angle = 0;
                if(CheckNeighbors(x, y, TileType.Wall) == 10)
                {
                    angle = 90;
                }
                break;
            case TileType.LockedDoor:
                obj = Instantiate(prefabDoor, transform);
                color = Color.red;
                angle = 0;
                if (CheckNeighbors(x, y, TileType.Wall) == 10)
                {
                    angle = 90;
                }
                break;
            default:break;
        }
        if (obj != null)
        {
            obj.transform.position = Vector3.forward * tileSize * y + Vector3.right * tileSize * x;
            obj.transform.rotation = Quaternion.Euler(0, angle, 0);
            foreach(MeshRenderer mesh in obj.GetComponentsInChildren<MeshRenderer>())
            {
                mesh.material.color = color;
            }

            switch(value)
            {
                case TileType.In:
                    entrancePosition = obj.transform.position;
                    break;

                case TileType.Chest:
                    if (prefabChest != null)
                    {
                        GameObject chest = Instantiate(prefabChest, transform);
                        chest.transform.position = obj.transform.position;
                        tiles.Add(chest);
                    }
                    break;
                case TileType.Enemy:
                    if (prefabEnemy != null)
                    {
                        GameObject enemy = Instantiate(prefabEnemy, transform);
                        enemy.transform.position = obj.transform.position;
                        tiles.Add(enemy);
                    }
                    break;
                case TileType.Key:
                    if (prefabKey != null)
                    {
                        GameObject key = Instantiate(prefabKey, transform);
                        key.transform.position = obj.transform.position;
                        tiles.Add(key);
                    }
                    break;
                default:
                    break;
            }
            tiles.Add(obj);
        }
    }



    int CheckNeighbors(ulong x, ulong y, params TileType[] values)
    {
        int bitarray = 0;


        /*    | 2 |
         * ---+---+---
         *  1 |x,y| 4
         * ---+---+---
         *    | 8 |
         *    
         *                              X           X
         *   0 =  O     1 = XO     2 =  O      3 = XO
         *  
         *                   
         *                              X           X
         *   4 =  OX    5 = XOX    6 =  OX     7 = XOX
         *                                  
         *                    
         *                              X           X
         *   8 =  O     9 = XO     10=  O      11= XO 
         *        X          X          X           X 
         *                   
         *                              X           X
         *   12=  OX    13= XOX    14=  OX     15= XOX 
         *        X          X          X           X
         */

        foreach (TileType value in values)
        {
            if (x > 0 && dungeon[x - 1, y] == value)
            {
                bitarray |= 1 << 0;
            }

            if (y > 0 && dungeon[x, y - 1] == value)
            {
                bitarray |= 1 << 1;
            }

            if (x < dungeon.param.width - 1 && dungeon[x + 1, y] == value)
            {
                bitarray |= 1 << 2;
            }

            if (y < dungeon.param.height - 1 && dungeon[x, y + 1] == value)
            {
                bitarray |= 1 << 3;
            }
        }

        return bitarray;
    }
}
