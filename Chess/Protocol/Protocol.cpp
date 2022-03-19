/* Created by Jeevaka Dassanayake on 4/21/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

#include "../../Shared/BaseIncludes.hpp"
#include "../../StdPlus/StdPlus.hpp"

#include "../Base/ChessConst.hpp"
#include "../Base/PieceEnum.hpp"
#include "../Base/Square.hpp"
#include "../Base/Move.hpp"
#include "../Base/Position.hpp"

#include "../Base/MoveEvaluator.hpp"
#include "../Base/RecursiveEvaluator.hpp"
#include "../Base/Engine.hpp"

#include "Protocol.hpp"


using namespace Chess;


Protocol::Protocol() : stopWatch( TimeUtils::GetSteadyNanos ){

}

void Protocol::setEngine( Engine *pE ) {
	pEngine = pE;
}
