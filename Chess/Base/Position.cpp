/* Created by Jeevaka Dassanayake on 3/20/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

#include "../../Shared/BaseIncludes.hpp"
#include "../../StdPlus/StdPlus.hpp"

#include "ChessConst.hpp"
#include "PieceEnum.hpp"
#include "PieceOps.hpp"
#include "Square.hpp"
#include "Move.hpp"
#include "Position.hpp"
#include "Notation.hpp"


using namespace Chess;

constexpr Position::DoPieceMoves Position::movers[ChessConst::NumPieces];


Position::Position() {
}


istream& Position::read( istream& is ) {
	return Notation::setPosition( *this, is );
}


ostream& Position::print( ostream& os ) const {
	return Notation::print( *this, os );
}

// The move is guaranteed to be a valid move.
void Position::applyMove( const Move& move ) {
	applyMove( move.getStart().getRow(), move.getStart().getColumn(), move.getEnd().getRow(), move.getEnd().getColumn()
			, move.promotedPiece(), move.isEnPassant() );
}


// The move is guaranteed to be a valid move.
void Position::applyMove( const Square& start, const Square& end, PieceEnum promoted ) {
	bool enPassant = getPieceType( start ) == PieceEnum::PAWN && start.getColumn() != end.getColumn() && isEmpty( end );
	applyMove( start.getRow(), start.getColumn(), end.getRow(), end.getColumn(), promoted, enPassant );
}


void Position::resetCastlingPermissions() {
	for ( int i = 0; i < 2; ++i ) {
		for ( int j = 0; j < 2; ++j ) {
			setCastlingPermission( (bool)i, (bool)j, false );
		}
	}
}


// The move is guaranteed to be a valid move.
void Position::applyMove( unsigned rStart, unsigned cStart, unsigned rDest, unsigned cDest, PieceEnum promoted
		, bool enPassant ) {
	PieceEnum moved = getPiece( rStart, cStart );

	// Regular move or pawn promotion.
	setPiece( rDest, cDest, PieceEnum::EMPTY == promoted ? moved : promoted );
	setPiece( rStart, cStart, PieceEnum::EMPTY );
	// If we take a rook at starting position then his castling rights on that side has to be revoked.
	bool isKingSide;
	if( lastRow() == rDest && ( ( isKingSide = 0 == cDest ) || ChessConst::ColumnCount - 1 == cDest ) ) {
		setCastlingPermission( !getTurn(), isKingSide, false );
	}

	// Castling.
	if ( PieceEnum::KING == moved ) {
		isKingSide = 2 == cDest - cStart;
		if( isKingSide || 3 == cStart - cDest ) {			// This is castling.
			unsigned cRook = isKingSide ? ChessConst::ColumnCount - 1 : 0;
			setPiece( rDest, cDest + (unsigned)( isKingSide ? -1 : 1 ), getPiece( rDest, cRook ) );
			setPiece( rDest, cRook, PieceEnum::EMPTY );
		}
		// Any king move means no more castling.
		setCastlingPermission( getTurn(), true, false );
		setCastlingPermission( getTurn(), false, false );
	}

	// Update castling permissions in case of a rook move.
	if ( PieceEnum::ROOK == moved && firstRow() == rStart ) {
		isKingSide = ChessConst::ColumnCount - 1 == cStart;
		if ( isKingSide || 0 == cStart ) {							// We are moving the rook from starting square.
			setCastlingPermission( getTurn(), isKingSide, false );	// Could be redundant if the rook was moved before.
		}
	}

	// En passant
	if ( enPassant ) {			// We have already moved the piece. Just remove the opponent's pawn.
		setPiece( rStart, cDest, PieceEnum::EMPTY );
	}

	// Mark if enPassant is possible.
	if ( PieceEnum::PAWN == moved && 0 == ( 1 & ( rStart ^ rDest ) ) ) {		// Rows have the same last bit.
		Square& square( getEnPassantSquare() );
		square.setRow( ( rStart + rDest ) / 2 );
		square.setColumn( cStart );
	} else {
		resetEnPassant();
	}

	setTurn( !getTurn() );								// Be nice.
	bumpCounters();
}


void Position::revertMove( const Move& move ) {
	unsigned rStart = move.getStart().getRow();
	unsigned cStart = move.getStart().getColumn();
	unsigned rDest = move.getEnd().getRow();
	unsigned cDest = move.getEnd().getColumn();

	// Regular move or pawn promotion.
	PieceEnum pieceMoved = move.promotedPiece() == PieceEnum::EMPTY ? getPiece( rDest, cDest )	// With color.
			: PieceOps::setColor( PieceEnum::PAWN, !getTurn() );
	PieceEnum pieceCaptured = move.capturedPiece() == PieceEnum::EMPTY ? PieceEnum::EMPTY
			: PieceOps::setColor( move.capturedPiece(), getTurn() );

	setPiece( rStart, cStart, pieceMoved );
	setPiece( rDest, cDest, move.isEnPassant() ? PieceEnum::EMPTY : pieceCaptured );

	// Castling.
	if ( PieceEnum::KING == pieceMoved ) {
		bool isKingSide = 2 == cDest - cStart;
		if( isKingSide || 3 == cStart - cDest ) {			// This was castling.
			unsigned cRookStat = isKingSide ? ChessConst::ColumnCount - 1 : 0;
			unsigned cRookDest = cDest + (unsigned)( isKingSide ? -1 : 1 );
			setPiece( rDest, cRookStat, getPiece( rDest, cRookDest ) );
			setPiece( rDest, cRookDest, PieceEnum::EMPTY );
		}
	}

	// En passant
	if ( move.isEnPassant() ) {
		setPiece( rStart, cDest, pieceCaptured );
	}

	// Restore castling permissions.
	for( bool isWhite : { true, false } ) {
		for ( bool isKingSide : { true, false } ) {
			setCastlingPermission( isWhite, isKingSide, move.getOldCastlingPermission( isWhite, isKingSide ) );
		}
	}

	bumpCounters();
	setTurn( !getTurn() );
}


/*
doAllMoves() {
 	for each row
 		for each column
 			if there is a piece of the color with the turn
 				for each possible move of that piece
					makeMove
					if the king is not under check	// Then it is valid.
						reportMove
					revertMove
 }
*/
void Position::doAllMoves( MoveEvaluator& moveEvaluator ) {
	for( unsigned row = ChessConst::RowCount - 1; row < ChessConst::RowCount; row-- ) {
		for ( unsigned column = 0; column < ChessConst::ColumnCount; column++ ) {
			PieceEnum piece = getPiece( row, column );
			bool white = PieceOps::splitColor( piece );
			if( PieceEnum::EMPTY != piece && white == getTurn() ) {
				(this->*movers[(unsigned)piece - 1])( row, column, moveEvaluator );
			}
		}
	}
}


