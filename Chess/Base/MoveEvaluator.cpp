/* Created by Jeevaka Dassanayake on 4/29/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

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

MoveEvaluator::MoveEvaluator( Position& p ) : position( p ){

}


