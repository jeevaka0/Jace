/* Created by Jeevaka Dassanayake on 4/2/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

#include "../../Shared/BaseIncludes.hpp"
#include "../../StdPlus/StdPlus.hpp"

#include "PieceEnum.hpp"
#include "PieceOps.hpp"


using namespace Chess;


PieceEnum PieceOps::setColor( PieceEnum piece, bool isWhite ) {
	return ( isWhite ? PieceEnum::WHITE : PieceEnum::EMPTY ) | piece;
}


bool PieceOps::splitColor( PieceEnum& piece ) {
	bool white = (bool)( PieceEnum::WHITE & piece );
	piece = stripColor( piece );
	return white;
}


PieceEnum PieceOps::stripColor( PieceEnum piece ) {
	return PieceEnum::NOCOLOR & piece;
}
