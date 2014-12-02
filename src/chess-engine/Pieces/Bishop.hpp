/*
 * Bishop.hpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

#ifndef BISHOP_H
#define BISHOP_H

#include "../ChessPiece.hpp"

class Bishop : public ChessPiece {

public:
	Bishop(Player);
	string getType();
};

#endif