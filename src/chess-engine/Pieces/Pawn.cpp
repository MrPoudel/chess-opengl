/*
 * Pawn.cpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

#include "Pawn.hpp"

using namespace std;

static vector<Point2D<int> > createPossibleMoves() {
	vector<Point2D<int> > moves;
	moves.push_back(createPoint(1, 1));		// Diagonal Direita
	moves.push_back(createPoint(1,-1));		// Diagonal Esquerda
	moves.push_back(createPoint(1, 0));		// Frente
	return moves;
}
Pawn::Pawn(Player player) : ChessPiece(player, createPossibleMoves(), false) {
	gotFirstMove = true;
}

string Pawn::getType() {
	return "Pawn";
}