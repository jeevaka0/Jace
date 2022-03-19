/* Created by Jeevaka Dassanayake on 3/28/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

#include "Base/ChessConst.hpp"
#include "Base/PieceEnum.hpp"
#include "Base/PieceOps.hpp"
#include "Base/Square.hpp"
#include "Base/Move.hpp"
#include "Base/Position.hpp"
#include "Base/Notation.hpp"
#include "Base/MoveEvaluator.hpp"
#include "Base/RecursiveEvaluator.hpp"
#include "Base/Engine.hpp"

#include "Protocol/Protocol.hpp"
#include "Protocol/Uci.hpp"

#include "OO/SquareOO.hpp"
#include "OO/MoveOO.hpp"
#include "OO/PositionOO.hpp"


#include "Algo/FixedDepthEvaluator.hpp"

using namespace Chess;
