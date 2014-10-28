#ifndef CHESS_H
#define CHESS_H

#include <vector>
#include <ostream>
#include "ChessPiece.hpp"
#include "../Points.hpp"
#include "Pieces/Pawn.hpp"

using namespace std;

class Chess {
private:
	ChessPiece * table[8][8];
	vector<ChessPiece> beated;
public:
	Chess();
	~Chess();
	friend ostream &operator<<(ostream &, const Chess &);

	bool move(Point2D<int> src, Point2D<int> dst);

};

#endif