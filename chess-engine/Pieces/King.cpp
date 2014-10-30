#include "King.hpp"

using namespace std;

static vector<Point2D<int> > createPossibleMoves() {
	vector<Point2D<int> > moves;
	moves.push_back(createPoint(1, 1));		// Diagonal Direita
	moves.push_back(createPoint(1,-1));		// Diagonal Esquerda
	moves.push_back(createPoint(1, 0));		// Front
	moves.push_back(createPoint(0, 1));		// Right
	moves.push_back(createPoint(0,-1));		// Left
	moves.push_back(createPoint(-1, 1));	// Diagonal Behind Right
	moves.push_back(createPoint(-1,-1));	// Diagonal Behind Left
	moves.push_back(createPoint(-1, 0));	// Behind
	return moves;
}
King::King(Player player) : ChessPiece(player, createPossibleMoves()) {}

string King::getType() {
	return "King";
}