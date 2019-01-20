using System;
using System.Runtime.InteropServices;

[StructLayout(LayoutKind.Explicit, CharSet = CharSet.Unicode)]
public struct DungeonParams
{
    [FieldOffset(0)] public ulong width;
    [FieldOffset(8)] public ulong height;
    [FieldOffset(16)] public ulong roomMinWidth;
    [FieldOffset(24)] public ulong roomMinHeight;
    [FieldOffset(32)] public ulong roomMaxWidth;
    [FieldOffset(40)] public ulong roomMaxHeight;
    [FieldOffset(48)] public char iteration;
    [FieldOffset(49)] public char maxChest;
    [FieldOffset(50)] public char maxChestPerRoom;
    [FieldOffset(51)] public char maxEnemy;
    [FieldOffset(52)] public char maxEnemyPerRoom;
    [FieldOffset(53)] public char nbLockedRoom;
    [FieldOffset(54)] public bool randomSeed;
    [FieldOffset(56)] public ulong seed;

    static DungeonParams zero = new DungeonParams {
        width = 0,
        height = 0,
        roomMinWidth = 0,
        roomMinHeight = 0,
        roomMaxWidth = 0,
        roomMaxHeight = 0,
        iteration = (char)0,
        maxChest = (char)0,
        maxChestPerRoom = (char)0,
        maxEnemy = (char)0,
        maxEnemyPerRoom = (char)0,
        nbLockedRoom = (char)0,
        seed = 0,
        randomSeed = false
    };

    static DungeonParams basic = new DungeonParams
    {
        width = 64,
        height = 64,
        roomMinWidth = 3,
        roomMinHeight = 3,
        roomMaxWidth = 0,
        roomMaxHeight = 0,
        iteration = (char)5,
        maxChest = (char)5,
        maxChestPerRoom = (char)2,
        maxEnemy = (char)20,
        maxEnemyPerRoom = (char)5,
        nbLockedRoom = (char)1,
        seed = 0,
        randomSeed = true
    };
}
