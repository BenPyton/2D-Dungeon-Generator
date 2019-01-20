using System;
using System.Runtime.InteropServices;

public class Room : IDisposable {

    private IntPtr m_handle = IntPtr.Zero;

    public UInt64 id {
        get { _CheckPtr(); return Lib_Room_getId(m_handle); }
        set { _CheckPtr(); Lib_Room_setId(m_handle, value); }
    }

    public int x
    {
        get { _CheckPtr(); return Lib_Room_getX(m_handle); }
        set { _CheckPtr(); Lib_Room_setX(m_handle, value); }
    }

    public int y
    {
        get { _CheckPtr(); return Lib_Room_getY(m_handle); }
        set { _CheckPtr(); Lib_Room_setY(m_handle, value); }
    }

    public int width
    {
        get { _CheckPtr(); return Lib_Room_getWidth(m_handle); }
        set { _CheckPtr(); Lib_Room_setWidth(m_handle, value); }
    }

    public int height
    {
        get { _CheckPtr(); return Lib_Room_getHeight(m_handle); }
        set { _CheckPtr(); Lib_Room_setHeight(m_handle, value); }
    }

    // I don't know how to do this
    public Room parent
    {
        get { _CheckPtr(); return new Room(Lib_Room_getParent(m_handle)); }
        set { _CheckPtr(); Lib_Room_setParent(m_handle, value.m_handle); }
    }

    public UInt32 neighborCount
    {
        get { _CheckPtr(); return Lib_Room_getNeighborCount(m_handle); }
    }

    public UInt32 linkCount
    {
        get { _CheckPtr(); return Lib_Room_getLinkCount(m_handle); }
    }

    public bool locked
    {
        get { _CheckPtr(); return Lib_Room_isLocked(m_handle); }
        set { _CheckPtr(); Lib_Room_setLocked(m_handle, value); }
    }


    public Room(int x = 0, int y = 0, int w = 1, int h = 1)
    {
        m_handle = Lib_Room_constructor(x, y, w, h);
    }

    public Room(Room room)
    {
        m_handle = Lib_Room_copyConstructor(room.m_handle);
    }

    public Room(IntPtr _internal_constructor_do_not_call_it)
    {
        m_handle = _internal_constructor_do_not_call_it;
    }

    ~Room()
    {
        Dispose();
    }

    public void Dispose()
    {
        if (IntPtr.Zero != m_handle)
        {
            Lib_Room_destructor(m_handle);
        }
    }


    private void _CheckPtr()
    {
        if (IntPtr.Zero == m_handle)
            throw new Exception("Room is null");
    }



    public void SetPosition(int x, int y)
    {
        _CheckPtr();
        Lib_Room_setPosition(m_handle, x, y);
    }

    public void SetSize(int width, int height)
    {
        _CheckPtr();
        Lib_Room_setSize(m_handle, width, height);
    }

    // I don't know how to do this
    public void SetParent(Room parent)
    {
        _CheckPtr();
        Lib_Room_setParent(m_handle, parent.m_handle);
    }

    public void AddNeighbor(Room room)
    {
        _CheckPtr();
        Lib_Room_addNeighbor(m_handle,  room.m_handle);
    }

    public Room GetNeighbor(int index)
    {
        _CheckPtr();
        return new Room(Lib_Room_getNeighbor(m_handle, index));
    }

    public void AddLink(Room room)
    {
        _CheckPtr();
        Lib_Room_addLink(m_handle, room.m_handle);
    }

    public Room GetLink(int index)
    {
        _CheckPtr();
        return new Room(Lib_Room_getLink(m_handle, index));
    }

    public bool Contains(int x, int y)
    {
        _CheckPtr();
        return Lib_Room_isIn(m_handle, x, y);
    }

    // Function import
    [DllImport("DungeonGenerator")] private static extern IntPtr Lib_Room_constructor(int _x, int _y, int _w, int _h);
    [DllImport("DungeonGenerator")] private static extern IntPtr Lib_Room_copyConstructor(IntPtr _other);
    [DllImport("DungeonGenerator")] private static extern void Lib_Room_destructor(IntPtr _this);

    [DllImport("DungeonGenerator")] private static extern void Lib_Room_setId(IntPtr _this, UInt64 _id);
    [DllImport("DungeonGenerator")] private static extern void Lib_Room_setX(IntPtr _this, int _x);
    [DllImport("DungeonGenerator")] private static extern void Lib_Room_setY(IntPtr _this, int _y);
    [DllImport("DungeonGenerator")] private static extern void Lib_Room_setPosition(IntPtr _this, int _x, int _y);
    [DllImport("DungeonGenerator")] private static extern void Lib_Room_setWidth(IntPtr _this, int _w);
    [DllImport("DungeonGenerator")] private static extern void Lib_Room_setHeight(IntPtr _this, int _h);
    [DllImport("DungeonGenerator")] private static extern void Lib_Room_setSize(IntPtr _this, int _w, int _h);
    [DllImport("DungeonGenerator")] private static extern void Lib_Room_setParent(IntPtr _this, IntPtr _parent);
    [DllImport("DungeonGenerator")] private static extern void Lib_Room_setLocked(IntPtr _this, bool _locked);

    [DllImport("DungeonGenerator")] private static extern UInt64 Lib_Room_getId(IntPtr _this);
    [DllImport("DungeonGenerator")] private static extern int Lib_Room_getX(IntPtr _this);
    [DllImport("DungeonGenerator")] private static extern int Lib_Room_getY(IntPtr _this);
    [DllImport("DungeonGenerator")] private static extern int Lib_Room_getWidth(IntPtr _this);
    [DllImport("DungeonGenerator")] private static extern int Lib_Room_getHeight(IntPtr _this);
    [DllImport("DungeonGenerator")] private static extern IntPtr Lib_Room_getParent(IntPtr _this);
    [DllImport("DungeonGenerator")] private static extern bool Lib_Room_isLocked(IntPtr _this);

    [DllImport("DungeonGenerator")] private static extern void Lib_Room_addNeighbor(IntPtr _this, IntPtr _room);
    [DllImport("DungeonGenerator")] private static extern IntPtr Lib_Room_getNeighbor(IntPtr _this, int _index);
    [DllImport("DungeonGenerator")] private static extern UInt32 Lib_Room_getNeighborCount(IntPtr _this);

    [DllImport("DungeonGenerator")] private static extern void Lib_Room_addLink(IntPtr _this, IntPtr _room);
    [DllImport("DungeonGenerator")] private static extern IntPtr Lib_Room_getLink(IntPtr _this, int _index);
    [DllImport("DungeonGenerator")] private static extern UInt32 Lib_Room_getLinkCount(IntPtr _this);

    [DllImport("DungeonGenerator")] private static extern bool Lib_Room_isIn(IntPtr _this, int _x, int _y);
    [DllImport("DungeonGenerator")] private static extern bool Lib_Room_pathExists(IntPtr _from, IntPtr _to);
}
