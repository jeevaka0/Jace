/* Created by Jeevaka Dassanayake on 4/21/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

namespace Chess {

	class Protocol;

	class Engine {
	public :
		Engine( Protocol& p );

		virtual bool canSetup();
		virtual void reset();		// Reset any internal state.
		virtual Position& getPosition() = 0;
		virtual void initialize();				// With current starting position.
		virtual void setMaxDepth( unsigned mp );
		virtual void applyMove( const Square& start, const Square& end, PieceEnum promoted ) = 0;		// Opponents move.
		virtual void applyMove( const Move& move ) = 0;		// Opponents move.

		virtual const Move& getBestMove() = 0;
		virtual unsigned long getPlyCount();

	protected :
		// Typedefs


		// Methods
		virtual RecursiveEvaluator& getMoveEvaluator() = 0;

		// Data
		Protocol& protocol;
		bool isSetup;
		bool isRunning;
	};
}
