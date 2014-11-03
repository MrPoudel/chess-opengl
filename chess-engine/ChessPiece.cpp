#include "ChessPiece.hpp"

ChessPiece::ChessPiece(Player player, std::vector<Point2D<int> > possibleMoves, bool multipleMoves) {
	this->player = player;
	this->possibleMoves = possibleMoves;
	this->multipleMoves = multipleMoves;
};

ChessPiece::~ChessPiece() {

};

vector<Point2D<int> > ChessPiece::getPossibleMoves() {
	return possibleMoves;
}

string ChessPiece::getType() {
	return "None";
}