// Attempt any move except castling and pawn moves.
bool Position::attemptDirectionalMove( unsigned rStart, unsigned cStart, unsigned rDest, unsigned cDest
		, MoveEvaluator& evaluator ) {
	PieceEnum piece = getPiece( rDest, cDest );
	bool white = PieceOps::splitColor( piece );
	bool keepGoing = PieceEnum::EMPTY == piece;			// Encountered our or opponent piece. Cannot move further.
	if( keepGoing || white != getTurn() ) {				// Empty or opposite colors.
		attemptOneMove( rStart, cStart, rDest, cDest, piece, PieceEnum::EMPTY, false, evaluator );
	}
	return keepGoing;
}


void Position::doDirectionalMoves( unsigned row, unsigned column, int rOffset, int cOffset, MoveEvaluator& evaluator ) {
	unsigned r = row, c = column;
	while( ( r += (unsigned)rOffset ) < ChessConst::RowCount && ( c += (unsigned)cOffset ) < ChessConst::ColumnCount
		   && attemptDirectionalMove( row, column, r, c, evaluator ) );
}


void Position::attemptPromotions( unsigned rStart, unsigned cStart, unsigned rDest, unsigned cDest, PieceEnum captured,
								  MoveEvaluator& evaluator ) {
	for ( PieceEnum promoted = PieceEnum::KNIGHT; promoted < PieceEnum::KING; ++promoted ) {
		attemptOneMove( rStart, cStart, rDest, cDest, captured, promoted, false, evaluator );
	}
}


