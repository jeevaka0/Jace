/* Created by Jeevaka Dassanayake on 2/27/22.
   Copyright (c) 2022 Jeevaka Dassanayake.*/

#include "../../Shared/BaseIncludes.hpp"
#include "../../StdPlus/StdPlus.hpp"

#include "../Base/ChessConst.hpp"
#include "../Base/PieceEnum.hpp"
#include "../Base/Square.hpp"
#include "../Base/Move.hpp"
#include "../Base/Position.hpp"

#include "../Base/MoveEvaluator.hpp"
#include "../Base/Notation.hpp"

#include "../OO/SquareOO.hpp"
#include "../OO/MoveOO.hpp"

#include "../Base/RecursiveEvaluator.hpp"
#include "FixedDepthEvaluator.hpp"

using namespace Chess;


FixedDepthEvaluator::FixedDepthEvaluator( Chess::Position& p ) : RecursiveEvaluator( p ) {
}


FixedDepthEvaluator::~FixedDepthEvaluator() {
}


void FixedDepthEvaluator::setMaxPlies( unsigned mp ) {
	RecursiveEvaluator::setMaxPlies( mp );
	levelInfo.resize( maxPlies );
}


Move& FixedDepthEvaluator::findBestMove() {
	initializeSearch();
	plies = 0;
	levelInfo[plies].initialize();
	position.doAllMoves( *this );
	return bestMove;
}


/* In the recursive tree
 * 1. We need to assign a value (from one side's POV). We choose the POV of the one who chooses the move to get there.
 * 2. Non-leaf nodes simply choose the value of the best child node it can choose from.
 * 3. Leaf nodes do a quick evaluation without doing any additional moves.
 * 4. We call the root node (current position) level 0. 'maxPlies' does not include this node as it means the depth.
*/

/* In the approach we have chosen,
 * At non-leaf nodes, 'evaluate' first sets its value to minimum possible and call 'position.doAllMoves' to visit children.
 * '2' is done by the children themselves during moves to avoid a second iteration over children.
 * Once 'position.doAllMoves' returns the parent has its value and do its part of '2' for its parent.
*/


// levelInfo[0] is the root node / position. We increment 'plies' only when we make a move / change position.
void FixedDepthEvaluator::evaluate( const Move& move ) {
	//Notation::print( position, cout );
	//cout << '\t' << plies << ')'; Notation::printMove( move, cout ); cout << endl;
	bumpPlyCount();
	position.applyMove( move );
	plies++;

	// Now come up with a value for the current node / position.
	if ( move.capturedPiece() == PieceEnum::KING ) {
		// This means we didn't have a way to avoid the king getting captured in our previous move.
		// The side that just made the 'move' has already won in the previous position.
		// But it is a stalemate if we were not under check. (See below.)
		levelInfo[ plies ].bestValue = -KING_CAPTURE;
	} else if ( plies == maxPlies ) {
		// Leaf: Come up with a value for the position in constant time.
		// E.g. Any capture value, capture value differential, pawn advancement etc.
		//Notation::printMove( move, cout ) << ", ";
		evaluateLeaf();
	} else {
		evaluateNonLeaf();
	}

	position.revertMove( move );
	plies--;
	// By now we have our best value. Update parent.
	updateNodeValue( -levelInfo[plies + 1].bestValue * DISCOUNT, move );

#ifndef NDEBUG
	//if( plies < 2 ) {
//	if( 0 == plies ) {
	//if( true ) {
//		cout << plies << ')'; Notation::printMove( move, cout ); cout << '\t' << levelInfo[plies].bestValue
//				<< "\t Total moves evaluated: " << plyCount << endl;
//	}
#endif
}


void FixedDepthEvaluator::evaluateNonLeaf() {
	levelInfo[ plies ].initialize( -DBL_MAX );
	position.doAllMoves( *this );

	// Check Stalemate: If king gets captured after every move, but king is not under attack.
	if ( -MATE == levelInfo[ plies ].bestValue && !position.isCheck() ) {			// Stalemate.
		levelInfo[ plies ].bestValue = 0;
	}
}


void FixedDepthEvaluator::updateNodeValue( double v, const Move& move ) {
	if ( levelInfo[ plies ].bestValue < v ) {
		levelInfo[ plies ].bestValue = v;
		if( 0 == plies ) {
			bestMove = move;
		}
	}
}
