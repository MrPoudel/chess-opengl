#include "ChessPiece.h"

ChessPiece::ChessPiece(Player player, std::vector<Point2D<int> > possibleMoves) {
	this->player = player;
	this->possibleMoves = possibleMoves;
};

ChessPiece::~ChessPiece() {

};

vector<Point2D<int> > ChessPiece::getPossibleMoves() {
	return possibleMoves;
}