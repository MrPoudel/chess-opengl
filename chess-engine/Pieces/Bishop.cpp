#include "Bishop.hpp"

using namespace std;

inline vector<Point2D<int> > createPossibleMoves() {
	vector<Point2D<int> > moves;
	for (int i = 1; i < 8; i++) {
		moves.push_back(createPoint(i, i));		// Diagonal Right
		moves.push_back(createPoint(i,-i));		// Digonal Left
		moves.push_back(createPoint(-i,i));		// Diagonal Behind Right
		moves.push_back(createPoint(-i,-i));		// Diagonal Behind Left
	}
	return moves;
}
Bishop::Bishop(Player player) : ChessPiece(player, createPossibleMoves()) {}

string Bishop::getType() {
	return "Bishop";
}