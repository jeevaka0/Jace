/* Created by Jeevaka Dassanayake on 4/21/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

#include "../../Shared/BaseIncludes.hpp"
#include "../../StdPlus/StdPlus.hpp"
#include "../../Chess/Chess.hpp"

#include "FirepowerEvaluator.hpp"
#include "BourdonnaisEvaluator.hpp"
#include "BourdonnaisEngine.hpp"


using namespace ChessAlgos;


BourdonnaisEngine::BourdonnaisEngine( Protocol& p ) : Engine( p ), evaluator( position ) {

}


Position& BourdonnaisEngine::getPosition() {
	return position;
}


RecursiveEvaluator& BourdonnaisEngine::getMoveEvaluator() {
	return evaluator;
}


const Move& BourdonnaisEngine::getBestMove() {
	// Evaluate.

	return evaluator.findBestMove();
}


// If we keep track of anything related to the position then we need adjust that here.
void BourdonnaisEngine::applyMove( const Square& start, const Square& end, PieceEnum promoted ) {
	position.applyMove( start, end, promoted );
}


void BourdonnaisEngine::applyMove( const Move& move ) {
	position.applyMove( move );
}
