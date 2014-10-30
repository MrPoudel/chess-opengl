#include "Tower.hpp"

using namespace std;

static vector<Point2D<int> > createPossibleMoves() {
	vector<Point2D<int> > moves;
	for (int i = 1; i < 8; i++) {
		moves.push_back(createPoint(0, i));		// Right
		moves.push_back(createPoint(0,-i));		// Left
		moves.push_back(createPoint(i, 0));		// Front
		moves.push_back(createPoint(-i,0));		// Behind
	}
	return moves;
}
Tower::Tower(Player player) : ChessPiece(player, createPossibleMoves()) {}

string Tower::getType() {
	return "Tower";
}