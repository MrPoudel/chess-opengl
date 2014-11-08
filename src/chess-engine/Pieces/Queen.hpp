#ifndef QUEEN_H
#define QUEEN_H

#include "../ChessPiece.hpp"

class Queen : public ChessPiece {

public:
	Queen(Player);
	string getType();
};

#endif