/*
 * Knight.hpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

#ifndef KNIGHT_H
#define KNIGHT_H

#include "../ChessPiece.hpp"

class Knight : public ChessPiece {

public:
	Knight(Player);
	string getType();
};

#endif