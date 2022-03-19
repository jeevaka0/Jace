/* Created by Jeevaka Dassanayake on 4/2/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

namespace Chess {

	class PieceOps {
	public :
		static PieceEnum setColor( PieceEnum piece, bool isWhite );
		static bool splitColor( PieceEnum& piece );
		static PieceEnum stripColor( PieceEnum piece );

	protected :
		// Typedefs


		// Methods


		// Data
	};
}
