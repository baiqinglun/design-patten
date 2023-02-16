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

// 修改代码
// 创建迷宫的类
class MazeGame{
public:
	MazeGame();
	Maze* CreateMaze(MazeFactory&);
}
// 创建一个迷宫
Maze* MazeGame::CreateMaze(MazeFactory& factory){
	Maze* aMaze = factory.MakeMaze();
	Room* r1 = factory.MakeRoom(1);
	Room* r2 = factory.MakeRoom(2);
	Door* aDoor = factory.MakeDoor(r1,r2);
	
	aMaze->addRoom(r1);
	aMaze->addRoom(r2);
	
	r1->setSide(North,factory.MakeWall());
	r1->setSide(East,aDoor);
	r1->setSide(South,factory.MakeWall());
	r1->setSide(West,factory.MakeWall());
	
	r2->setSide(North,factory.MakeWall());
	r2->setSide(East,factory.MakeWall());
	r2->setSide(South,factory.MakeWall());
	r2->setSide(West,aDoor);
	
	return aMaze;
}

// 创建迷宫组件
class MazeFactory{
public:
	MazeFactory();
	
	virtual Maze* MakeMaze() const {
		return new Maze;
	}
	virtual Wall* MakeWall() const{
		return new Wall;
	}
	virtual Room* MakeRoom(int n) const {
		return new Room(n);
	}
	virtual Door* MakeDoor(Room* r1,Room* r2) const {
		return new Door(r1,r2);
	}
}

// 创建具有魔法的迷宫
class EnchantedMazeFactory : public MazeFactory {
public:
	EnchantedMazeFactory();
	
	virtual Room* MakeRoom(int n) const {
		return new EnchantedRoom(n,CastSpell);
	}
	virtual Door* MakeDoor(Room* r1,Room* r2) const {
		return new DoorNeedingSpell(r1,r2);
	}
	virtual Wall* MakeWall() const {
		return new WallNeedingSpell();
	}
protected:
	Spell* CastSpell() const;
}

// 创建具有爆炸的迷宫
class BombedMazeFactory : public MazeFactory{
	BombedMazeFactory();
	virtual Wall* MakeWall() const;
	virtual Room* MakeRoom(int n) const;
	virtual Door* MakeDoor(Room* r1,Room* r2) const;
}
// 房间内是否有炸弹，炸弹是否爆炸
class RoomWithABomb : public Room {
	RoomWithABomb(int);
}
// 墙是否被损坏
class BombedWall :public Wall {
	BombedWall();
}
// 门是否被损坏
class BombedDoor :public Door {
	BombedDoor(Room = 0,Room = 0);
}
// 创建墙
Wall* BombedMazeFactory::MakeWall() const {
	return new BombedWall();
}
// 创建房间
Room* BombedMazeFactory::MakeRoom(int n) const {
	return new RoomWithABomb(n);
}
// 创建门
Room* BombedMazeFactory::MakeDoor(Room* r1,Room* r2) const {
	return new BombedDoor(Room* r1,Room* r2);
}

// 创建一个含有炸弹的迷宫
MazeGame game;
BombedMazeFactory factory;
game.CreateMaze(factory);





















