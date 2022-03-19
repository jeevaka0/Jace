/* Created by Jeevaka Dassanayake on 2/27/22.
   Copyright (c) 2022 Jeevaka Dassanayake.*/

namespace Chess {

	class FixedDepthEvaluator : public RecursiveEvaluator {
	public:
		FixedDepthEvaluator( Position& p );
		virtual ~FixedDepthEvaluator();

		virtual void setMaxPlies( unsigned mp ) override;
		virtual Move& findBestMove() override;
		virtual void evaluate( const Move& move ) override;

	protected:
		// Typedefs
		class LevelInfo {			// Purpose of 'canCaptureKing' is ???
		public:
			double bestValue;
			bool canCaptureKing;
			void initialize() { bestValue = -DBL_MAX; canCaptureKing = false; };
			void initialize( double v ) { bestValue = v; canCaptureKing = false; };
		};


		// Methods
		virtual void evaluateLeaf() = 0;
		virtual void evaluateNonLeaf();
		virtual void updateNodeValue( double v, const Move& move );

		// Data
		unsigned plies;
		MoveOO bestMove;
		vector<LevelInfo> levelInfo;

		static constexpr double MOVE = 1.0;
		static constexpr double KING_CAPTURE = DBL_MAX;
		static constexpr double DISCOUNT = 1.0 - DBL_EPSILON;
		static constexpr double MATE = KING_CAPTURE * DISCOUNT;			// If, after any move the opponent can capture king.
	};
}

