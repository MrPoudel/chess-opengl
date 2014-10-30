#include "Queen.hpp"

using namespace std;

static vector<Point2D<int> > createPossibleMoves() {
	vector<Point2D<int> > moves;
	for (int i = 1; i < 8; i++) {
		moves.push_back(createPoint(i, i));		// Diagonal Right
		moves.push_back(createPoint(i,-i));		// Digonal Left
		moves.push_back(createPoint(-i,i));		// Diagonal Behind Right
		moves.push_back(createPoint(-i,-i));	// Diagonal Behind Left
		moves.push_back(createPoint(0, i));		// Right
		moves.push_back(createPoint(0,-i));		// Left
		moves.push_back(createPoint(i, 0));		// Front
		moves.push_back(createPoint(-i,0));		// Behind
	}
	return moves;
}
Queen::Queen(Player player) : ChessPiece(player, createPossibleMoves()) {}

string Queen::getType() {
	return "Queen";
}