/*
 * Bishop.cpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

#include "Bishop.hpp"

using namespace std;

static vector<Point2D<int> > createPossibleMoves() {
	vector<Point2D<int> > moves;
	//for (int i = 1; i < 8; i++) {
	moves.push_back(createPoint(1, 1));		// Diagonal Right
	moves.push_back(createPoint(1,-1));		// Digonal Left
	moves.push_back(createPoint(-1,1));		// Diagonal Behind Right
	moves.push_back(createPoint(-1,-1));	// Diagonal Behind Left
	//}
	return moves;
}
Bishop::Bishop(Player player) : ChessPiece(player, createPossibleMoves(), true) {}

string Bishop::getType() {
	return "Bishop";
}