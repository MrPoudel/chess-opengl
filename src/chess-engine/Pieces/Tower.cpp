/*
 * Tower.cpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

#include "Tower.hpp"

using namespace std;

static vector<Point2D<int> > createPossibleMoves() {
	vector<Point2D<int> > moves;
	//for (int i = 1; i < 8; i++) {
		moves.push_back(createPoint(0, 1));		// Right
		moves.push_back(createPoint(0,-1));		// Left
		moves.push_back(createPoint(1, 0));		// Front
		moves.push_back(createPoint(-1,0));		// Behind
	//}
	return moves;
}
Tower::Tower(Player player) : ChessPiece(player, createPossibleMoves(), true) {}

string Tower::getType() {
	return "Tower";
}