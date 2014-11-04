#include "Chess.hpp"
#include <cstddef>
#include <typeinfo>
#include <iostream>

using namespace std;

static bool isInsideChess(int x, int y) {
	return !(x < 0 || x >= 8 || y < 0 || y >= 8);
}

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

	cPlayer = ONE;
}

Chess::~Chess() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			delete table[i][j];
		}
	}
}

Player Chess::getCurrentPlayer() {
	return this->cPlayer;
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

bool Chess::move(ChessPiece* srcPiece, Point2D<int> dst) {
	Point2D<int> src = getPosition(srcPiece);
	if (!isInsideChess(src.x, src.y))
		return false;
	vector<Point2D<int> > vec = getPossiblePositions(srcPiece);
	bool found = false;
	for (vector<Point2D<int> >::iterator it = vec.begin(); it != vec.end(); ++it)
		if (it->x == dst.x && it->y == dst.y)
			found = true;
	if (!found)
		return false;

	if (table[dst.x][dst.y] == NULL)
	{	
		table[dst.x][dst.y] = table[src.x][src.y];
		table[src.x][src.y] = NULL;
	} else {
		beated.push_back(*table[dst.x][dst.y]);
		table[dst.x][dst.y] = table[src.x][src.y];
		table[src.x][src.y] = NULL;
	}


	if (cPlayer == ONE)
		cPlayer = TWO;
	else
		cPlayer = ONE;
	return true;
}

vector<Point2D<int> > Chess::getPossiblePositions(ChessPiece * src) {
	vector<Point2D<int> > vec;

	Point2D<int> pos = this->getPosition(src);
	if (pos.x == -1 && pos.y == -1)
		return vec;
	Point2D<int> tmp;
	vector<Point2D<int> > points = src->getPossibleMoves();
	for(vector<Point2D<int> >::iterator it = points.begin(); it != points.end(); ++it) {
		if (!src->multipleMoves) {
			int coef = 1;
			if (src->getType() == "Pawn" && src->player == TWO)
				coef = -1;
			tmp.x = pos.x + it->x * coef;
			tmp.y = pos.y + it->y * coef;
			if (!isInsideChess(tmp.x, tmp.y))
				continue;
			if (table[tmp.x][tmp.y] == NULL) {
				if (src->getType() != "Pawn" || it->y == 0)	
					vec.push_back(tmp);
			} else {
				if ((src->getType() != "Pawn" || it->y != 0) && table[tmp.x][tmp.y]->player != src->player)
					vec.push_back(tmp);
			}
		} else {
			for (int i = 1; i < 8; i++) {
				tmp.x = pos.x + i * it->x;
				tmp.y = pos.y + i * it->y;
				if (!isInsideChess(tmp.x, tmp.y))
					break;

				if (table[tmp.x][tmp.y] != NULL && table[tmp.x][tmp.y]->player == src->player)
					break;
				vec.push_back(tmp);
				if (table[tmp.x][tmp.y] != NULL && table[tmp.x][tmp.y]->player != src->player)
					break;
			}
		}
	}
	return vec;
}

ostream& operator<<(ostream& output, const Chess& obj) {
	for (int i = 7; i >= 0; i--) {
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