void Position::doPawnMoves( unsigned row, unsigned column, MoveEvaluator& evaluator ) {
	int rOffset = getTurn() ? 1 : -1;
	unsigned r = row + (unsigned)rOffset;
	if ( r < ChessConst::RowCount ) {
		// Check enPassant.
		if ( hasEnpassant() ) {
			const Square& enPassantSquare( getEnPassantSquare() );
			if ( enPassantSquare.getRow() == r ) {
				for ( int cOffset = -1; cOffset < 2; cOffset += 2 ) {
					unsigned c = column + (unsigned)cOffset;
					if ( enPassantSquare.getColumn() == c ) {
						attemptOneMove( row, column, r, c, PieceEnum::PAWN, PieceEnum::EMPTY, true, evaluator );
					}
				}
			}
		}

		// Captures.
		for ( int cOffset = -1; cOffset < 2; cOffset += 2 ) {
			unsigned c = column + (unsigned)cOffset;
			if ( c < ChessConst::ColumnCount ) {
				PieceEnum piece = getPiece( r, c );
				bool isWhite = PieceOps::splitColor( piece );
				if ( PieceEnum::EMPTY != piece && isWhite != getTurn() ) {
					attemptOneMove( row, column, r, c, piece, PieceEnum::EMPTY, false, evaluator );
				}
			}
		}

		// Forward
		if ( isEmpty( r, column ) ) {
			if( lastRow() == r ) {
				attemptPromotions( row, column, r, column, PieceEnum::EMPTY, evaluator );
			} else {
				attemptOneMove( row, column, r, column, PieceEnum::EMPTY, PieceEnum::EMPTY, false, evaluator );
				if ( secondRow() == row ) {			// We can try to move two squares as well.
					r += (unsigned)rOffset;
					if ( isEmpty( r, column ) ) {
						attemptOneMove( row, column, r, column, PieceEnum::EMPTY, PieceEnum::EMPTY, false, evaluator );
					}
				}
			}
		}
	}
}


void Position::doKnightMoves( unsigned row, unsigned column, MoveEvaluator& evaluator ) {
	unsigned r, c;
	for ( int rOffset = -2; rOffset < 3; rOffset += 1 ) {
		if( 0 != rOffset && ( r = row + (unsigned)rOffset ) < ChessConst::RowCount ) {
			unsigned cOffset = 3 - (unsigned)abs( rOffset );
			if( ( c = column + cOffset ) < ChessConst::ColumnCount ) {
				attemptDirectionalMove( row, column, r, c, evaluator );
			}
			if( ( c = column - cOffset ) < ChessConst::ColumnCount ) {
				attemptDirectionalMove( row, column, r, c, evaluator );
			}
		}
	}
}


void Position::doBishopMoves( unsigned row, unsigned column, MoveEvaluator& evaluator ) {
	for ( int rOffset = -1; rOffset < 2; rOffset += 2 ) {
		for ( int cOffset = -1; cOffset < 2; cOffset += 2 ) {
			doDirectionalMoves( row, column, rOffset, cOffset, evaluator );
		}
	}
}


void Position::doRookMoves( unsigned row, unsigned column, MoveEvaluator& evaluator ) {
	for ( int rOffset = -1; rOffset < 2; rOffset += 2 ) {
		doDirectionalMoves( row, column, rOffset, 0, evaluator );
	}
	for ( int cOffset = -1; cOffset < 2; cOffset += 2 ) {
		doDirectionalMoves( row, column, 0, cOffset, evaluator );
	}
}


void Position::doQueenMoves( unsigned row, unsigned column, MoveEvaluator& evaluator ) {
	doBishopMoves( row, column, evaluator );
	doRookMoves( row, column, evaluator );
}


void Position::doKingMoves( unsigned row, unsigned column, MoveEvaluator& evaluator ) {
	for ( int rOffset = -1; rOffset < 2; rOffset += 1 ) {				// Regular King Moves.
		for ( int cOffset = -1; cOffset < 2; cOffset += 1 ) {
			if ( 0 != rOffset || 0 != cOffset ) {
				unsigned r = row + (unsigned)rOffset;
				unsigned c = column + (unsigned)cOffset;
				if ( r < ChessConst::RowCount && c < ChessConst::ColumnCount ) {
					attemptDirectionalMove( row, column, r, c, evaluator );
				}
			}
		}
	}
	attemptCastling( true, evaluator );
	attemptCastling( false, evaluator );
}


void Position::attemptCastling( bool isKingSide, MoveEvaluator& evaluator ) {
	if ( getCastlingPermission( getTurn(), true ) ) {
		unsigned row = getTurn() ? 0 : ChessConst::RowCount - 1;
		unsigned column = ChessConst::KingFile;
		if ( !isAttacked( row, column ) ) {							// Is king under check?
			unsigned step = isKingSide ? 1 : (unsigned) -1;
			unsigned cRookEnd = column + step;
			if ( isEmpty( row, cRookEnd ) && !isAttacked( row, cRookEnd ) ) {		// Can king pass through the next square?
				unsigned cEnd = cRookEnd + step;
				// Check if king's destination and, in case of Q side castling the square rook pass through are empty.
				if ( isEmpty( row, cEnd ) && ( isKingSide || getPiece( row, cEnd + step ) == PieceEnum ::EMPTY ) ) {
					attemptOneMove( row, column, row, cEnd, PieceEnum::EMPTY, PieceEnum::EMPTY, false, evaluator );
				}
			}
		}
	}
}


