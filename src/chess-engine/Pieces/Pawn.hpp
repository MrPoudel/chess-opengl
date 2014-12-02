/*
 * Pawn.hpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

#ifndef PAWN_H
#define PAWN_H

#include "../ChessPiece.hpp"

class Pawn : public ChessPiece {
public:
	bool gotFirstMove;
	Pawn(Player);
	string getType();
};

#endif