#include "Chess.h"
#include <cstddef>

Chess::Chess() {
	/* Player one setup */
	table[0][0] = new Pawn(ONE);
	table[0][1] = new Pawn(ONE);
	table[0][2] = new Pawn(ONE);
	table[0][3] = new Pawn(ONE);
	
	table[0][4] = new Pawn(ONE);
	table[0][5] = new Pawn(ONE);
	table[0][6] = new Pawn(ONE);
	table[0][7] = new Pawn(ONE);

	for (int i = 0; i < 8; i++)
		table[1][i] = new Pawn(ONE);

	/* Player two setup */
	table[7][0] = new Pawn(TWO);
	table[7][1] = new Pawn(TWO);
	table[7][2] = new Pawn(TWO);
	table[7][3] = new Pawn(TWO);

	table[7][4] = new Pawn(TWO);
	table[7][5] = new Pawn(TWO);
	table[7][6] = new Pawn(TWO);
	table[7][7] = new Pawn(TWO);

	for (int i = 0; i < 8; i++)
		table[6][i] = new Pawn(TWO );

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
	if (src.x < 0 || src.x >= 8 || src.y < 0 || src.y >= 8 || dst.x < 0 || dst.x >= 8 || dst.y < 0 || dst.y >= 8)
		return false;

	Point2D<int> tmp;
	tmp.x = src.x - dst.x;
	tmp.y = src.y - dst.y;
	vector<Point2D<int> > points = table[src.x][src.y]->getPossibleMoves();
	bool found = false;
	for(vector<Point2D<int> >::iterator it = points.begin(); it != points.end(); ++it) {
		if (it->x == tmp.x && it->y == tmp.y)
			found = true;		
	}
	if (!found || table[dst.x][dst.y]->player == table[src.x][src.y]->player)	
		return false;

	if (table[dst.x][dst.y] == NULL) {
		table[dst.x][dst.y] = table[src.x][src.y];
		table[src.x][src.y] = NULL;
	} else {
		beated.push_back(*table[dst.x][dst.y]);
		table[dst.x][dst.y] = table[src.x][src.y];
		table[src.x][src.y] = NULL;
	}

	return true;
}