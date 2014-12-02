/*
 * Tower.hpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

#ifndef TOWER_H
#define TOWER_H

#include "../ChessPiece.hpp"

class Tower : public ChessPiece {

public:
	Tower(Player);
	string getType();
};

#endif