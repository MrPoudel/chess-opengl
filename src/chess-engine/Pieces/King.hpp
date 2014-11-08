#ifndef KING_H
#define KING_H

#include "../ChessPiece.hpp"

class King : public ChessPiece {

public:
	King(Player);
	string getType();
};

#endif