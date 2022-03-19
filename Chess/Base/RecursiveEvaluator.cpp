/* Created by Jeevaka Dassanayake on 3/6/22.
   Copyright (c) 2022 Jeevaka Dassanayake.*/

#include "../../Shared/BaseIncludes.hpp"
#include "../../StdPlus/StdPlus.hpp"

#include "ChessConst.hpp"
#include "PieceEnum.hpp"
#include "Square.hpp"
#include "Move.hpp"
#include "Position.hpp"

#include "MoveEvaluator.hpp"
#include "Notation.hpp"

#include "RecursiveEvaluator.hpp"

using namespace Chess;


RecursiveEvaluator::RecursiveEvaluator( Position& p ) : MoveEvaluator( p ) {

}


void RecursiveEvaluator::setMaxPlies( unsigned mp ) {
	maxPlies = mp;
}


void RecursiveEvaluator::bumpPlyCount() {
	plyCount++;
}


unsigned long RecursiveEvaluator::getPlyCount() {
	return plyCount;
}


void RecursiveEvaluator::initializeSearch() {
	plyCount = 0;
}
