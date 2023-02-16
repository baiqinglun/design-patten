
// 迷宫组件抽象类
class MapSite{
public:
	virtual void Enter();
}

// 房间组件
class Room : public MapSite{
public:
	Room(int roomNo);
	// 返回一个方向的迷宫组件
	Mapsite* GetSide(Direction) const;
	
	void SetSide(Mapsite*);
	
	virtual void Enter();
	
private:
	Mapsite* _sides[4];
	int _roomNumber;
}

// 门组件
class Door : public MapSite{
public:
	Door(Room = 0,Room = 0);
	Room* OtherSideForm(Room*);
	virtual void Enter();
	
private:
	Room* _room1;
	Room* _room2;
	bool _isOpen;
}

// 墙组件
class Wall : public MapSite{
public:
	Wall();
	virtual void Enter();
}

// 房间集合
class Maze{
public:
	Maze();
	void AddRoom(Room*);
	Room* RoomNo(int) const;
}

// 创建迷宫的类
class MazeGame{
public:
	MazeGame();
	Maze* CreateMaze();
}
// 创建一个迷宫



Maze* MazeGame::CreateMaze(){
	Maze* aMaze = new Maze;
	Room* r1 = new Room(1);
	Room* r2 = new Room(2);
	Door* theDoor = new Door(r1,r2);
	
	aMaze->addRoom(r1);
	aMaze->addRoom(r2);
	
	r1->setSide(North,new Wall);
	r1->setSide(East,theDoor);
	r1->setSide(South,new Wall);
	r1->setSide(West,new Wall);
	
	r2->setSide(North,new Wall);
	r2->setSide(East,new Wall);
	r2->setSide(South,new Wall);
	r2->setSide(West,theDoor);
	
	return aMaze;
}


