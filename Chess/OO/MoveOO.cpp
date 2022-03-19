/* Created by Jeevaka Dassanayake on 4/23/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

#include "../../Shared/BaseIncludes.hpp"
#include "../../StdPlus/StdPlus.hpp"

#include "../Base/PieceEnum.hpp"
#include "../Base/Square.hpp"
#include "../Base/Move.hpp"

#include "SquareOO.hpp"
#include "MoveOO.hpp"


using namespace Chess;

MoveOO::MoveOO() {
}


MoveOO::MoveOO( const Square& s, const Square& e, PieceEnum p, bool ep, PieceEnum c, bool wep, const Square& o
		, const bool (&cp)[2][2] )
		: start( s ), end( e ), promoted( p ), enPassant( ep ), captured( c ), wasEnPassant( wep ), oldEnPassantSquare( o )	{
	for( bool isWhite : { true, false } ) {
		for ( bool isKingSide : { true, false } ) {
			castlingPermission[isWhite][isKingSide] = cp[isWhite][isKingSide];
		}
	}
}


Move& MoveOO::operator=( const Move& other ) {
	start = other.getStart();
	end = other.getEnd();
	promoted = other.promotedPiece();
	enPassant = other.isEnPassant();
	return *this;
}


const Square& MoveOO::getStart() const {
	return start;
}


const Square& MoveOO::getEnd() const {
	return end;
}


PieceEnum MoveOO::promotedPiece() const {
	return promoted;
}


bool MoveOO::isEnPassant() const {
	return enPassant;
}


PieceEnum MoveOO::capturedPiece() const {
	return captured;
}


bool MoveOO::hadEnPassant() const {
	return wasEnPassant;
}


const Square& MoveOO::enPassantSquare() const {
	return oldEnPassantSquare;
}


bool MoveOO::getOldCastlingPermission( bool isWhite, bool isKingSide ) const {
	return castlingPermission[isWhite][isKingSide];
}
