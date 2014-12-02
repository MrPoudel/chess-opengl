/*
 * Knight.cpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

#include "Knight.hpp"

using namespace std;

static vector<Point2D<int> > createPossibleMoves() {
	vector<Point2D<int> > moves;
	moves.push_back(createPoint(1, 2));		// Right
	moves.push_back(createPoint(-1,2));		// Right

	moves.push_back(createPoint(1, -2));	// Left
	moves.push_back(createPoint(-1,-2));	// Left

	moves.push_back(createPoint(2,-1));		// Front
	moves.push_back(createPoint(2, 1));		// Front

	moves.push_back(createPoint(-2,-1));	// Behind
	moves.push_back(createPoint(-2, 1));	// Behind
	return moves;
}
Knight::Knight(Player player) : ChessPiece(player, createPossibleMoves(), false) {}

string Knight::getType() {
	return "Knight";
}