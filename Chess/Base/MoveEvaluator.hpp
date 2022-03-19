/* Created by Jeevaka Dassanayake on 4/29/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

namespace Chess {

	class MoveEvaluator {
	public :
		MoveEvaluator( Position& p );
		virtual void evaluate( const Move& move ) = 0;

	protected :
		// Typedefs

		// Data
		Position& position;
	};
}
