#ifndef CHESS_H
#define CHESS_H

#include <vector>
#include <ostream>
#include "ChessPiece.hpp"
#include "../utils/Points.hpp"
#include "Pieces/Pawn.hpp"
#include "Pieces/King.hpp"
#include "Pieces/Queen.hpp"
#include "Pieces/Knight.hpp"
#include "Pieces/Tower.hpp"
#include "Pieces/Bishop.hpp"

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