// Check if the current square is attached by any of the enemy pieces.
bool Position::isAttacked( unsigned row, unsigned column ) const {
	// We need to check attacks from

	// Pawns
	PieceEnum piece = PieceOps::setColor( PieceEnum::PAWN, !getTurn() );
	int rOffset = getTurn() ? 1 : -1;
	unsigned r = row + (unsigned)rOffset;
	bool yes = containsPiece( r, column - 1, piece ) ||  containsPiece( r, column + 1, piece );

	// King
	piece = PieceOps::setColor( PieceEnum::KING, !getTurn() );
	for ( rOffset = -1; rOffset < 2 && !yes; rOffset += 1 ) {
		for ( int cOffset = -1; cOffset < 2 && !yes; cOffset += 1 ) {
			// Checking (0,0) is ok here because it is not going to match.
			yes = containsPiece( row + (unsigned)rOffset, column + (unsigned)cOffset, piece );
		}
	}

	// Knights
	piece = PieceOps::setColor( PieceEnum::KNIGHT, !getTurn() );
	for ( rOffset = -2; rOffset < 3 && !yes; rOffset += 1 ) {
		if( 0 != rOffset ) {
			int cOffset = 3 - abs( rOffset );
			yes = containsPiece( row + (unsigned)rOffset, column + (unsigned)cOffset, piece )
					|| containsPiece( row + (unsigned)rOffset, column - (unsigned)cOffset, piece );
		}
	}

	PieceEnum queen = PieceOps::setColor( PieceEnum::QUEEN, !getTurn() );
	// Bishops
	piece = PieceOps::setColor( PieceEnum::BISHOP, !getTurn() );
	for ( rOffset = -1; rOffset < 2 && !yes; rOffset += 2 ) {
		for ( int cOffset = -1; cOffset < 2 && !yes; cOffset += 2 ) {
			yes = containsPieceInDirection( row, column, rOffset, cOffset, piece, queen );
		}
	}

	// Rooks
	piece = PieceOps::setColor( PieceEnum::ROOK, !getTurn() );
	for ( rOffset = -1; rOffset < 2 && !yes; rOffset += 2 ) {
		yes = containsPieceInDirection( row, column, rOffset, 0, piece, queen );
	}
	for ( int cOffset = -1; cOffset < 2 && !yes; cOffset += 2 ) {
		yes = containsPieceInDirection( row, column, 0, cOffset, piece, queen );
	}

	// Queens - check while doing above.

	return yes;
}


bool Position::containsPiece( unsigned row, unsigned column, PieceEnum piece ) const {
	return row < ChessConst::RowCount && column < ChessConst::ColumnCount && getPiece( row, column ) == piece;
}


bool Position::containsPieceInDirection( unsigned row, unsigned column, int rOffset, int cOffset, PieceEnum piece
		, PieceEnum queen ) const {
	PieceEnum destPiece = PieceEnum::EMPTY;
	while( ( row += (unsigned)rOffset ) < ChessConst::RowCount && ( column += (unsigned)cOffset ) < ChessConst::ColumnCount
		   && ( destPiece = getPiece( row, column ) ) == PieceEnum::EMPTY );
	bool yes = piece == destPiece || destPiece == queen;
	return yes;
}


bool Position::isCheck() const {
	// First find where the king is.
	PieceEnum king = PieceOps::setColor( PieceEnum::KING, getTurn() );
	unsigned column;
	unsigned row = ChessConst::RowCount - 1;
	do {
		for ( column = 0; column < ChessConst::ColumnCount; column++ ) {
			if( getPiece( row, column ) == king ) {
				break;
			}
		}
	} while	( ChessConst::ColumnCount == column && row-- < ChessConst::RowCount );

	return isAttacked( row, column );
}


unsigned Position::firstRow() const {
	return getTurn() ? 0 : ChessConst::RowCount - 1;
}


unsigned Position::secondRow() const {
	return getTurn() ? 1 : ChessConst::RowCount - 2;
}


unsigned Position::lastRow() const {
	return getTurn() ? ChessConst::RowCount - 1 : 0;
}


PieceEnum Position::getPieceType( const Square& square ) {
	return PieceOps::stripColor( getPiece( square ) );
}
