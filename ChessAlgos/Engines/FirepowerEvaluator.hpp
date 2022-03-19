/* Created by Jeevaka Dassanayake on 3/6/22.
   Copyright (c) 2022 Jeevaka Dassanayake.*/

namespace ChessAlgos {

	class FirepowerEvaluator : public MoveEvaluator {
	public :
		FirepowerEvaluator( Position& p );
		virtual void evaluate( const Move& move ) override;

		void reset();
		unsigned long getMoveCount();

	protected :
		// Typedefs


		// Methods


		// Data
		unsigned long moveCount;
		// Can we add additional measures such as value of the pieces we can capture? Capture differential etc?
	};
}
