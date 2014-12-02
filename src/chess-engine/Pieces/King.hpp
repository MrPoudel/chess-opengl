/*
 * King.hpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

#ifndef KING_H
#define KING_H

#include "../ChessPiece.hpp"

class King : public ChessPiece {

public:
	King(Player);
	string getType();
};

#endif