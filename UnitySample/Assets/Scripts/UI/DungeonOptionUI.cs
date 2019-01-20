using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class DungeonOptionUI : MonoBehaviour {

    [SerializeField] InputField inputSeed;
    [SerializeField] Toggle toggleRandomSeed;
    [SerializeField] InputField inputDungeonWidth;
    [SerializeField] InputField inputDungeonHeight;
    [SerializeField] InputField inputRoomMinWidth;
    [SerializeField] InputField inputRoomMinHeight;
    [SerializeField] InputField inputRoomMaxWidth;
    [SerializeField] InputField inputRoomMaxHeight;
    [SerializeField] InputField inputNbEnemy;
    [SerializeField] InputField inputNbChest;
    [SerializeField] InputField inputNbLockedRoom;
    [SerializeField] Button buttonGenerate;

    DungeonGenerator dg = null;
    // Use this for initialization
    void Start ()
    {
        dg = DungeonGenerator.instance;

        buttonGenerate.onClick.AddListener(() =>
        {
            int value = 0;
            ulong valueLong = 0;
            dg.dungeonSize = new Vector2Int(int.TryParse(inputDungeonWidth.text, out value) ? value : dg.dungeonSize.x, int.TryParse(inputDungeonHeight.text, out value) ? value : dg.dungeonSize.y);
            dg.roomMinSize = new Vector2Int(int.TryParse(inputRoomMinWidth.text, out value) ? value : dg.roomMinSize.x, int.TryParse(inputRoomMinHeight.text, out value) ? value : dg.roomMinSize.y);
            dg.roomMaxSize = new Vector2Int(int.TryParse(inputRoomMaxWidth.text, out value) ? value : dg.roomMaxSize.x, int.TryParse(inputRoomMaxHeight.text, out value) ? value : dg.roomMaxSize.y);
            dg.nbMaxEnemies = int.TryParse(inputNbEnemy.text, out value) ? value : dg.nbMaxEnemies;
            dg.nbMaxChest = int.TryParse(inputNbChest.text, out value) ? value : dg.nbMaxChest;
            dg.nbLockedRoom = int.TryParse(inputNbLockedRoom.text, out value) ? value : dg.nbLockedRoom;
            dg.randomSeed = toggleRandomSeed.isOn;
            dg.seed = ulong.TryParse(inputSeed.text, out valueLong) ? valueLong : dg.seed;
            dg.Generate();
        });

        inputSeed.text = dg.seed.ToString();
        toggleRandomSeed.isOn = dg.randomSeed;
        inputDungeonWidth.text = dg.dungeonSize.x.ToString();
        inputDungeonHeight.text = dg.dungeonSize.y.ToString();
        inputRoomMinWidth.text = dg.roomMinSize.x.ToString();
        inputRoomMinHeight.text = dg.roomMinSize.y.ToString();
        inputRoomMaxWidth.text = dg.roomMaxSize.x.ToString();
        inputRoomMaxHeight.text = dg.roomMaxSize.y.ToString();
        inputNbEnemy.text = dg.nbMaxEnemies.ToString();
        inputNbChest.text = dg.nbMaxChest.ToString();
        inputNbLockedRoom.text = dg.nbLockedRoom.ToString();
}
	
	// Update is called once per frame
	void Update () {
		
	}
}
