#pragma once
class Player {
public:
	Player(int row, int col, char symbol) { this->row = row; this->col = col; this->symbol = symbol; alive = true; };
	int getRow() const { return row };
	int getCol() const { return col };
	char getSymbol() const { return symbol };
	bool isAlive() const { return alive };
	void setAsDead() { alive = false };
	bool move(Movement delta); //fazer separado pq tem q olhar se é valido 
private:
	int row, col;
	bool alive;
	char symbol;
};

