#ifndef TOWER_H
#define TOWER_H

#include "../ChessPiece.hpp"

class Tower : public ChessPiece {

public:
	Tower(Player);
	string getType();
};

#endif