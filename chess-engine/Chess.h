#ifndef CHESS_H
#define CHESS_H

#include <vector>
#include "ChessPiece.h"
#include "../Points.h"
#include "Pawn.h"

using namespace std;

class Chess {
private:
	ChessPiece * table[8][8];
	vector<ChessPiece> beated;
public:
	Chess();
	~Chess();
	bool move(Point2D<int> src, Point2D<int> dst);
};

#endif