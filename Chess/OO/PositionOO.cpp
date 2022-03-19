/* Created by Jeevaka Dassanayake on 3/20/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

#include "../../Shared/BaseIncludes.hpp"
#include "../../StdPlus/StdPlus.hpp"

#include "../Base/ChessConst.hpp"
#include "../Base/PieceEnum.hpp"
#include "../Base/PieceOps.hpp"
#include "../Base/Square.hpp"
#include "../Base/Move.hpp"
#include "../Base/Position.hpp"

#include "SquareOO.hpp"
#include "MoveOO.hpp"
#include "../Base/MoveEvaluator.hpp"

#include "PositionOO.hpp"


using namespace Chess;


PositionOO::PositionOO() : Position() {
}


PieceEnum PositionOO::getPiece( unsigned row, unsigned column ) const {
	return squares[row][column];
}


PieceEnum PositionOO::getPiece( const Square& square ) const {
	return getPiece( square.getRow(), square.getColumn() );
}


bool PositionOO::isEmpty( unsigned row, unsigned column ) const {
	return getPiece( row, column ) == PieceEnum::EMPTY;
}


bool PositionOO::isEmpty( const Square& square ) const {
	return getPiece( square ) == PieceEnum::EMPTY;
}


bool PositionOO::getTurn() const {
	return isWhitesTurn;
}

bool PositionOO::getCastlingPermission( bool isWhite, bool isKingSide ) const {
	return castlingPermission[isWhite][isKingSide];
}

bool PositionOO::hasEnpassant() const {
	return enPassantPossible;
}

const Square& PositionOO::getEnPassantSquare() const {
	return enPassantSquare;
}


unsigned PositionOO::getHalfMoveCount() const {
	return halfMoveCount;
}

unsigned PositionOO::getFullMoveCount() const {
	return fullMoveCount;
}


void PositionOO::setPiece( unsigned row, unsigned column, PieceEnum piece ) {
	squares[row][column] = piece;
}


void PositionOO::setTurn( bool isWhite ) {
	isWhitesTurn = isWhite;
}

void PositionOO::flipTurn() {
	isWhitesTurn = !isWhitesTurn;
}


void PositionOO::setCastlingPermission( bool isWhite, bool isKingSide, bool allowed ) {
	castlingPermission[isWhite][isKingSide] = allowed;
}

void PositionOO::setEnPassant( const Square& square, bool yes ) {
	enPassantPossible = yes;
	enPassantSquare = square;
}


void PositionOO::resetEnPassant() {
	enPassantPossible = false;
}

void PositionOO::setHalfMoveCount( unsigned count ) {
	halfMoveCount = count;
}

void PositionOO::setFullMoveCount( unsigned count ) {
	fullMoveCount = count;
}


void PositionOO::bumpCounters() {
	halfMoveCount++;
	if( getTurn() ) {
		fullMoveCount++;
	}
}


void PositionOO::revertCounters() {
	halfMoveCount--;
	if( getTurn() ) {
		fullMoveCount--;
	}
}


Square& PositionOO::getEnPassantSquare() {
	return enPassantSquare;
}


void PositionOO::attemptOneMove( unsigned rStart, unsigned cStart, unsigned rDest, unsigned cDest, PieceEnum captured
		, PieceEnum promoted, bool enPassant, MoveEvaluator& evaluator ) {
	// We have two choices.
	// 1. Evaluate only if king doesn't get attacked.
	// 2. Evaluator can evaluate 'checked' position with max value to the opponent when it is checking next level moves.

	MoveOO move ( SquareOO( rStart, cStart ), SquareOO( rDest, cDest ) , promoted, enPassant, captured, enPassantPossible
			, enPassantSquare, castlingPermission );

	evaluator.evaluate( move );
}
