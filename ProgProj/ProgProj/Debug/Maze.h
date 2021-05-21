#pragma once
class Maze {
public:
	Maze(int numRows, int numCols) { this->numRows = numRows; this->numCols = numCols };
	bool addPost(const Post& post, const Position& position); //falta fazer
	int getnumRows() const { return numRows };
	int getnumCols() const { return numCols };
	// other methods
private:
	int numRows, numCols;
	// data structure that represents the posts
};
