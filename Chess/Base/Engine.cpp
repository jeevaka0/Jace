/* Created by Jeevaka Dassanayake on 4/21/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

#include "../../Shared/BaseIncludes.hpp"
#include "../../StdPlus/StdPlus.hpp"

#include "ChessConst.hpp"
#include "PieceEnum.hpp"
#include "Square.hpp"
#include "Move.hpp"
#include "Position.hpp"
#include "MoveEvaluator.hpp"
#include "RecursiveEvaluator.hpp"
#include "Engine.hpp"

#include "../Protocol/Protocol.hpp"


using namespace Chess;


Engine::Engine( Protocol& p ) : protocol( p ){

}


bool Engine::canSetup() {
	return !isSetup;
}


void Engine::reset() {
	isSetup = false;
}


void Engine::initialize() {
	isSetup = true;
}


void Engine::setMaxDepth( unsigned mp ) {
	getMoveEvaluator().setMaxPlies( mp );
}


unsigned long Engine::getPlyCount() {
	return getMoveEvaluator().getPlyCount();
}
