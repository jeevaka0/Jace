/* Created by Jeevaka Dassanayake on 5/12/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

namespace ChessAlgos {

	class FixedValuations {
	public :
		constexpr static double Win = DBL_MAX;
		//	EMPTY = 0, PAWN = 1, KNIGHT = 2, BISHOP = 3, ROOK = 4, QUEEN = 5, KING = 6,
		constexpr static double Pieces[ ChessConst::NumPieces + 1 ]
				= { 0.0, 1.0, 3.0, 3.0, 5.0, 9.0, DBL_MAX };				// Change king's value when/if needed.

	protected :
		// Typedefs


		// Methods


		// Data
	};
}
