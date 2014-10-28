#include "Pawn.h"

using namespace std;

vector<Point2D<int> > createPossibleMoves() {
	vector<Point2D<int> > moves;
	moves.push_back(createPoint(-1,1));
	moves.push_back(createPoint(-1,1));
	return moves;
}
Pawn::Pawn(Player player) : ChessPiece(player, createPossibleMoves()) {}