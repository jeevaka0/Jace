/* Created by Jeevaka Dassanayake on 4/21/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

namespace ChessAlgos {

	class BourdonnaisEngine : public Engine {
	public :
		BourdonnaisEngine( Protocol& p );

		virtual Position& getPosition() override;
		virtual const Move& getBestMove() override;
		virtual void applyMove( const Square& start, const Square& end, PieceEnum promoted ) override;
		virtual void applyMove( const Move& move ) override;

	protected :
		// Typedefs


		// Methods
		virtual RecursiveEvaluator& getMoveEvaluator() override;


		// Data
		PositionOO position;
		BourdonnaisEvaluator evaluator;
	};
}
