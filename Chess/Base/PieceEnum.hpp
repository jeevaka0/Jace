/* Created by Jeevaka Dassanayake on 3/31/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

namespace Chess {

	enum class PieceEnum : unsigned {
		EMPTY = 0,
		BPAWN = 1, BKNIGHT = 2, BBISHOP = 3, BROOK = 4, BQUEEN = 5, BKING = 6,			// Just for debugging.
		PAWN = 1, KNIGHT = 2, BISHOP = 3, ROOK = 4, QUEEN = 5, KING = 6,
		NOCOLOR = 7, WHITE = 8,
		WPAWN = 9, WKNIGHT = 10, WBISHOP = 11, WROOK = 12, WQUEEN = 13, WKING = 14			// Just for debugging.
	};
}

template<> struct EnableBitMaskOperators<Chess::PieceEnum>
{
	static const bool enable = true;
};


template<> struct EnableArithmeticOperators<Chess::PieceEnum>
{
	static const bool enable = true;
};
