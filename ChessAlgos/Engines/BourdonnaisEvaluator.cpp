/* Created by Jeevaka Dassanayake on 4/29/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

#include "../../Shared/BaseIncludes.hpp"
#include "../../StdPlus/StdPlus.hpp"
#include "../../Chess/Chess.hpp"

#include "../Valuation/FixedValuations.hpp"

#include "FirepowerEvaluator.hpp"
#include "BourdonnaisEvaluator.hpp"

using namespace ChessAlgos;

BourdonnaisEvaluator::BourdonnaisEvaluator( Position& p ) : FixedDepthEvaluator( p )
	, firepowerEvaluator( p ) {
}


void BourdonnaisEvaluator::evaluateLeaf() {
	// We want to count the firepower of each side. So we do one more recursion.
	unsigned long theirMoves = firepowerEvaluator.getMoveCount();

	position.flipTurn();
	unsigned long ourMoves = firepowerEvaluator.getMoveCount();
	position.flipTurn();

	double value;
	// When the denominator is 0
	if ( ourMoves > theirMoves ) {
		value = double( ourMoves ) / ( 0 == theirMoves ? 0.25 : double( theirMoves ) );
	} else {
		value = -double( theirMoves ) / ( 0 == ourMoves ? 0.25 : double( ourMoves ) );
	}

	levelInfo[ plies ].bestValue = -value;	// The value to opposite side.
											// (We negate this when evaluating our value in FixedDepthEvaluator::evaluate.)
	//cout << theirMoves << ", " << ourMoves << ", " << value << ", " << endl;
}
