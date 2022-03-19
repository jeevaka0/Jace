/* Created by Jeevaka Dassanayake on 3/6/22.
   Copyright (c) 2022 Jeevaka Dassanayake.*/

#include "../../Shared/BaseIncludes.hpp"
#include "../../StdPlus/StdPlus.hpp"
#include "../../Chess/Chess.hpp"

#include "FirepowerEvaluator.hpp"

using namespace ChessAlgos;

FirepowerEvaluator::FirepowerEvaluator( Position& p ) : MoveEvaluator( p ) {
}

void FirepowerEvaluator::reset() {
	moveCount = 0;
}


void FirepowerEvaluator::evaluate( const Move& move ) {
	moveCount++;
}


unsigned long FirepowerEvaluator::getMoveCount() {
	reset();
	position.doAllMoves( *this );
	return moveCount;
}
