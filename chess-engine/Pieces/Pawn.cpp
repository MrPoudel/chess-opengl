#include "Pawn.hpp"

using namespace std;

vector<Point2D<int> > createPossibleMoves() {
	vector<Point2D<int> > moves;
	moves.push_back(createPoint(1, 1));		// Diagonal Direita
	moves.push_back(createPoint(1,-1));		// Diagonal Esquerda
	moves.push_back(createPoint(1, 0));		// Frente
	return moves;
}
Pawn::Pawn(Player player) : ChessPiece(player, createPossibleMoves()) {}

string Pawn::getType() {
	return "Pawn";
}