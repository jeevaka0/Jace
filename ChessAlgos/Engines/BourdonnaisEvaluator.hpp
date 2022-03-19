/* Created by Jeevaka Dassanayake on 4/29/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

namespace ChessAlgos {

	class BourdonnaisEvaluator : public FixedDepthEvaluator {
	public :
		BourdonnaisEvaluator( Position& p );

	protected :
		virtual void evaluateLeaf() override;

		FirepowerEvaluator firepowerEvaluator;
	};
}
