#pragma once
#ifndef Position
#define Position
struct Position
{
	int row, col;
};
#endif
class Robot {
public:
	enum State { ALIVE, STUCK, DEAD };
	Robot(int row, int col) { this->row = row; this->col = col; id = ++robotCounter; };
	int getID() const { return id };
	char getSymbol() const { if (alive) { return 'R' } else return 'r' }; // get char representation of robot (R if alive, r if dead)
	int getRow() const { return row };
	int getCol() const { return col };
	Position getPosition() const { return Position(row, col) };
	bool isAlive() const { return alive; }
	void setRow(int x) { row = x };
	void setCol(int y) { row = y };
	void setPosition(const Position& pos) { row = pos.row; col = pos.col; };
	void setAsDead() { alive = false };
	//other methods
private:
	static int robotCounter; //used to attribute automatically the id to the robots (starts by 1)
	int id;
	int row, col;
	bool alive;
	// other attributes (?)
};
