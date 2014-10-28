#ifndef PAWN_H
#define PAWN_H

#include "../ChessPiece.hpp"

class Pawn : public ChessPiece {

public:
	Pawn(Player);
	string getType();
};

#endif