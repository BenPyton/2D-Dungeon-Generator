using System;
using System.Runtime.InteropServices;



public enum TileType : short
{
	Empty = 0,
	Wall,
	In,
	Out,
	Door,
	LockedDoor,
	Key,
	Chest,
	Enemy
};

public class Dungeon : IDisposable
{
    private IntPtr m_handle = IntPtr.Zero;

    public TileType this[UInt64 x, UInt64 y]
    {
        get { _CheckPtr(); return (TileType)Lib_Dungeon_getValue(m_handle, x, y); }
        set { _CheckPtr(); Lib_Dungeon_setValue(m_handle, x, y, (short)value); }
    }

    public DungeonParams param {
        get { _CheckPtr(); return Lib_Dungeon_getParams(m_handle); }
        set { _CheckPtr(); Lib_Dungeon_setParams(m_handle, value); }
    }

    public UInt32 roomCount
    {
        get { _CheckPtr(); return Lib_Dungeon_getRoomCount(m_handle); }
    }

    public Dungeon(UInt64 width, UInt64 height)
    {
        m_handle = Lib_Dungeon_constructor(width, height);
    }

    public Dungeon(DungeonParams p)
    {
        m_handle = Lib_Dungeon_paramsConstructor(p);
    }

    ~Dungeon()
    {
        Dispose();
    }

    public void Dispose()
    {
        if (IntPtr.Zero != m_handle)
        {
            Lib_Dungeon_destructor(m_handle);
        }
    }

    public void Generate()
    {
        _CheckPtr();
        Lib_Dungeon_generate(m_handle);
    }

    public Room GetRoom(int index)
    {
        _CheckPtr();
        return new Room(Lib_Dungeon_getRoom(m_handle, index));
    }

    public Room GetRoomAt(UInt64 x, UInt64 y)
    {
        _CheckPtr();
        return new Room(Lib_Dungeon_getRoomAt(m_handle, x, y));
    }

    private void _CheckPtr()
    {
        if (IntPtr.Zero == m_handle)
            throw new Exception("Dungeon is null");
    }

    // Function import
    [DllImport("DungeonGenerator")] private static extern IntPtr Lib_Dungeon_constructor(UInt64 _width, UInt64 _height);
    [DllImport("DungeonGenerator", CallingConvention = CallingConvention.Cdecl)] private static extern IntPtr Lib_Dungeon_paramsConstructor(DungeonParams _params);
    [DllImport("DungeonGenerator")] private static extern void Lib_Dungeon_destructor(IntPtr _this);

    [DllImport("DungeonGenerator")] private static extern UInt32 Lib_Dungeon_getRoomCount(IntPtr _this);
    [DllImport("DungeonGenerator")] private static extern IntPtr Lib_Dungeon_getRoom(IntPtr _this, int _index);
    [DllImport("DungeonGenerator")] private static extern IntPtr Lib_Dungeon_getRoomAt(IntPtr _this, UInt64 _x, UInt64 _y);
    [DllImport("DungeonGenerator")] private static extern void Lib_Dungeon_generate(IntPtr _this);
    [DllImport("DungeonGenerator")] private static extern short Lib_Dungeon_getValue(IntPtr _this, UInt64 x, UInt64 _y);
    [DllImport("DungeonGenerator")] private static extern void Lib_Dungeon_setValue(IntPtr _this, UInt64 _x, UInt64 _y, short _value);
    [DllImport("DungeonGenerator", CallingConvention = CallingConvention.Cdecl)] private static extern DungeonParams Lib_Dungeon_getParams(IntPtr _this);
    [DllImport("DungeonGenerator", CallingConvention = CallingConvention.Cdecl)] private static extern void Lib_Dungeon_setParams(IntPtr _this, DungeonParams _params);
}
