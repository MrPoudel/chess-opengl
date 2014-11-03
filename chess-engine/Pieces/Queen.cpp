#include "Queen.hpp"

using namespace std;

static vector<Point2D<int> > createPossibleMoves() {
	vector<Point2D<int> > moves;
	//for (int i = 1; i < 8; i++) {
	moves.push_back(createPoint(1, 1));		// Diagonal Right
	moves.push_back(createPoint(1,-1));		// Digonal Left
	moves.push_back(createPoint(-1,1));		// Diagonal Behind Right
	moves.push_back(createPoint(-1,-1));	// Diagonal Behind Left
	moves.push_back(createPoint(0, 1));		// Right
	moves.push_back(createPoint(0,-1));		// Left
	moves.push_back(createPoint(1, 0));		// Front
	moves.push_back(createPoint(-1,0));		// Behind
	//}
	return moves;
}
Queen::Queen(Player player) : ChessPiece(player, createPossibleMoves(), true) {}

string Queen::getType() {
	return "Queen";
}