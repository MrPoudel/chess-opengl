#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <vector>
#include <string>
#include "../utils/Points.hpp"

using namespace std;

enum Player {ONE, TWO};

class ChessPiece {
	private:
		vector<Point2D<int> > possibleMoves;
	public:
		Player player;
		ChessPiece(Player, vector<Point2D<int> >);
		~ChessPiece();

		vector<Point2D<int> > getPossibleMoves();
		virtual string getType();
};

#endif