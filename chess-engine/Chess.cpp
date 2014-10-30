#include "Chess.hpp"
#include <cstddef>
#include <typeinfo>
#include <iostream>

Chess::Chess() {
	/* Player one setup */
	table[0][0] = new Tower(ONE);
	table[0][1] = new Knight(ONE);
	table[0][2] = new Bishop(ONE);
	table[0][3] = new Queen(ONE);
	
	table[0][4] = new King(ONE);
	table[0][5] = new Bishop(ONE);
	table[0][6] = new Knight(ONE);
	table[0][7] = new Tower(ONE);

	for (int i = 0; i < 8; i++)
		table[1][i] = new Pawn(ONE);

	/* Player two setup */
	table[7][0] = new Tower(TWO);
	table[7][1] = new Knight(TWO);
	table[7][2] = new Bishop(TWO);
	table[7][3] = new Queen(TWO);

	table[7][4] = new King(TWO);
	table[7][5] = new Bishop(TWO);
	table[7][6] = new Knight(TWO);
	table[7][7] = new Tower(TWO);

	for (int i = 0; i < 8; i++)
		table[6][i] = new Pawn(TWO);

	for (int i = 2; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
			table[i][j] = NULL;
		}
	}
}

Chess::~Chess() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			delete table[i][j];
		}
	}
}

bool Chess::move(Point2D<int> src, Point2D<int> dst) {
	/* Check valid move */
	if (src.x < 0 || src.x >= 8 || src.y < 0 || src.y >= 8 || 
		dst.x < 0 || dst.x >= 8 || dst.y < 0 || dst.y >= 8 ||
		table[src.x][src.y] == NULL)
		return false;
	Point2D<int> res;
	res.x = dst.x - src.x;
	res.y = dst.y - src.y;
	if (table[src.x][src.y]->getType() == "Pawn" && table[src.x][src.y]->player == TWO)
		res.x *= -1;

	vector<Point2D<int> > points = table[src.x][src.y]->getPossibleMoves();
	bool found = false;

	for(vector<Point2D<int> >::iterator it = points.begin(); it != points.end(); ++it) {
		if (it->x == res.x && it->y == res.y)
			found = true;		
	}
	if (!found)	
		return false;

	if (table[dst.x][dst.y] == NULL) {
		if (table[src.x][src.y]->getType() == "Pawn" && res.y != 0)
			return false;

		table[dst.x][dst.y] = table[src.x][src.y];
		table[src.x][src.y] = NULL;
	} else {
		if (table[src.x][src.y]->getType() == "Pawn" && res.y == 0)
			return false;
		beated.push_back(*table[dst.x][dst.y]);
		table[dst.x][dst.y] = table[src.x][src.y];
		table[src.x][src.y] = NULL;
	}

	return true;
}

vector<ChessPiece *> Chess::getListPieces() {
	vector<ChessPiece *> vect;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (table[i][j] != NULL)
				vect.push_back(table[i][j]);
		}
	}
	return vect;
}

Point2D<int> Chess::getPosition(ChessPiece * ptr) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (table[i][j] == ptr) {
				Point2D<int> point = { i, j };
				return point;
			}
		}
	}
	Point2D<int> point = { -1, -1 };
	return point;
}

bool Chess::move(ChessPiece* src, Point2D<int> dst) {
	return this->move(this->getPosition(src), dst);
}

ostream& operator<<(ostream& output, const Chess& obj) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (obj.table[i][j] == NULL)
				output << "_" << i << j << " ";
			else if (obj.table[i][j]->getType() == "Pawn") 
				output << "P" << i << j << " ";
			else if (obj.table[i][j]->getType() == "Knight") 
				output << "H" << i << j << " ";
			else if (obj.table[i][j]->getType() == "King") 
				output << "K" << i << j << " ";
			else if (obj.table[i][j]->getType() == "Queen") 
				output << "Q" << i << j << " ";
			else if (obj.table[i][j]->getType() == "Tower") 
				output << "T" << i << j << " ";
			else if (obj.table[i][j]->getType() == "Bishop") 
				output << "B" << i << j << " ";

		}
		output << endl;
	}
	return output;
}